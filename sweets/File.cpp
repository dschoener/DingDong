/*
 * File.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>

#include "File.h"

namespace sweets
{

File::File(const std::string & fileName)
:m_fileName(fileName),
 m_fileDesc(FD_INVALID),
 m_lastOptions(OPTIONS_INVALID)
{}

File::~File()
{
	close();
}

bool File::isOpen() const
{
	return (m_fileDesc != FD_INVALID);
}

void File::open(Usage usage) throw (IOException)
{
	switch (usage)
	{
	case FILE_WRITE:
		open(O_WRONLY);
		break;
	case FILE_RW:
		open(O_RDWR);
		break;
	default:
		open(O_RDONLY);
		break;
	}
}

void File::reopen() throw (IOException)
{
	if (isOpen())
		close();

	open(m_lastOptions);
}

void File::open(int options) throw (IOException)
{
	if (isOpen())
		close();

	m_fileDesc = ::open(m_fileName.c_str(), options);

	if (m_fileDesc < 0)
	{
		m_fileDesc = FD_INVALID;
		std::ostringstream oss;
		oss << "failed to open pipe '" << m_fileName << "' (" << errno << ")";
		throw IOException(oss.str());
	}

	m_lastOptions = options;
}

void File::close()
{
	if (m_fileDesc != FD_INVALID)
	{
		::close(m_fileDesc);
		m_fileDesc = FD_INVALID;
	}
}

} /* namespace sweets */
