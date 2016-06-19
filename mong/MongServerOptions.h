/*
 * MongServerOptions.h
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#ifndef MONGSERVEROPTIONS_H_
#define MONGSERVEROPTIONS_H_

#include <string>
#include "MongTypes.h"

namespace mong
{
/**
 * Class MongServerOptions
 */
class MongServerOptions
{
public:
	MongServerOptions();
	MongServerOptions(const ServeHttpOptions & opts);
	MongServerOptions(const MongServerOptions & opts);
	virtual ~MongServerOptions();

	void setOptions(const ServeHttpOptions & opts);
	const struct mg_serve_http_opts & getOptions() { return m_options; }
	void clear();

	void operator = (const ServeHttpOptions & o) { setOptions(o); }
	void operator = (const MongServerOptions & o) { setOptions(o.m_options); }
	operator const struct mg_serve_http_opts & () { return getOptions(); }

private:
	ServeHttpOptions m_options;
	std::string m_authDomain;
	std::string m_docRoot;
	std::string m_dirListing;
	std::string m_indexFiles;
	std::string m_hiddenFilePattern;
};

} /* namespace mong */

#endif /* MONGSERVEROPTIONS_H_ */
