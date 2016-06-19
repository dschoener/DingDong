/*
 * GongRpcServer.h
 *
 *  Created on: Dec 9, 2015
 *      Author: developer
 */

#ifndef GONGSERVER_H_
#define GONGSERVER_H_

#include <Event.h>
#include <MongServer.h>
#include <Logger.h>
#include <Exception.h>
#include <libconfig.h++>
#include <JsonParser.h>
#include <MongEventHandler.h>
#include <MongTypes.h>
#include <PipeReader.h>
#include <PipeWriter.h>
#include <EventParser.h>

namespace gong
{

/**
 * Class GongServer
 */
class GongServer: public mong::MongEventHandler
{
public:
	GongServer();
	virtual ~GongServer();

	virtual const std::string & handleRpcRequest(const mong::RpcRequest & request);
	virtual void onWebsocketNew(const mong::Connection & connecton);
	virtual void onWebsocketClosed(const mong::Connection & connecton);
	virtual void onIdle(time_t now);

	void loadConfig(const std::string & file) throw (libconfig::ConfigException);
	void start();
	void stop();

private:
	void lookupConfigValue(libconfig::Config & config, const std::string & id,
			const char * & opt) throw (libconfig::ConfigException);
	void lookupConfigValue(libconfig::Config & config, const std::string & id,
			std::string & opt) throw (libconfig::ConfigException);
	void openChannels(const std::string & pipeIn, const std::string & pipeOut);
	bool tryOpenOutChannel();
	bool tryOpenInChannel();
	void closeChannels();
	void receiveCommands();
	void handleEvent(const unfrozen::Event & event);

	mong::MongServer m_server;
	logger::Logger & m_logger;
	std::string m_bindAddr;
	sweets::PipeReader * m_pipeIn;
	sweets::PipeWriter * m_pipeOut;
};

} /* namespace server */

#endif /* GONGSERVER_H_ */
