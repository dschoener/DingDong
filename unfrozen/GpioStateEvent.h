/*
 * GpioStateEvent.h
 *
 *  Created on: Dec 26, 2015
 *      Author: developer
 */

#ifndef GPIOSTATEEVENT_H_
#define GPIOSTATEEVENT_H_

#include <string>
#include "GpioEvent.h"

namespace unfrozen
{

class GpioStateEvent: public GpioEvent
{
public:
	static const std::string Name;

	GpioStateEvent(unsigned sid, const std::string & gid,
		const std::string & state);

	const std::string & getState() const { return m_state; }
	virtual std::string toJsonString() const;

private:
	std::string m_state;
};

} /* namespace unfrozen */

#endif /* GPIOSTATEEVENT_H_ */
