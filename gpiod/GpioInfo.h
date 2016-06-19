/*
 * GpioInfo.h
 *
 *  Created on: 01.01.2016
 *      Author: denis
 */

#ifndef GPIOINFO_H_
#define GPIOINFO_H_

#include <Exception.h>
#include <PipeReader.h>

namespace gpiod
{

class GpioInfo
{
public:
	static const std::string KEY_PATH;
	static const std::string KEY_DIR;
	static const std::string KEY_EDGE;
	static const std::string KEY_SCRIPT_INIT;
	static const std::string KEY_SCRIPT_EXIT;
	static const std::string KEY_SCRIPT_EVENT;

	static const std::vector<std::string> keys;

	GpioInfo(const std::string & path);

	void setValue(const std::string & key, const std::string & value);
	void setValue(const std::string & key, const char * value);
	const std::string & getValue(const std::string & key) const throw (sweets::Exception);

	const std::string toString() const throw ();

private:
	typedef std::map<std::string, std::string> MapValues;
	MapValues mapValues;
};

} /* namespace gpiod */

#endif /* GPIOINFO_H_ */
