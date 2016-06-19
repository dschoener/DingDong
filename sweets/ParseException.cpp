/*
 * ParseException.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: developer
 */

#include "ParseException.h"

namespace sweets
{

ParseException::ParseException(const char * what) throw ()
:Exception(what)
{}

ParseException::ParseException(const std::string & what) throw ()
:Exception(what)
{}

ParseException::~ParseException() throw ()
{}

} /* namespace server */
