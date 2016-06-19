/*
 * Logger.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: developer
 */

#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <syslog.h>

namespace logger
{
// ==================================================================== //
// LoggerManager
// ==================================================================== //
LoggerManager::LoggerMap * LoggerManager::mapLogger = NULL;
Level LoggerManager::baseLevel = logger::LEVEL_INFO;
LoggerManager lm;

LoggerManager::LoggerManager()
{}

LoggerManager::~LoggerManager()
{
	if (mapLogger != NULL)
		delete mapLogger;
}

Logger & LoggerManager::getLogger(const char * label)
{
	if (mapLogger == NULL)
		mapLogger = new LoggerManager::LoggerMap;

	LoggerMap::iterator iter = mapLogger->find(label);
	if (iter == mapLogger->end())
	{
		// does not exist
		iter = mapLogger->insert(LoggerMap::value_type(label, Logger(label))).first;
		(*iter).second.setLevel(baseLevel);
	}

	return (*iter).second;
}

// ==================================================================== //
// LogWriter
// ==================================================================== //
LogWriter::LogWriter()
{}

LogWriter::~LogWriter()
{}

std::string LogWriter::toString(Level lvl)
{
	switch(lvl)
	{
	case LEVEL_DBG:
		return std::string("dbg");
	case LEVEL_INFO:
		return std::string("inf");
	case LEVEL_WARN:
		return std::string("wrn");
	case LEVEL_ERR:
		return std::string("err");
	default:
		return std::string("???");
	}
}

void LogWriter::setLabel(const char * label)
{
	m_label = label;
}

// ==================================================================== //
// SysLogWriter
// ==================================================================== //
SysLogWriter::SysLogWriter(int facility)
{
	openlog(getLabel().c_str(), LOG_PERROR|LOG_CONS|LOG_PID|LOG_NOWAIT,
			facility);
}

SysLogWriter::~SysLogWriter()
{
	closelog();
}

void SysLogWriter::write(Level level, const char * msg)
{
	int prio = LOG_ERR;
	switch(level)
	{
	case LEVEL_ERR:
		prio = LOG_ERR;
		break;
	case LEVEL_INFO:
		prio = LOG_INFO;
		break;
	case LEVEL_WARN:
		prio = LOG_WARNING;
		break;
	default:
		prio = LOG_DEBUG;
		break;
	}
	syslog(prio, "%s", msg);
}

// ==================================================================== //
// ConsoleLogWriter
// ==================================================================== //
void ConsoleLogWriter::write(Level level, const char * msg)
{

	if (level == LEVEL_ERR || level == LEVEL_WARN)
	{
		std::cerr << toString(level) << ": " << msg << std::endl;
	}
	else
	{
		std::cout << toString(level) << ": " << msg << std::endl;
	}
}

// ==================================================================== //
// Logger
// ==================================================================== //
Logger::Logger(const char * label)
:m_curLevel(LEVEL_INFO),
 m_writer(NULL),
 m_label(label)
{}

Logger::~Logger()
{}

const char * Logger::getLabel() const
{
	return m_label.c_str();
}

void Logger::info(const char * msg, ...)
{
	char msgBuf[SIZE_LOG_BUFFER];
	va_list args;
	va_start (args, msg);
	vsnprintf (msgBuf, sizeof(msgBuf), msg, args);
	va_end (args);
	log(LEVEL_INFO, msgBuf);
}

void Logger::err(const char * msg, ...)
{
	char msgBuf[SIZE_LOG_BUFFER];
	va_list args;
	va_start (args, msg);
	vsnprintf (msgBuf, sizeof(msgBuf), msg, args);
	va_end (args);
	log(LEVEL_ERR, msgBuf);
}

void Logger::warn(const char * msg, ...)
{
	char msgBuf[SIZE_LOG_BUFFER];
	va_list args;
	va_start (args, msg);
	vsnprintf (msgBuf, sizeof(msgBuf), msg, args);
	va_end (args);
	log(LEVEL_WARN, msgBuf);
}

void Logger::dbg(const char * msg, ...)
{
	char msgBuf[SIZE_LOG_BUFFER];
	va_list args;
	va_start (args, msg);
	vsnprintf (msgBuf, sizeof(msgBuf), msg, args);
	va_end (args);
	log(LEVEL_DBG, msgBuf);
}

void Logger::log(Level level, const char * msg)
{
	if (level <= m_curLevel)
	{
		getWriter().write(level, msg);
	}
}

void Logger::setLevel(Level level)
{
	m_curLevel = level;
}

Level Logger::getLevel() const
{
	return m_curLevel;
}

LogWriter & Logger::getWriter()
{
	if (m_writer != NULL)
	{
		return *m_writer;
	}
	return defaultWriter;
}

void Logger::setWriter(LogWriter & writer)
{
	m_writer = &writer;
	m_writer->setLabel(getLabel());
}
} /* namespace gpiod */
