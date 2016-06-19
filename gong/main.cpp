/*
 * main.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: developer
 */

#include <MongEventHandler.h>
#include <Option.h>
#include <signal.h>
#include <iostream>

#include "GongServer.h"

using namespace gong;
using namespace mong;
using namespace logger;
using namespace sweets;

static GongServer * g_gong = 0;

void sighandler(int sig)
{
	switch(sig)
	{
	case SIGTERM:
		g_gong->stop();
		break;
	}
}

int main(int argc, char * argv[])
{
	Option options;
	options.addOption('c', true);
	options.addOption('v');

	try
	{
		options.parse(argc, argv);

		if (options.getOption('v').isEnabled())
		{
			LoggerManager::getLogger("gong").setLevel(LEVEL_DBG);
		}

		GongServer gong;
		g_gong = &gong;

		if (options.getOption('c').hasArgument())
		{
			gong.loadConfig(options.getOption('c').getArgument());
		}

		signal(SIGTERM, sighandler);
		gong.start();
	}
	catch(Exception & e)
	{
		LoggerManager::getLogger("gong").err(e.what());
		return 1;
	}

	return 0;
}


