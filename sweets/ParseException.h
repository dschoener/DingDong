/*
 * ParseException.h
 *
 *  Created on: Dec 11, 2015
 *      Author: developer
 */

#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_

#include "Exception.h"

namespace sweets
{
/**
 * Class ParseException
 */
class ParseException: public sweets::Exception
{
public:
	ParseException(const char * what) throw ();
	ParseException(const std::string & what) throw ();
	virtual ~ParseException() throw ();
};

} /* namespace server */

#endif /* PARSEEXCEPTION_H_ */
