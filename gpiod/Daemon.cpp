/*
 * Daemon.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#include "Daemon.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <sstream>
#include <string.h>

using namespace logger;
using namespace sweets;

namespace gpiod
{
static const std::string CONF_RUN_DIRECTORY("daemon.run_directory");
static const std::string CONF_GPIO("daemon.gpio");
static const std::string EVENT_INIT("init");
static const std::string EVENT_EXIT("exit");
static const std::string EVENT_EVENT("event");

Daemon::Daemon()
:m_logger(LoggerManager::getLogger("gpiod")),
 m_state(STATE_UNKNOWN)
{}

Daemon::~Daemon()
{}

void Daemon::setConfigFile(const std::string & configFile)
{
	this->configFile = configFile;
}

void Daemon::stop()
{
	m_state = STATE_STOPPING;
	m_logger.info("stopping daemon");
}

void Daemon::reset()
{
	m_logger.info("reseting daemon");
}


void Daemon::exec(const std::string & pathCmd, const Daemon::GpioInfo & gpi,
		const std::string & hint, const std::string & value)
{
	const std::string & gpio = gpi.getValue(GpioInfo::KEY_PATH);
	const std::string & direction = gpi.getValue(GpioInfo::KEY_DIR);
	std::ostringstream oss;
	oss << pathCmd << " \"" << gpio << "\" \"" << direction << "\" \""
			<< hint << "\" \"" << value << "\"";
	int rv = ::system(oss.str().c_str());
	if (rv < 0)
	{
		m_logger.warn("executing command '%s' (%s) failed with status %d",
				pathCmd.c_str(), hint.c_str(), rv);
	}
	else
	{
		m_logger.dbg("exec: %s", oss.str().c_str());
	}
}

void Daemon::initFileDescriptors()
{
	m_logger.dbg("initializing ...");

	m_descriptors.resize(mapGpioInfo.size());

	int i = 0;
	for (MapGpioInfo::const_iterator iter = mapGpioInfo.begin();
			iter != mapGpioInfo.end(); iter++, i++)
	{
		const GpioInfo & gpi = (*iter).second;
		const std::string & pathGpio = gpi.getValue(GpioInfo::KEY_PATH);

		m_descriptors[i].fd = open(pathGpio);
		m_descriptors[i].events = POLLIN;
		m_descriptors[i].revents = 0;

		// call init scripts
		const std::string & pathScript = gpi.getValue(GpioInfo::KEY_SCRIPT_EVENT);
		if (pathScript.length() > 0)
		{
			exec(pathScript, gpi, EVENT_INIT);
		}
	}
}

void Daemon::cleanupFileDescriptors()
{
	m_logger.dbg("finalizing ...");

	int i = 0;
	for (MapGpioInfo::const_iterator iter = mapGpioInfo.begin();
			iter != mapGpioInfo.end(); iter++, i++)
	{
		const GpioInfo & gpi = (*iter).second;
		::close(m_descriptors[i].fd);

		// call exit scripts
		const std::string & pathScript = gpi.getValue(GpioInfo::KEY_SCRIPT_EVENT);
		if (pathScript.length() > 0)
		{
			exec(pathScript, gpi, EVENT_EXIT);
		}
	}

	m_descriptors.clear();
}

void Daemon::handleDescriptorEvents()
{
	int i = 0;
	for (MapGpioInfo::const_iterator iter = mapGpioInfo.begin();
			iter != mapGpioInfo.end(); iter++, i++)
	{
		if ((m_descriptors[i].revents & POLLIN) &&
			!(m_descriptors[i].revents & POLLHUP))
		{
			const GpioInfo & gpi = (*iter).second;
			const std::string & pathGpio = gpi.getValue(GpioInfo::KEY_PATH);

			m_logger.info("received event for file '%s': %d", pathGpio.c_str(),
					m_descriptors[i].revents);

			const std::string sread(read(m_descriptors[i].fd,
					(*iter).second.getValue(GpioInfo::KEY_PATH)));

			const std::string & pathScript = gpi.getValue(
					GpioInfo::KEY_SCRIPT_EVENT);
			if (pathScript.length() > 0)
			{
				exec(pathScript, gpi, EVENT_EVENT, sread);
			}
			m_descriptors[i].revents = 0;
		}
	}
}

void Daemon::run() throw(std::exception)
{
	loadConfig();
	changeDirectory();
	initFileDescriptors();

	m_state = STATE_RUNNING;

	while ((mapGpioInfo.size() > 0) && (m_state == STATE_RUNNING))
	{
		int rv = ppoll(m_descriptors.data(), mapGpioInfo.size(), NULL, NULL);

		if (rv > 0)
		{
			handleDescriptorEvents();
		}
		else if (rv < 0)
		{
			if (errno != EINTR)
			{
				throw ErrorException("unexpected error");
			}
		}
	}

	cleanupFileDescriptors();
	m_state = STATE_STOPPED;
}

const std::string Daemon::read(int fd, const std::string & file)
{
	m_logger.dbg("read file '%s'", file.c_str());
	char buf[128];
	ssize_t rv = ::read(fd, buf, sizeof(buf) -1);

	if (rv < 0)
	{
		m_logger.warn("failed to read file '%s' (%s)", file.c_str(),
				strerror(errno));
		rv = 0;
	}

	buf[rv] = '\0';
	return std::string(buf);
}

int Daemon::open(const std::string & file) throw (ErrorException)
{
	m_logger.dbg("open file '%s'", file.c_str());
	int fd = ::open(file.c_str(), O_RDONLY|O_NONBLOCK);
	if (fd < 0)
	{
		std::ostringstream oss;
		oss << "failed to open file '" << file << "'";
		throw ErrorException(oss.str());
	}
	return fd;
}

void Daemon::changeDirectory() throw (ErrorException)
{
	if (chdir(workDirectory.c_str()) < 0)
	{
		throw ErrorException("failed change directory");
	}
}

void Daemon::setSessionId() throw (ErrorException)
{
	if (setsid() < 0)
	{
		throw ErrorException("failed to create a new SID");
	}
}

bool Daemon::fork() throw (ErrorException)
{
	pid_t pid = ::fork();
	if (pid != 0)
	{
		if (pid < 0)
		{
			throw ErrorException("failed to fork process");
		}
	}
	return (pid == 0);
}

void Daemon::runDaemonized() throw (std::exception)
{
	m_logger.dbg("daemon is going to daemonize");

	// create new process
	if (!fork())
		return;

	// running as child process!
	m_logger.dbg("new daemon process has been forked");

	umask(0);
	setSessionId();

//	::close(STDOUT_FILENO);
//	::close(STDERR_FILENO);
//	::close(STDIN_FILENO);

	run();
}
} /* namespace gpiod */
