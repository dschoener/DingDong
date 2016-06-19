/*
 * WebsocketMessageContext.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "WebsocketMessageContext.h"

namespace mong
{

WebsocketMessageContext::WebsocketMessageContext(mong::Connection & conn,
		mong::WebsocketMessage & msg)
:ConnectionContext(conn),
 m_wsockMessage(msg)
{}

WebsocketMessageContext::~WebsocketMessageContext()
{}

} /* namespace mong */
