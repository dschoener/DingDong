/*
 * GpioInfo.cpp
 *
 *  Created on: 01.01.2016
 *      Author: denis
 */

#include "GpioInfo.h"

namespace gpiod
{

const std::string GpioInfo::KEY_PATH("path");
const std::string GpioInfo::KEY_DIR("direction");
const std::string GpioInfo::KEY_EDGE("edge");
const std::string GpioInfo::KEY_SCRIPT_EVENT("event_handler");

const std::vector<std::string> GpioInfo::keys = { KEY_PATH,
		KEY_DIR, KEY_EDGE, KEY_SCRIPT_EVENT };

GpioInfo::GpioInfo(const std::string & path)
{
	for (std::vector<std::string>::const_iterator iter = keys.begin();
			iter != keys.end(); iter++)
	{
		std::string key = (*iter);
		mapValues.insert(MapValues::value_type(key, std::string("")));
	}

	setValue(KEY_PATH, path);
	setValue(KEY_DIR, std::string("out"));
	setValue(KEY_EDGE, std::string("none"));
}

void GpioInfo::setValue(const std::string & key, const char * value)
{
	mapValues[key] = value;
}

void GpioInfo::setValue(const std::string & key, const std::string & value)
{
	mapValues[key] = value;
}

const std::string & GpioInfo::getValue(const std::string & id) const
throw (sweets::Exception)
{
	MapValues::const_iterator iter = mapValues.find(id);
	if (iter == mapValues.end())
		throw sweets::Exception(std::string("value not found: ") + id);

	return (*iter).second;
}

const std::string GpioInfo::toString() const throw ()
{
	bool isFirst = true;
	std::ostringstream oss;
	for (MapValues::const_iterator iter = mapValues.begin();
			iter != mapValues.end(); iter++)
	{
		std::string key = (*iter).first;
		std::string val = (*iter).second;
		if (!isFirst)
			oss << ", ";
		else
			isFirst = false;
		oss << key << "=" << val;
	}
	return oss.str();
}

} /* namespace gpiod */
