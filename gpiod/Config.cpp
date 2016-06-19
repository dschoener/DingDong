/*
 * Config.cpp
 *
 *  Created on: 02.01.2016
 *      Author: denis
 */

#include "Config.h"

namespace gpiod
{

Config::Config()
{
	// TODO Auto-generated constructor stub

}

void Daemon::loadConfig() throw (libconfig::ConfigException)
{
	m_logger.info("reading configuration file '%s'", configFile.c_str());

	m_config.readFile(configFile.c_str());

	workDirectory = "."; // default
	if (m_config.exists(CONF_RUN_DIRECTORY.c_str()))
	{
		const char * value = NULL;
		m_config.lookupValue(CONF_RUN_DIRECTORY.c_str(), value);
		workDirectory = value;
	}

	const libconfig::Setting & settings = m_config.lookup(CONF_GPIO.c_str());

	mapGpioInfo.clear();
	for (int i = 0; i < settings.getLength(); i++)
	{
		const libconfig::Setting & s = settings[i];
		const char * value;
		s.lookupValue(GpioInfo::KEY_PATH.c_str(), value);

		GpioInfo & gp =	mapGpioInfo.insert(
				MapGpioInfo::value_type(value, GpioInfo(value))).first->second;

		for (std::vector<std::string>::const_iterator iter = GpioInfo::keys.begin();
				iter != GpioInfo::keys.end(); iter++)
		{
			const std::string key = (*iter);
			if (key != GpioInfo::KEY_PATH && s.exists(key))
			{
				if (s.lookupValue(key, value))
				{
					gp.setValue(key, value);
				}
			}
		}

		m_logger.dbg("added new gpio info group: %s",
				gp.toString().c_str());
	}
}

} /* namespace gpiod */
