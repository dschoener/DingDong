/*
 * HttpMessageContext.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "HttpMessageContext.h"

namespace mong
{

HttpMessageContext::HttpMessageContext(mong::Connection & conn,
		mong::HttpMessage & msg)
:ConnectionContext(conn),
 m_httpMessage(msg)
{}

HttpMessageContext::~HttpMessageContext()
{}

} /* namespace mong */
