/*
 * GpioEvent.cpp
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#include "GpioEvent.h"

namespace unfrozen
{

GpioEvent::GpioEvent(unsigned sid, const std::string & name,
		const std::string & gid)
:Event(sid, name),
 m_gpioId(gid)
{}

} /* namespace unfrozen */
