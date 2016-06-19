/*
 * GpioInfoRequestEvent.h
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#ifndef GPIOINFOREQUESTEVENT_H_
#define GPIOINFOREQUESTEVENT_H_

#include <string>
#include "Event.h"

namespace unfrozen
{

class GpioInfoRequestEvent: public Event
{
public:
	static const std::string Name;

	GpioInfoRequestEvent(unsigned sid);

	virtual std::string toJsonString() const;
};

} /* namespace unfrozen */

#endif /* GPIOINFOREQUESTEVENT_H_ */
