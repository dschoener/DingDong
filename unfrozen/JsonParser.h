/*
 * JsonParser.h
 *
 *  Created on: Dec 11, 2015
 *      Author: developer
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <vector>
#include <string>
#include <ParseException.h>

#include "JsonToken.h"

namespace unfrozen
{
/**
 * Class NotFoundException
 */
class NotFoundException : public sweets::Exception
{
public:
	NotFoundException(const std::string & what) :Exception(what) {}
};

/**
 * class JsonParser
 */
class JsonParser
{
public:
	typedef std::vector<JsonToken> TokenArray;

	JsonParser();
	virtual ~JsonParser();

	void parse(const std::string & input) throw (sweets::ParseException);
	JsonToken find(const std::string & what) const;
	JsonToken find(const std::string & what, unsigned index) const;
	void clear();

private:
	JsonToken find(const std::string & what, const std::string & appendix) const;
	void * m_tokens;
};

} /* namespace server */

#endif /* JSONPARSER_H_ */
