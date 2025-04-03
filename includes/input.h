#pragma once
#include <tools.h>

using json = nlohmann::json;

namespace input
{
	void init(int argc, char *argv[]);
	void parseArguments(int argc, char *argv[], const json &json_obj);
}