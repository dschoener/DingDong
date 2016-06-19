/*
 * WebServer.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: developer
 */

#include "MongServer.h"

#include "mongoose.h"
#include <string.h>

using namespace logger;

namespace mong
{

// ====================================================================== //
// MongServer
// ====================================================================== //
MongServer::MongServer()
:m_state(STATE_STOPPED),
 m_logger(LoggerManager::getLogger("mong-server")),
 m_reqHandler(NULL)
{}

MongServer::~MongServer()
{}

bool MongServer::isWebsocketConnection(const Connection & connection)
{
	return (connection.flags & MG_F_IS_WEBSOCKET) > 0;
}

void MongServer::handleEvent(struct mg_connection *nc, int ev, void *ev_data)
{
	MongServer * server = (MongServer*)nc->mgr->user_data;

	switch (ev)
	{
		case MG_EV_HTTP_REQUEST:
		{
			HttpMessageContext context(*nc, *((HttpMessage*)ev_data));
			server->onHttpRequest(context);
			break;
		}
		case MG_EV_HTTP_REPLY:
		{
			HttpMessageContext context(*nc, *((HttpMessage*)ev_data));
			server->onHttpReply(context);
			break;
		}
		case MG_EV_WEBSOCKET_HANDSHAKE_REQUEST:
		{
			HttpMessageContext context(*nc, *((HttpMessage*)ev_data));
			server->onWebsocketHandshakeRequest(context);
			break;
		}
		case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
		{
			server->onWebsocketHandshakeDone(*nc);
			break;
		}
		case MG_EV_WEBSOCKET_FRAME:
		{
			WebsocketMessageContext context(*nc, *((struct websocket_message*)ev_data));
			server->onWebsocketFrame(context);
			break;
		}
		case MG_EV_CLOSE:
			server->onClose(*nc);
			break;
		default:
			// nothing to do!
			break;
	}
}

void MongServer::start(const char * connection, MongEventHandler & handler)
{
	m_reqHandler = &handler;
	m_logger.info("starting server ...");

	// init mongoose
	mg_mgr_init(&m_mongMgr, this);

	m_logger.dbg("preparing websocket server");
	struct mg_connection * nc = mg_bind(&m_mongMgr, connection, handleEvent);
	mg_set_protocol_http_websocket(nc);

	m_state = STATE_RUNNING;

	for (;m_state == STATE_RUNNING;) {
		const time_t now = mg_mgr_poll(&m_mongMgr, 500);
		handler.onIdle(now);
	}

	onStopped();
}

void MongServer::stop()
{
	m_logger.info("stopping server ...");
	m_state = STATE_STOPPING;
}

void MongServer::setServerOptions(const MongServerOptions & options)
{
	m_mongOpts = options;
}

void MongServer::sendReply(mong::Connection & connection, const std::string & reply)
{
	mg_printf(&connection,
			"HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
			"Content-Type: application/json\r\n\r\n%s",
			reply.length(), reply.c_str());
}

void MongServer::sendWebsocketMessage(mong::Connection & connection,
		const std::string & msg)
{
	mg_send_websocket_frame(&connection, WEBSOCKET_OP_TEXT, msg.c_str(), msg.length());
}

// ====================================================================== //
// Event handlers
// ====================================================================== //

void MongServer::onStopped()
{
	mg_mgr_free(&m_mongMgr);
	m_state = STATE_STOPPED;
	m_logger.info("server stopped");
}

void MongServer::onHttpRequest(HttpMessageContext & context)
{
	const mong::HttpMessage & hm = context.getHttpMessage();
	m_logger.info("received HTTP request: %s", hm.message);
	mg_serve_http(&context.getConnection(), &context.getHttpMessage(),
			(const ServeHttpOptions&)m_mongOpts);
	/*
	struct json_token tokens[200];
	struct mg_rpc_request request;

	memset(&request, 0, sizeof(request));
	int rv = parse_json(hm.body.p, hm.body.len, tokens,
			sizeof(tokens) / sizeof(tokens[0]));

	if (rv <= 0)
	{
		char buf[SIZE_MAX_BUF];
		int err_code = (rv == JSON_STRING_INVALID) ? JSON_RPC_PARSE_ERROR
												  : JSON_RPC_SERVER_ERROR;
		mg_rpc_create_std_error(buf, sizeof(buf), &request, err_code);
		m_logger.log(logger::LEVEL_ERR, buf);
		return;
	}

	request.message = tokens;
	request.id = find_json_token(tokens, "id");
	request.method = find_json_token(tokens, "method");
	request.params = find_json_token(tokens, "params");

	if (request.id == NULL || request.method == NULL)
	{
		char buf[SIZE_MAX_BUF];
		mg_rpc_create_std_error(buf, sizeof(buf), &request,
				JSON_RPC_INVALID_REQUEST_ERROR);
		m_logger.log(logger::LEVEL_ERR, buf);
		return;
	}

	onRpcRequest(context, request);
	context.getConnection().flags |= MG_F_SEND_AND_CLOSE;
	*/
}

void MongServer::onClose(mong::Connection & connection)
{
	m_logger.info("connection closed");
	if (isWebsocketConnection(connection))
	{
		onWebsocketClosed(connection);
	}
}

void MongServer::onWebsocketClosed(mong::Connection & connection)
{
	m_logger.info("websocket connection closed");
	m_reqHandler->onWebsocketClosed(connection);
}

void MongServer::onHttpReply(HttpMessageContext & context)
{
	const mong::HttpMessage & hm = context.getHttpMessage();
	m_logger.info("received HTTP reply: %s", hm.message);
}

void MongServer::onWebsocketHandshakeRequest(HttpMessageContext & context)
{
	const mong::HttpMessage & hm = context.getHttpMessage();
	m_logger.info("received websocket handshake request: %s", hm.message);
}

void MongServer::onWebsocketHandshakeDone(mong::Connection & conn)
{
	m_logger.info("received websocket handshake done");
	m_reqHandler->onWebsocketNew(conn);
}

void MongServer::onWebsocketFrame(WebsocketMessageContext & context)
{
	const mong::WebsocketMessage & wm = context.getWebsocketMessage();
	m_logger.info("received websocket frame: %.*s", wm.size, wm.data);
	m_reqHandler->onWebsocketMessage(context);
}

void MongServer::onRpcRequest(HttpMessageContext & context,
		const mong::RpcRequest & request)
{
	m_logger.info("received RPC request: %.*s", request.message->len,
			request.message->ptr);
	sendReply(context.getConnection(), m_reqHandler->handleRpcRequest(request));
}

}
