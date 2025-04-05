#include <string>
#include <unordered_map>
#include <iomanip>

#include "app.h"

using namespace std;
using namespace nlohmann;

typedef enum
{
	CMD_UNKNOWN,
	CMD_INSTALL,
	CMD_DELETE,
	CMD_LIST,
	CMD_HELP
} Command;

unordered_map<string, Command> commandMap = {
	{"-i", CMD_INSTALL},
	{"--install", CMD_INSTALL},
	{"-d", CMD_DELETE},
	{"--delete", CMD_DELETE},
	{"-l", CMD_LIST},
	{"--list", CMD_LIST},
	{"--help", CMD_HELP}};

App::App(int argc, char *argv[]) : argc(argc), argv(argv) {}

void App::run() { initArguments(); }

void printHelp(const json &json_obj)
{
	cout << "Available commands:\n";

	cout << left << setw(20) << "--install, -i" << ": Install a package\n";
	cout << left << setw(20) << "--list, -l" << ": List available packages\n";
	cout << left << setw(20) << "--help" << ": Show this help message\n";

	for (auto &[key, value] : json_obj.items())
		cout << left << setw(20) << key << ": " << value << endl;
}

void App::initArguments()
{
	json json_obj = getjson("public/packages/manifest.json");

	if (argc <= 1)
	{
		printHelp(json_obj);
		return;
	}

	try
	{
		parseArguments(json_obj);
	}
	catch (const exception &e)
	{
		cerr << "Error loading JSON: " << e.what() << endl;
	}
}

void App::parseArguments(const json &json_obj)
{
	Command currentCommand = CMD_UNKNOWN;

	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];

		if (commandMap.contains(arg))
		{
			currentCommand = commandMap[arg];

			if (currentCommand == CMD_HELP)
			{
				printHelp(json_obj);
				return;
			}
			else if (currentCommand == CMD_LIST)
			{
				cout << "Available packages:\n";
				for (auto &[key, value] : json_obj.items())
					cout << key << ": " << value << endl;
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
				cout << ": " << json_obj[arg] << " - installing " << endl;
				if (install(json_obj[arg]))
					cout << "installed";
			}
			else
			{
				cout << ": [Key not found]";
			}
		}
		cout << endl;
	}
}
