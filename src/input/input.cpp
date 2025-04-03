#include <iostream>
#include <string>
#include <unordered_map>

#include "input.h"

using namespace std;
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
	CMD_LIST
} Command;

unordered_map<string, Command> commandMap = {
	{"-i", CMD_INSTALL},
	{"--install", CMD_INSTALL},
	{"-l", CMD_LIST},
	{"--list", CMD_LIST}};

void input::init(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cerr << "No arguments provided.\n";
		return;
	}

	try
	{
		json json_obj = getjson("test/test.json");
		parseArguments(argc, argv, json_obj);
	}
	catch (const exception &e)
	{
		cerr << "Error loading JSON: " << e.what() << endl;
	}
}

void input::parseArguments(int argc, char *argv[], const json &json_obj)
{
	Command currentCommand = CMD_UNKNOWN;

	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];

		if (commandMap.find(arg) != commandMap.end())
		{
			currentCommand = commandMap[arg];
			if (currentCommand == CMD_LIST)
			{
				cout << "Available packages:\n";
				for (auto &[key, value] : json_obj.items())
				{
					cout << key << ": " << value << endl;
				}
				return;
			}
			continue;
		}

		if (currentCommand == CMD_UNKNOWN)
		{
			cerr << "Unknown command: " << arg << endl;
			return;
		}

		cout << arg;

		if (currentCommand == CMD_INSTALL)
		{
			if (json_obj.contains(arg))
			{
				cout << ": " << json_obj[arg];
			}
			else
			{
				cout << ": [Key not found]";
			}
		}
		cout << endl;
	}
}
