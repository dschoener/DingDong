/*
 * JsonToken.h
 *
 *  Created on: Dec 17, 2015
 *      Author: developer
 */

#ifndef JSONTOKEN_H_
#define JSONTOKEN_H_

#include <string>

namespace unfrozen
{

/**
 * Class JsonToken
 */
class JsonToken
{
public:
	enum Type {
	  JSON_TYPE_EOF     = 0,      /* End of parsed tokens marker */
	  JSON_TYPE_STRING  = 1,
	  JSON_TYPE_NUMBER  = 2,
	  JSON_TYPE_OBJECT  = 3,
	  JSON_TYPE_TRUE    = 4,
	  JSON_TYPE_FALSE   = 5,
	  JSON_TYPE_NULL    = 6,
	  JSON_TYPE_ARRAY   = 7
	};

	JsonToken();
	JsonToken(const JsonToken & token);
	JsonToken(const char * ptr, size_t len, Type type);

	const std::string & getValue() const { return m_value; }
	Type getType() const { return m_type; }

	bool operator == (const std::string & s) const { return (m_value == s); }

private:
	Type m_type;
	std::string m_value;
};

}
#endif /* JSONTOKEN_H_ */
