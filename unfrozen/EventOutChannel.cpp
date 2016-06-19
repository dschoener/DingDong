/*
 * CommandOutChannel.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "EventOutChannel.h"

namespace unfrozen
{

EventOutChannel::EventOutChannel(sweets::Writer & writer)
:m_writer(writer)
{}

void EventOutChannel::sendCommand(const Event & event)
throw (sweets::Exception)
{
	m_writer.write(event.toJsonString());
}

} /* namespace unfrozen */
