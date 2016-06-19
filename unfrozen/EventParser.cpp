/*
 * EventParser.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include "EventParser.h"
#include "JsonParser.h"
#include "PingEvent.h"
#include "StringConverter.h"
#include "GpioInfoEvent.h"
#include "GpioStateEvent.h"
#include "GpioInfoRequestEvent.h"
#include "GpioStateRequestEvent.h"

namespace unfrozen
{

EventParser::EventParser()
{}

EventParser::~EventParser()
{
	m_events.clear();
}

static const std::string TOK_NAME("cmd.name");
static const std::string TOK_PARAM_GID("cmd.params.gid");
static const std::string TOK_PARAM_STATE("cmd.params.state");
static const std::string TOK_PARAM_SID("cmd.params.sid");
static const std::string GRP_NAME_GPIO("gpio-");

const EventParser::EventList & EventParser::parse(const std::string & in)
throw (sweets::ParseException)
{
	m_events.clear();

	JsonParser parser;
	parser.parse(in);
	const JsonToken & tokName = parser.find(TOK_NAME);

	if (tokName.getType() != JsonToken::JSON_TYPE_STRING)
		throw sweets::ParseException("unexpected command name type for command 'cmd.name' found");

	JsonToken tokSid = parser.find(TOK_PARAM_SID);
	assertToken(TOK_PARAM_SID, tokSid, JsonToken::JSON_TYPE_NUMBER);
	unsigned sid = static_cast<unsigned>(
			sweets::StringConverter::toInteger(tokSid.getValue()));

	if (tokName == PingEvent::Name)
	{
		m_events.push_back(EventList::value_type(PingEvent(sid)));
	}
	else if (tokName.getValue().substr(0, GRP_NAME_GPIO.length()) == GRP_NAME_GPIO)
	{
		if (tokName == GpioStateEvent::Name)
		{
			JsonToken tokGid = parser.find(TOK_PARAM_GID);
			JsonToken tokState = parser.find(TOK_PARAM_STATE);

			assertToken(TOK_PARAM_GID,   tokGid,   JsonToken::JSON_TYPE_STRING);
			assertToken(TOK_PARAM_STATE, tokState, JsonToken::JSON_TYPE_STRING);

			m_events.push_back(EventList::value_type(
				GpioStateEvent(sid, tokGid.getValue(), tokState.getValue())));
		}
		else if (tokName == GpioStateRequestEvent::Name)
		{
			JsonToken tokGid = parser.find(TOK_PARAM_GID);

			assertToken(TOK_PARAM_GID, tokGid, JsonToken::JSON_TYPE_STRING);

			m_events.push_back(EventList::value_type(
				GpioStateRequestEvent(sid, tokGid.getValue())));
		}
		else if (tokName == GpioInfoRequestEvent::Name)
		{
			m_events.push_back(EventList::value_type(
				GpioInfoRequestEvent(sid)));
		}
		else if (tokName == GpioInfoEvent::Name)
		{
			bool foundMore = true;
			GpioInfoEvent::GpioInfoItemList items;

			for (int i = 0; foundMore; i++)
			{
				JsonToken tokItemGid = parser.find(TOK_PARAM_GID, i);

				if (tokItemGid.getType() != JsonToken::JSON_TYPE_NULL)
				{
					assertToken(TOK_PARAM_GID, tokItemGid, JsonToken::JSON_TYPE_STRING);
					JsonToken tokItemState = parser.find(TOK_PARAM_STATE, i);

					assertToken(TOK_PARAM_STATE, tokItemState, JsonToken::JSON_TYPE_STRING);

					items.push_back(GpioInfoEvent::GpioInfoItemList::value_type(
						GpioInfoEvent::GpioInfoItem(tokItemGid.getValue(),
								tokItemState.getValue())));
				}
				else
				{
					foundMore = false;
				}
			}

			m_events.push_back(EventList::value_type(
				GpioInfoEvent(sid, items)));
		}
		else
		{
			throw sweets::ParseException(std::string("unknown command found: ")
				+ tokName.getValue());
		}
	}
	else
	{
		throw sweets::ParseException(std::string("unknown command found: ")
			+ tokName.getValue());
	}

	return m_events;
}

void EventParser::assertToken(const std::string & item, const JsonToken & token,
	JsonToken::Type type) throw (sweets::ParseException)
{
	if (token.getType() != type)
		throw sweets::ParseException(std::string("item ") + item
				+ std::string(" not found"));
}

} /* namespace unfrozen */
