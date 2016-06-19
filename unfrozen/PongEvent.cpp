/*
 * PongEvent.cpp
 *
 *  Created on: 27.12.2015
 *      Author: denis
 */

#include <sstream>

#include "PongEvent.h"

namespace unfrozen
{

const std::string PongEvent::Name = "pong";

PongEvent::PongEvent(unsigned sid)
:Event(sid, Name)
{}

std::string PongEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{name: \"" << Name << "\", params: {"
		<< "sid: " << getSessionId() << "}}";
	return oss.str();
}

} /* namespace unfrozen */
