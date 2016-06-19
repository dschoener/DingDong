/*
 * GpioStateRequestEvent.h
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#ifndef GPIOSTATEREQUESTEVENT_H_
#define GPIOSTATEREQUESTEVENT_H_

#include <string>
#include "GpioEvent.h"

namespace unfrozen
{

class GpioStateRequestEvent: public GpioEvent
{
public:
	static const std::string Name;

	GpioStateRequestEvent(unsigned sid, const std::string & gid);

	virtual std::string toJsonString() const;
};

} /* namespace unfrozen */

#endif /* GPIOSTATEREQUESTEVENT_H_ */
