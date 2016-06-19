/*
 * Channel.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "IOException.h"

namespace sweets
{

/**
 * Class Channel
 */
class Channel
{
public:
	virtual ~Channel() {}

	virtual bool isOpen() const = 0;
	virtual void reopen() throw (IOException) = 0;
};

}

#endif /* CHANNEL_H_ */
