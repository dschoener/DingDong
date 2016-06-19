/*
 * Exception.h
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#include <string>
#include <exception>

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

namespace sweets
{

/**
 * Class Exception
 */
class Exception: public std::exception
{
protected:
	std::string msg;

public:
	Exception(const char * what) throw ();
	Exception(const std::string & what) throw ();
	virtual ~Exception() throw();

	virtual const char* what() const throw();
};

/**
 * Class ErrorException
 */
class ErrorException: public Exception
{
public:
	ErrorException(const char * what) throw();
	ErrorException(const std::string & what) throw();
	virtual ~ErrorException() throw();

	static std::string createErrorMessage(const std::string & message);
};

} /* namespace gpiod */

#endif /* EXCEPTION_H_ */
