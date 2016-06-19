/*
 * Command.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include "Event.h"

#include "JsonParser.h"

namespace unfrozen
{
unsigned Event::s_id = 0;

unsigned Event::getNextId()
{
	s_id++;
	return s_id;
}

Event::Event(unsigned id, const std::string & name)
:m_name(name),
 m_id(id)
{}

Event::~Event()
{}

} /* namespace unfrozen */
