/*
 * GpioStateEvent.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#include <sstream>

#include "GpioStateEvent.h"

namespace unfrozen
{

const std::string GpioStateEvent::Name = "gpio-state";

GpioStateEvent::GpioStateEvent(unsigned sid, const std::string & gid,
		const std::string & state)
:GpioEvent(sid, Name, gid),
 m_state(state)
{}

std::string GpioStateEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{\"name\": \"" << Name << "\", \"params\": {"
		<< "\"sid\": " << getSessionId()
		<< ", \"gid\": \"" << getGpioId() << "\""
		<< ", \"state\": \"" << m_state << "\"}}";
	return oss.str();
}

} /* namespace unfrozen */
