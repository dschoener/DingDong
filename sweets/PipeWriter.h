/*
 * PipeWriter.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#ifndef PIPEWRITER_H_
#define PIPEWRITER_H_

#include "File.h"
#include "Writer.h"

namespace sweets
{

class PipeWriter: public File, public Writer
{
public:
	PipeWriter(const std::string & fileName);

	virtual void write(const std::string & msg) throw (sweets::IOException);
	virtual void open() throw (sweets::ErrorException);
};

} /* namespace sweets */

#endif /* PIPEWRITER_H_ */
