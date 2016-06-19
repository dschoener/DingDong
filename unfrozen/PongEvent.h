/*
 * PongEvent.h
 *
 *  Created on: 27.12.2015
 *      Author: denis
 */

#ifndef PONGEVENT_H_
#define PONGEVENT_H_

#include <string>

#include "Event.h"

namespace unfrozen
{

class PongEvent: public Event
{
public:
	static const std::string Name;

	PongEvent(unsigned sid);

	virtual std::string toJsonString() const;
};

} /* namespace unfrozen */

#endif /* PONGEVENT_H_ */
