#include <iostream>

#include "app.h"
#include "input.h"

using namespace std;

void app(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cout << "No arguments\n";
		return;
	}

	input::init(argc, argv);
}