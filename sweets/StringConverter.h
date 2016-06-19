/*
 * StringConverter.h
 *
 *  Created on: Dec 17, 2015
 *      Author: developer
 */

#ifndef STRINGCONVERTER_H_
#define STRINGCONVERTER_H_

namespace sweets
{

class StringConverter
{
protected:
	StringConverter();

public:
	static int toInteger(const std::string & value);
};

} /* namespace sweets */

#endif /* STRINGCONVERTER_H_ */
