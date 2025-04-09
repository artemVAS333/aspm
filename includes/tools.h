#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "json.hpp"
#include "globals.h"

using json = nlohmann::json;

int get_git(char *p, const char *path);
json getjson(const char *path);
json updatejson(const char *path, nlohmann::json &new_data);
int install(const json &json_obj);

