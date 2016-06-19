/*
 * PipeReader.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "PipeReader.h"

namespace sweets
{

PipeReader::PipeReader(const std::string & fileName)
:File(fileName)
{}

const std::string & PipeReader::read() throw (IOException)
{
	char buf[SIZE_MAX_READ_BUF];
	ssize_t rcount = 0;
	m_readBuffer.clear();
	m_readBuffer.reserve(SIZE_MAX_READ_BUF);

	while ((rcount = ::read(getFileDescriptor(), buf, sizeof(buf))) > 0)
	{
		m_readBuffer.append(buf, rcount);
	}

	if (rcount < 0)
	{
		if ((rcount != (-EAGAIN)) && (rcount != (-EWOULDBLOCK)))
		{
			// error
			throw IOException(ErrorException::createErrorMessage(
					"failed to read from pipe"));
		}
	}

	return m_readBuffer;
}

void PipeReader::open() throw (sweets::ErrorException)
{
	File::open(O_ASYNC | O_NONBLOCK | O_RDONLY);
}

} /* namespace sweets */
