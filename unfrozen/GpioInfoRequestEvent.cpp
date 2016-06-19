/*
 * GpioInfoRequestEvent.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#include <sstream>

#include "GpioInfoRequestEvent.h"

namespace unfrozen
{

const std::string GpioInfoRequestEvent::Name = "gpio-info-request";

GpioInfoRequestEvent::GpioInfoRequestEvent(unsigned sid)
:Event(sid, Name)
{}

std::string GpioInfoRequestEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{\"name\": \"" << Name << "\", \"params\": {"
		<< "\"sid\": " << getSessionId() << "}}";
	return oss.str();
}

} /* namespace unfrozen */
