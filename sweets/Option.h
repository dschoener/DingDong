/*
 * Option.h
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#ifndef OPTION_H_
#define OPTION_H_

#include <string>
#include <map>
#include "ParseException.h"

namespace sweets
{
/**
 * Class InvalidOptionException
 */
class InvalidOptionException : public Exception
{
public:
	InvalidOptionException(const char * what)
		:Exception(what) {}
};

/**
 * Class Option
 */
class Option
{
private:
	class OptionInfo
	{
	public:
		OptionInfo() :bHasArgument(false), bIsEnabled(false) {}

		bool isEnabled() const { return bIsEnabled; }
		bool hasArgument() const { return bHasArgument; }
		const std::string getArgument() const { return strArgument; }

		bool bHasArgument;
		bool bIsEnabled;
		std::string strArgument;
	};

	typedef std::map<char, OptionInfo> OptionInfoMap;
	OptionInfoMap mapOptions;
	std::string strShortOpt;
	int cntArgs;
	char * const * vectArgs;

public:
	Option();
	virtual ~Option();

public:
	void parse(int argc, char * const * argv) throw(ParseException);
	void addOption(char option, bool hasArgument = false);
	const OptionInfo & getOption(char option) throw (InvalidOptionException);

private:
	void setOptionString(std::string & buffer);
	int getFirstOption(int argc, char * const * argv);
	int getNextOption();
};

} /* namespace opt */

#endif /* OPTION_H_ */
