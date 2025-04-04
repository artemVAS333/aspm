#include <iostream>

#include "app.h"
#include "input.h"

using namespace std;

App::App(int argc, char *argv[]) : argc(argc), argv(argv) {}

void App::run() { input::init(argc, argv); }