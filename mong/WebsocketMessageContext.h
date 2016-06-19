/*
 * WebsocketMessageContext.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef WEBSOCKETMESSAGECONTEXT_H_
#define WEBSOCKETMESSAGECONTEXT_H_

#include "ConnectionContext.h"

namespace mong
{

class WebsocketMessageContext: public ConnectionContext
{
public:
	WebsocketMessageContext(mong::Connection & conn,
			mong::WebsocketMessage & msg);
	virtual ~WebsocketMessageContext();

	mong::WebsocketMessage & getWebsocketMessage() { return m_wsockMessage; }

private:
	mong::WebsocketMessage & m_wsockMessage;
};

} /* namespace mong */

#endif /* WEBSOCKETMESSAGECONTEXT_H_ */
