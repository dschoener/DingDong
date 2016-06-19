/*
 * IOException.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef IOEXCEPTION_H_
#define IOEXCEPTION_H_

#include "Exception.h"

namespace sweets
{

/**
 * Class IOException
 */
class IOException: public sweets::Exception
{
public:
	IOException(const std::string & what) :Exception(what) {}
	virtual ~IOException() {}
};

} /* namespace unfrozen */

#endif /* IOEXCEPTION_H_ */
