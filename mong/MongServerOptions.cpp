/*
 * MongServerOptions.cpp
 *
 *  Created on: 15.12.2015
 *      Author: denis
 */

#include <string.h>

#include "MongServerOptions.h"

#define SET_OPTION(IN, CSTR, OPT) if (IN != NULL) { \
	CSTR = IN; OPT = CSTR.c_str(); } else { \
		CSTR.clear(); }

namespace mong
{

MongServerOptions::MongServerOptions()
{
	clear();
}

MongServerOptions::MongServerOptions(const ServeHttpOptions & opts)
{
	setOptions(opts);
}

MongServerOptions::MongServerOptions(const MongServerOptions & opts)
{
	setOptions(opts.m_options);
}

MongServerOptions::~MongServerOptions()
{}

void MongServerOptions::setOptions(const struct mg_serve_http_opts & opts)
{
	clear();
	SET_OPTION(opts.auth_domain,              m_authDomain, m_options.auth_domain);
	SET_OPTION(opts.document_root,            m_docRoot,    m_options.document_root);
	SET_OPTION(opts.enable_directory_listing, m_dirListing, m_options.enable_directory_listing);
	SET_OPTION(opts.index_files,              m_indexFiles, m_options.index_files);
	SET_OPTION(opts.hidden_file_pattern,      m_hiddenFilePattern, m_options.hidden_file_pattern);
}

void MongServerOptions::clear()
{
	::memset(&m_options, 0, sizeof(m_options));
}

} /* namespace mong */
