#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "json.hpp"

int get_git(char* p, char* path);
nlohmann::json getjson(char *path);
nlohmann::json updatejson(char *path, nlohmann::json &new_data);
