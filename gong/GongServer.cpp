/*
 * GongRpcServer.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: developer
 */

#include <vector>
#include <unistd.h>
#include <Exception.h>
#include <JsonParser.h>
#include <sstream>
#include <MongServerOptions.h>
#include <MongTypes.h>

#include "GongServer.h"
#include <EventParser.h>
#include <PingEvent.h>
#include <EventInChannel.h>
#include <EventOutChannel.h>
#include <PongEvent.h>

using namespace logger;
using namespace sweets;
using namespace unfrozen;
using namespace mong;

namespace gong
{

// ========================================================================== //
// GongServer
// ========================================================================== //
static const std::string CONF_BIND_ADDRESS("server.bind_address");
static const std::string CONF_DOC_ROOT("server.document_root");
static const std::string CONF_INDEX_FILES("server.index_files");
static const std::string CONF_AUTH_DOMAIN("server.auth_domain");
static const std::string CONF_ENABLE_DIR_LISTING("server.enable_directory_listing");
static const std::string CONF_PIPE_IN("server.pipe_in");
static const std::string CONF_PIPE_OUT("server.pipe_out");

GongServer::GongServer()
:m_logger(LoggerManager::getLogger("gong")),
 m_bindAddr(":8080"),
 m_pipeIn(NULL),
 m_pipeOut(NULL)
{}

GongServer::~GongServer()
{
	closeChannels();
}

const std::string & GongServer::handleRpcRequest(const mong::RpcRequest & request)
{
	static const std::string s_defaultResponse("{ result : none }");
	return s_defaultResponse;
}

void GongServer::onWebsocketNew(const mong::Connection & connecton)
{

}

void GongServer::onWebsocketClosed(const mong::Connection & connecton)
{

}

void GongServer::onIdle(time_t now)
{
	receiveCommands();
}

void GongServer::receiveCommands()
{
	if (m_pipeIn == NULL || !m_pipeIn->isOpen())
		return;

	try
	{
		EventInChannel eic(*m_pipeIn);
		const EventParser::EventList & list = eic.receiveCommands();

		for (EventParser::EventList::const_iterator iter = list.begin();
				iter != list.end(); iter++)
		{
			handleEvent(*iter);
		}
	}
	catch (Exception & e)
	{
		m_logger.err("failed to parse command (%s)", e.what());
	}
}

void GongServer::handleEvent(const unfrozen::Event & event)
{
	m_logger.info("execute command: %s", event.getName().c_str());

	if (event.getName() == PingEvent::Name)
	{
		if (tryOpenOutChannel())
		{
			EventOutChannel eoc(*m_pipeOut);
			eoc.sendCommand(PongEvent(event.getSessionId()));
		}
	}

	else
	{
		throw ParseException(std::string("invalid command received: ")
			+ event.getName().c_str());
	}
}

void GongServer::lookupConfigValue(libconfig::Config & config, const std::string & id,
		std::string & opt) throw (libconfig::ConfigException)
{
	const char * value = NULL;
	lookupConfigValue(config, id, value);
	opt = value;
}

void GongServer::lookupConfigValue(libconfig::Config & config, const std::string & id,
		const char * & opt) throw (libconfig::ConfigException)
{
	if (config.exists(CONF_DOC_ROOT.c_str()))
	{
		const char * value = NULL;
		config.lookupValue(id.c_str(), value);
		opt = value;
	}
}

void GongServer::loadConfig(const std::string & file)
throw (libconfig::ConfigException)
{
	m_logger.info("reading configuration file '%s'", file.c_str());

	libconfig::Config config;
	config.readFile(file.c_str());
	mong::ServeHttpOptions options;

	lookupConfigValue(config, CONF_DOC_ROOT,       options.document_root);
	lookupConfigValue(config, CONF_AUTH_DOMAIN,    options.auth_domain);
	lookupConfigValue(config, CONF_INDEX_FILES,    options.index_files);
	lookupConfigValue(config, CONF_BIND_ADDRESS,   m_bindAddr);
	lookupConfigValue(config, CONF_ENABLE_DIR_LISTING, options.enable_directory_listing);
	m_server.setServerOptions(options);

	std::string pipeIn, pipeOut;
	lookupConfigValue(config, CONF_PIPE_IN, pipeIn);
	lookupConfigValue(config, CONF_PIPE_OUT, pipeOut);

	openChannels(pipeIn, pipeOut);
}

bool GongServer::tryOpenOutChannel()
{
	if (!m_pipeOut->isOpen())
	{
		try
		{
			m_pipeOut->open();
		}
		catch(ErrorException & e)
		{
			m_logger.err("%s", e.what());
		}
	}

	return m_pipeOut->isOpen();
}

bool GongServer::tryOpenInChannel()
{
	if (!m_pipeIn->isOpen())
	{
		try
		{
			m_pipeIn->open();
		}
		catch(ErrorException & e)
		{
			m_logger.err("%s", e.what());
		}
	}

	return m_pipeIn->isOpen();
}

void GongServer::openChannels(const std::string & pipeInName,
		const std::string & pipeOutName)
{
	closeChannels();

	m_pipeIn = new PipeReader(pipeInName);
	m_pipeOut = new PipeWriter(pipeOutName);

	tryOpenOutChannel();
	tryOpenInChannel();
}

void GongServer::closeChannels()
{
	if (m_pipeIn)
	{
		delete m_pipeIn;
		m_pipeIn = NULL;
	}

	if (m_pipeOut)
	{
		delete m_pipeOut;
		m_pipeOut = NULL;
	}
}

void GongServer::start()
{
	m_server.start(m_bindAddr.c_str(), *this);
}

void GongServer::stop()
{
	m_server.stop();
}

} /* namespace server */
