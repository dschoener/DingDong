/*
 * CommandInChannel.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "EventInChannel.h"

namespace unfrozen
{

EventInChannel::EventInChannel(sweets::Reader & reader)
:m_reader(reader)
{}

const EventParser::EventList & EventInChannel::receiveCommands()
throw (sweets::Exception)
{
	m_commands.clear();

	EventParser parser;
	m_commands = parser.parse(m_reader.read());

	return m_commands;
}

} /* namespace unfrozen */
