/*
 * CommandInChannel.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef COMMANDINCHANNEL_H_
#define COMMANDINCHANNEL_H_

#include <IOException.h>
#include <Reader.h>

#include "EventParser.h"

namespace unfrozen
{

/**
 * Class CommandInChannel
 */
class EventInChannel
{
public:
	EventInChannel(sweets::Reader & reader);

	const EventParser::EventList & receiveCommands() throw (sweets::Exception);

private:
	sweets::Reader & m_reader;
	EventParser::EventList m_commands;
};

} /* namespace unfrozen */

#endif /* COMMANDINCHANNEL_H_ */
