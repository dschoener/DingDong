/*
 * GpioStateRequestEvent.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#include <sstream>

#include "GpioStateRequestEvent.h"

namespace unfrozen
{

const std::string GpioStateRequestEvent::Name = "gpio-state-request";

GpioStateRequestEvent::GpioStateRequestEvent(unsigned sid, const std::string & gid)
:GpioEvent(sid, Name, gid)
{}

std::string GpioStateRequestEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{name: \"" << Name << "\", params: {"
		<< "sid: " << getSessionId() << ", gid: \"" << getGpioId() << "\"}}";
	return oss.str();
}

} /* namespace unfrozen */
