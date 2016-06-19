/*
 * ConnectionContext.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "ConnectionContext.h"

namespace mong
{

ConnectionContext::ConnectionContext(mong::Connection & conn)
:m_connection(conn)
{}

ConnectionContext::~ConnectionContext()
{}

} /* namespace mong */
