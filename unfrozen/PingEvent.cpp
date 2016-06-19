/*
 * PingEvent.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <sstream>

#include "PingEvent.h"

namespace unfrozen
{

const std::string PingEvent::Name = "ping";

PingEvent::PingEvent(unsigned sid)
:Event(sid, PingEvent::Name)
{}

std::string PingEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{name: \"" << Name << "\", params: {"
		<< "sid: " << getSessionId() << "}}";
	return oss.str();
}

} /* namespace unfrozen */
