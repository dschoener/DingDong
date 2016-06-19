/*
 * JsonParser.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: developer
 */

#include <stdlib.h>
#include <sstream>

#include "JsonParser.h"
#include "frozen/frozen.h"

using namespace sweets;

namespace unfrozen
{

JsonParser::JsonParser()
:m_tokens(NULL)
{}

JsonParser::~JsonParser()
{
	clear();
}

void JsonParser::parse(const std::string & input) throw (ParseException)
{
	clear();
	m_tokens = ::parse_json2(input.c_str(), input.length());

	if (m_tokens == NULL)
		throw ParseException(input);
}

JsonToken JsonParser::find(const std::string & what,
		const std::string & appendix) const
{
	if (m_tokens == NULL)
		return JsonToken();

	std::string s(what);
	json_token * token = ::find_json_token((json_token*)m_tokens,
			s.append(appendix).c_str());

	if (token == NULL)
		return JsonToken();

	return JsonToken(token->ptr, token->len, (JsonToken::Type)token->type);
}

JsonToken JsonParser::find(const std::string & what) const
{
	return find(what, "");
}

JsonToken JsonParser::find(const std::string & what, unsigned index) const
{
	std::ostringstream oss;
	oss << "[" << index << "]";
	return find(what, oss.str());
}

void JsonParser::clear()
{
	if (m_tokens == NULL)
	{
		::free(m_tokens);
		m_tokens = NULL;
	}
}

} /* namespace server */
