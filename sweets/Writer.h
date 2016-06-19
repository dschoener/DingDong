/*
 * StringWriter.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <string>

#include "IOException.h"

namespace sweets
{
/**
 * Class Writer
 */
class Writer
{
public:
	virtual ~Writer() {}

	virtual void write(const std::string & msg) throw (IOException) = 0;
};

}

#endif /* WRITER_H_ */
