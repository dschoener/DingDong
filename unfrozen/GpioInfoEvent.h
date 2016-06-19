/*
 * GpioEvent.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef GPIOINFOEVENT_H_
#define GPIOINFOEVENT_H_

#include <list>

#include "GpioEvent.h"

namespace unfrozen
{

/**
 * Class GpioInfoEvent
 */
class GpioInfoEvent: public Event
{
public:
	static const std::string Name;

	/**
	 * Class GpioInfoItem
	 */
	class GpioInfoItem
	{
	public:
		GpioInfoItem(const std::string & gid, const std::string & value);

		const std::string gid;
		const std::string value;
	};

	typedef std::list<GpioInfoItem> GpioInfoItemList;

	GpioInfoEvent(unsigned sid, const GpioInfoItemList & items);
	virtual ~GpioInfoEvent();

	const GpioInfoItemList & getInfoItems() const { return m_items; }

	virtual std::string toJsonString() const;

private:
	GpioInfoItemList m_items;
};

} /* namespace unfrozen */

#endif /* GPIOINFOEVENT_H_ */
