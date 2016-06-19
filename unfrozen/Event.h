/*
 * Command.h
 *
 *  Created on: Dec 14, 2015
 *      Author: developer
 */

#include <string>
#include <Exception.h>

#ifndef COMMAND_H_
#define COMMAND_H_

namespace unfrozen
{

/**
 * Class Command
 */
class Event
{
public:
	enum {
		ID_INVALID = -1
	};

protected:
	Event(unsigned id, const std::string & name);

public:
	virtual ~Event();

	const std::string & getName() const { return m_name; }
	unsigned getSessionId() const { return m_id; }

	bool operator == (const std::string & s) const { return (m_name == s); }

	virtual std::string toJsonString() const { return std::string(""); };

private:
	static unsigned getNextId();
	static unsigned s_id;

	std::string m_name;
	unsigned m_id;
};

} /* namespace unfrozen */

#endif /* COMMAND_H_ */
