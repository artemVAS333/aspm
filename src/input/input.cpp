#include "input.h"

#include <iostream>
using namespace std;

namespace input
{
	void init(int argc, char *argv[]);
}

void input::init(int argc, char *argv[])
{
	if (argc > 1)
		for (int i = 1; i < argc; i++)
			cout << argv[i] << endl;
}
