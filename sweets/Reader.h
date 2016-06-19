/*
 * Reader.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef READER_H_
#define READER_H_

#include <string>

#include "IOException.h"

namespace sweets
{

/**
 * Class Reader
 */
class Reader
{
public:
	virtual ~Reader() {}

	virtual const std::string & read() throw (IOException) = 0;
};

}

#endif /* READER_H_ */
