/*
 * PipeReader.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#ifndef PIPEREADER_H_
#define PIPEREADER_H_

#include "File.h"
#include "IOException.h"
#include "Reader.h"

namespace sweets
{

class PipeReader: public File, public Reader
{
public:
	enum {
		SIZE_MAX_READ_BUF = 2048
	};

	PipeReader(const std::string & fileName);

	virtual const std::string & read() throw (IOException);
	virtual void open() throw (sweets::ErrorException);

private:
	std::string m_readBuffer;
};

} /* namespace sweets */

#endif /* PIPEREADER_H_ */
