#pragma once
#include <tools.h>
#include "globals.h"
using json = nlohmann::json;

namespace input
{
	void init(int argc, char *argv[]);
	void parseArguments(int argc, char *argv[], const json &json_obj);
}
typedef enum
{
	CMD_UNKNOWN,
	CMD_INSTALL,
	CMD_LIST,
	CMD_HELP
} Command;

