/*
 * WebServer.h
 *
 *  Created on: Dec 3, 2015
 *      Author: developer
 */

#include <vector>
#include <Logger.h>
#include "mongoose.h"
#include "MongEventHandler.h"
#include "MongTypes.h"
#include "MongServerOptions.h"

#ifndef MONGSERVER_H_
#define MONGSERVER_H_

namespace mong
{
/**
 * Class MongServer
 */
class MongServer
{
public:
	enum State {
		STATE_UNKNOWN = 0,
		STATE_RUNNING,
		STATE_STOPPING,
		STATE_STOPPED
	};

	MongServer();
	virtual ~MongServer();

public:

	void start(const char * connection, MongEventHandler & handler);
	void stop();
	void setServerOptions(const MongServerOptions & options);
	void sendWebsocketMessage(mong::Connection & conn,
			const std::string & msg);

protected:
	enum {
		SIZE_MAX_BUF = 1024
	};
	static bool isWebsocketConnection(const mong::Connection & nc);

private:

	void onStopped();
	void onHttpRequest(HttpMessageContext & cx);
	void onHttpReply(HttpMessageContext & cx);
	void onWebsocketHandshakeRequest(HttpMessageContext & cx);
	void onWebsocketHandshakeDone(mong::Connection & conn);
	void onWebsocketFrame(WebsocketMessageContext & cx);
	void onRpcRequest(HttpMessageContext & cx, const mong::RpcRequest & request);
	void onClose(mong::Connection & conn);
	void onWebsocketClosed(mong::Connection & conn);
	void sendReply(mong::Connection & conn, const std::string & reply);

private:
	static void handleEvent(struct mg_connection *nc, int ev, void *data);

	// ====================================================================== //
private:
	MongServerOptions m_mongOpts;
	mg_mgr m_mongMgr;
	State m_state;
	logger::Logger & m_logger;
	MongEventHandler * m_reqHandler;
};

} /* namespace mong */

#endif /* MONGSERVER_H_ */
