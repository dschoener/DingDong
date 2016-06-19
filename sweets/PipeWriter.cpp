/*
 * PipeWriter.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "PipeWriter.h"

namespace sweets
{

PipeWriter::PipeWriter(const std::string & fileName)
:File(fileName)
{}

void PipeWriter::write(const std::string & msg) throw (IOException)
{
	ssize_t wcount = 0;
	const char * buf = msg.c_str();
	size_t written = 0;
	size_t len = msg.length();

	while ((wcount = ::write(getFileDescriptor(), buf, len - written)) > 0)
	{
		buf += wcount;
		written += wcount;
	}

	if (wcount < 0)
	{
		if ((wcount != (-EAGAIN)) && (wcount != (-EWOULDBLOCK)))
		{
			// error
			throw IOException(ErrorException::createErrorMessage(
					"failed to write to pipe"));
		}
	}
}

void PipeWriter::open() throw (ErrorException)
{
	File::open(O_ASYNC | O_NONBLOCK | O_WRONLY);
}

} /* namespace sweets */
