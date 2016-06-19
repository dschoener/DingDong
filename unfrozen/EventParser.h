/*
 * EventParser.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <list>
#include <string>
#include <ParseException.h>

#include "Event.h"
#include "JsonToken.h"

#ifndef COMMANDPARSER_H_
#define COMMANDPARSER_H_

namespace unfrozen
{

/**
 * Class EventParser
 */
class EventParser
{
public:
	typedef std::list<Event> EventList;

	EventParser();
	virtual ~EventParser();

	const EventList & parse(const std::string & in) throw (sweets::ParseException);

private:
	static void assertToken(const std::string & item, const JsonToken & token,
		JsonToken::Type type) throw (sweets::ParseException);

	EventList m_events;
};

} /* namespace unfrozen */

#endif /* COMMANDPARSER_H_ */
