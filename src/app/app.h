#pragma once

class App
{
private:
	int argc;
	char **argv;

public:
	App(int argc, char *argv[]);
	void run();
};
