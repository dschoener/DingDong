/*
 * Types.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include "mongoose.h"

#ifndef TYPES_H_
#define TYPES_H_

namespace mong
{
typedef struct http_message HttpMessage;
typedef struct websocket_message WebsocketMessage;
typedef struct mg_rpc_request RpcRequest;
typedef struct mg_connection Connection;
typedef struct mg_serve_http_opts ServeHttpOptions;
}

#endif /* TYPES_H_ */
