#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

int get_git(char *p, const char *path);
json getjson(const char *path);
json updatejson(const char *path, nlohmann::json &new_data);
int install(const json &json_obj);


#ifndef GLOBALS_H
#define GLOBALS_H

extern std::string installed_json;
extern std::string buildPath;
extern std::string updateNAME;
extern std::string binPath;
extern std::string mainPath;
extern std::string toinstall_json;
#endif
