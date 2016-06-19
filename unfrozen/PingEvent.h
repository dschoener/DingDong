/*
 * PingEvent.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <string>

#include "Event.h"

#ifndef PINGCOMMAND_H_
#define PINGCOMMAND_H_

namespace unfrozen
{

class PingEvent: public Event
{
public:
	static const std::string Name;

	PingEvent(unsigned sid);

	virtual std::string toJsonString() const;
};

} /* namespace unfrozen */

#endif /* PINGCOMMAND_H_ */
