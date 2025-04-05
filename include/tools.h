#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "json.hpp"

using namespace nlohmann;

int get_git(const char *p, const char *path);
json getjson(const char *path);
json updatejson(const char *path, json &new_data);
int install(const json &json_obj);
bool uninstall(const std::string &app_name);

#ifndef GLOBALS_H
#define GLOBALS_H

// extern char installed_json[];
// extern char buildPath[];
// extern std::string updateNAME;
// extern char binPath[];

#endif
