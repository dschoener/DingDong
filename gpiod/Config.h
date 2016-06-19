/*
 * Config.h
 *
 *  Created on: 02.01.2016
 *      Author: denis
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <libconfig.h++>
#include <string>

namespace gpiod
{

class Config
{
public:
	Config(const std::string & confPath);

	void load() throw (libconfig::ConfigException);

private:
	libconfig::Config m_config;
};

} /* namespace gpiod */

#endif /* CONFIG_H_ */
