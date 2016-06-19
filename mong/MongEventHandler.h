/*
 * RpcHandler.h
 *
 *  Created on: Dec 8, 2015
 *      Author: developer
 */

#include <vector>
#include <string>
#include "mongoose.h"
#include "HttpMessageContext.h"
#include "WebsocketMessageContext.h"

#ifndef RPCHANDLER_H_
#define RPCHANDLER_H_

namespace mong
{

/**
 * Class MongEventHandler
 */
class MongEventHandler
{
public:
	MongEventHandler();
	virtual ~MongEventHandler();

	typedef std::vector<std::string> RpcFunctionNames;

	virtual const std::string & handleRpcRequest(
			const mong::RpcRequest & request) = 0;
	virtual void onWebsocketNew(const mong::Connection & connecton) {}
	virtual void onWebsocketClosed(const mong::Connection & connecton) {}
	virtual void onWebsocketMessage(const WebsocketMessageContext & context) {}
	virtual void onIdle(time_t now) {}
};

} /* namespace server */

#endif /* RPCHANDLER_H_ */
