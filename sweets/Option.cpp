/*
 * Option.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#include "Option.h"
#include <unistd.h>
#include <stdlib.h>
#include <string>

namespace sweets
{

Option::Option()
:cntArgs(0),
 vectArgs(NULL)
{}

Option::~Option()
{}

void Option::addOption(char option, bool hasArgument)
{
	mapOptions[option].bHasArgument = hasArgument;
}

const Option::OptionInfo & Option::getOption(char option) throw (InvalidOptionException)
{
	if (mapOptions.count(option) == 0)
	{
		std::string msg("option character ");
		msg.push_back(option);
		msg.append(" not found");
		throw InvalidOptionException(msg.c_str());
	}

	return mapOptions[option];
}

int Option::getFirstOption(int argc, char * const * argv)
{
	optind = 1; // reset
	setOptionString(strShortOpt);
	cntArgs = argc;
	vectArgs = argv;
	return getNextOption();
}

int Option::getNextOption()
{
	return getopt(cntArgs, vectArgs, strShortOpt.c_str());
}

void Option::setOptionString(std::string & s)
{
	s.clear();
	OptionInfoMap::iterator iter = mapOptions.begin();
	for (; iter != mapOptions.end(); iter++)
	{
		s += (*iter).first;
		if ((*iter).second.bHasArgument)
			s += ':';
	}
}

void Option::parse(int argc, char * const * argv) throw (ParseException)
{
	for (int opt = getFirstOption(argc, argv); opt != -1; opt = getNextOption())
	{
		if (mapOptions.count(opt) == 0)
			throw ParseException(std::string("invalid argument found: " + opt).c_str());

		mapOptions[opt].bIsEnabled = true;
		if (mapOptions[opt].bHasArgument)
			mapOptions[opt].strArgument = optarg;
		else
			mapOptions[opt].strArgument = "";
    }
}

} /* namespace opt */
