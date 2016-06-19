/*
 * StringConverter.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: developer
 */

#include <string>

#include "StringConverter.h"

namespace sweets
{

StringConverter::StringConverter()
{}

int StringConverter::toInteger(const std::string & value)
{
	return std::stoi(value.c_str());
}
} /* namespace sweets */
