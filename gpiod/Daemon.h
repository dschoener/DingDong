/*
 * Daemon.h
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include <Exception.h>
#include <Logger.h>

#include <string>
#include <map>
#include <vector>
#include <poll.h>
#include <PipeWriter.h>
#include "Types.h"
#include "GpioInfo.h"

namespace gpiod
{

class Daemon
{
public:
	enum State {
		STATE_UNKNOWN = 0,
		STATE_RUNNING,
		STATE_STOPPING,
		STATE_STOPPED
	};

	typedef std::vector<PollInfo> PollInfoArray;
	typedef std::map<std::string, GpioInfo> MapGpioInfo;

	Daemon();
	virtual ~Daemon();

public:
	void run() throw(std::exception);
	void runDaemonized() throw(std::exception);
	void setConfigFile(const std::string & configFile);
	void stop();
	void reset();

private:
	void loadConfig() throw (libconfig::ConfigException);
	void changeDirectory() throw (sweets::ErrorException);
	void setSessionId() throw (sweets::ErrorException);
	bool fork() throw (sweets::ErrorException);
	int open(const std::string & file) throw (sweets::ErrorException);
	void exec(const std::string & pathCmd, const GpioInfo & gpi,
			const std::string & hint, const std::string & value = "");
	const std::string read(int fd, const std::string & file);
	void initFileDescriptors();
	void cleanupFileDescriptors();
	void handleDescriptorEvents();

	Config m_config;
	logger::Logger & m_logger;
	MapGpioInfo mapGpioInfo;
	std::string configFile;
	std::string workDirectory;
	PollInfoArray m_descriptors;
	State m_state;
};

} /* namespace gpiod */

#endif /* DAEMON_H_ */
