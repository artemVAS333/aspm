#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "json.hpp"

using json = nlohmann::json;

int get_git(char *p, char *path);
json getjson(char *path);
json updatejson(char *path, nlohmann::json &new_data);
