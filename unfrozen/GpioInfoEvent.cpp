/*
 * GpioEvent.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include <sstream>

#include "GpioInfoEvent.h"

namespace unfrozen
{

const std::string GpioInfoEvent::Name = "gpio-info";

GpioInfoEvent::GpioInfoItem::GpioInfoItem(const std::string & _gid,
	const std::string & _value)
:gid(_gid),
 value(_value)
{}

GpioInfoEvent::GpioInfoEvent(unsigned sid, const GpioInfoItemList & items)
:Event(sid, Name),
 m_items(items)
{}

GpioInfoEvent::~GpioInfoEvent()
{}

std::string GpioInfoEvent::toJsonString() const
{
	std::ostringstream oss;
	oss << "{\"name\": \"" << Name << "\", \"params\": {"
		<< "\"sid\": " << getSessionId()
		<< ", \"items\": [";
	for (GpioInfoItemList::const_iterator iter = m_items.begin();
		iter != m_items.end(); iter++)
	{
		oss << ((iter == m_items.begin()) ? "" : ", ") << "{\"gid\": \""
			<< (*iter).gid << "\", \"state\": \"" << (*iter).value << "\"}";
	}
	oss << "]}}";
	return oss.str();
}

} /* namespace unfrozen */
