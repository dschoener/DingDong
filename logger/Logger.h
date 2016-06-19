/*
 * Logger.h
 *
 *  Created on: Nov 30, 2015
 *      Author: developer
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <map>

namespace logger
{
class Logger;

enum Level
{
	LEVEL_ERR = 0,
	LEVEL_WARN,
	LEVEL_INFO,
	LEVEL_DBG
};

/**
 * Class LogWriter
 */
class LogWriter
{
public:
	LogWriter();
	virtual  ~LogWriter();

	virtual void write(Level lvl, const char * msg) = 0;

	static std::string toString(Level lvl);
	const std::string & getLabel() { return m_label; }
	void setLabel(const char * label);

private:
	std::string m_label;
};

/**
 * Class ConsoleLogWriter
 */
class ConsoleLogWriter : public LogWriter
{
public:

	virtual void write(Level lvl, const char * msg);
};

/**
 * Class SysLogWriter
 */
class SysLogWriter : public LogWriter
{
public:
	SysLogWriter(int facility);
	virtual ~SysLogWriter();

	virtual void write(Level lvl, const char * msg);
};

/**
 * Class Logger
 */
class Logger
{
public:
	enum Size {
		SIZE_LOG_BUFFER = 1024
	};

private:
	Level m_curLevel;
	LogWriter * m_writer;
	ConsoleLogWriter defaultWriter;
	std::string m_label;

public:
	Logger(const char * label);
	virtual ~Logger();

	void info(const char * msg, ...);
	void err(const char * msg, ...);
	void warn(const char * msg, ...);
	void dbg(const char * msg, ...);
	void log(Level level, const char * msg);

	void setLevel(Level level);
	Level getLevel() const;

	void setWriter(LogWriter & writer);
	const char * getLabel() const;

private:
	LogWriter & getWriter();
};

/**
 * Class LoggerManager
 */
class LoggerManager
{
private:
	typedef std::map<std::string, Logger> LoggerMap;
	static LoggerMap * mapLogger;
	static Level baseLevel;

public:
	LoggerManager();
	virtual ~LoggerManager();
	static Logger& getLogger(const char * label);
};

} /* namespace gpiod */

#endif /* LOGGER_H_ */
