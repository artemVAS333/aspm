#pragma once

#include <iostream>

#include "tools.h"

using namespace nlohmann;

class App
{
private:
	int argc;
	char **argv;

public:
	App();
	App(int argc, char *argv[]);

	void run();

	void initArguments();
	void parseArguments(const json &json_obj);
};