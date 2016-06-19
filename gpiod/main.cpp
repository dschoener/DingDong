/*
 * main.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: developer
 */

#include <exception>
#include <sstream>
#include <signal.h>

#include "Daemon.h"
#include <Option.h>
#include <Logger.h>

using namespace gpiod;
using namespace logger;
using namespace sweets;

static Daemon * g_daemon = NULL;

void sighandler(int sig)
{
	switch(sig)
	{
	case SIGTERM:
		g_daemon->stop();
		break;
	case SIGHUP:
		g_daemon->reset();
		break;
	}
}

int main(int argc, char * argv[])
{
	sweets::Option options;
	options.addOption('v');
	options.addOption('d');
	options.addOption('c', true);

	signal(SIGHUP, sighandler);
	signal(SIGTERM, sighandler);

	Daemon daemon;
	g_daemon = &daemon;

	try
	{
		options.parse(argc, argv);

		if (options.getOption('v').isEnabled())
		{
			LoggerManager::getLogger("gpiod").setLevel(LEVEL_DBG);
		}

		daemon.setConfigFile(options.getOption('c').getArgument());

		if (!options.getOption('d').isEnabled())
			daemon.runDaemonized();
		else
			daemon.run();
	}
	catch(std::exception &e)
	{
		LoggerManager::getLogger("gpiod").err("%s", e.what());
		return 1;
	}

	return 0;
}

