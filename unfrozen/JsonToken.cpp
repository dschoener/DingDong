/*
 * JsonToken.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: developer
 */

#include "JsonToken.h"

namespace unfrozen
{

JsonToken::JsonToken()
:m_type(JsonToken::JSON_TYPE_NULL)
{}

JsonToken::JsonToken(const JsonToken & token)
:m_type(token.m_type),
 m_value(token.m_value)
{}

JsonToken::JsonToken(const char * ptr, size_t len, Type type)
:m_type(type),
 m_value(ptr, len)
{}

}
