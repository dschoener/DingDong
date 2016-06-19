/*
 * HttpMessageContext.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef HTTPMESSAGECONTEXT_H_
#define HTTPMESSAGECONTEXT_H_

#include "ConnectionContext.h"
#include "MongTypes.h"

namespace mong
{

class HttpMessageContext: public ConnectionContext
{
public:
	HttpMessageContext(mong::Connection & conn, mong::HttpMessage & msg);
	virtual ~HttpMessageContext();

	mong::HttpMessage & getHttpMessage() { return m_httpMessage; }

private:
	mong::HttpMessage & m_httpMessage;
};

} /* namespace mong */

#endif /* HTTPMESSAGECONTEXT_H_ */
