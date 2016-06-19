/*
 * File.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#ifndef FILE_H_
#define FILE_H_

#include <string>

#include "Exception.h"
#include "IOException.h"
#include "Channel.h"

namespace sweets
{

class File : public Channel
{
public:
	enum {
		FD_INVALID = -1,
		OPTIONS_INVALID = 0
	};

	enum Usage {
		FILE_READ,
		FILE_WRITE,
		FILE_RW
	};

	File(const std::string & fileName);
	virtual ~File();

	const std::string & getFileName() const { return m_fileName; }
	int getFileDescriptor() const { return m_fileDesc;  }

	virtual bool isOpen() const;
	virtual void open(Usage usage) throw (IOException);
	virtual void reopen() throw (IOException);
	virtual void close();

protected:
	virtual void open(int options) throw (IOException);

private:
	std::string m_fileName;
	int m_fileDesc;
	int m_lastOptions;
};

} /* namespace sweets */

#endif /* FILE_H_ */
