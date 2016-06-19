/*
 * Exception.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#include "Exception.h"
#include <errno.h>
#include <string.h>

namespace sweets
{

// ==================================================================== //
// Exception
// ==================================================================== //

Exception::Exception(const char * what) throw()
:msg(what)
{}

Exception::Exception(const std::string & what) throw()
:msg(what.c_str())
{}

Exception::~Exception() throw()
{}

const char * Exception::what() const throw ()
{
	return msg.c_str();
}

// ==================================================================== //
// ErrorException
// ==================================================================== //

ErrorException::ErrorException(const char * what) throw()
: Exception(what)
{
	msg = createErrorMessage(what);
}

ErrorException::ErrorException(const std::string & what) throw()
: Exception(what)
{
	msg = createErrorMessage(what);
}

ErrorException::~ErrorException() throw()
{}

std::string ErrorException::createErrorMessage(const std::string & message)
{
	std::string s(message);
	return s.append(" (").append(strerror(errno)).append(")");
}

} /* namespace gpiod */
