/*
 * GpioEvent.h
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#ifndef GPIOEVENT_H_
#define GPIOEVENT_H_

#include <string>
#include "Event.h"

namespace unfrozen
{

class GpioEvent: public Event
{
public:
	GpioEvent(unsigned sid, const std::string & name, const std::string & gid);

	const std::string & getGpioId() const { return m_gpioId; }

private:
	std::string m_gpioId;
};

} /* namespace unfrozen */

#endif /* GPIOEVENT_H_ */
