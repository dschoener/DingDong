/*
 * CommandOutChannel.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef EVENTOUTCHANNEL_H_
#define EVENTOUTCHANNEL_H_

#include <Exception.h>
#include <Writer.h>

#include "Event.h"

namespace unfrozen
{

/**
 * class EventOutChannel
 */
class EventOutChannel
{
public:
	EventOutChannel(sweets::Writer & writer);

	void sendCommand(const Event & event) throw (sweets::Exception);

private:
	sweets::Writer & m_writer;
};

} /* namespace unfrozen */

#endif /* EVENTOUTCHANNEL_H_ */
