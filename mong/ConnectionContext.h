/*
 * ConnectionContext.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "MongTypes.h"

#ifndef CONNECTIONCONTEXT_H_
#define CONNECTIONCONTEXT_H_

namespace mong
{

class ConnectionContext
{
public:
	ConnectionContext(mong::Connection & conn);
	virtual ~ConnectionContext();

	mong::Connection & getConnection() { return m_connection; }

private:
	mong::Connection & m_connection;
};

} /* namespace mong */

#endif /* CONNECTIONCONTEXT_H_ */
