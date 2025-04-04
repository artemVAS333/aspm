#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

int get_git(char *p, char *path);
json getjson(const char *path);
json updatejson(char *path, nlohmann::json &new_data);
int install(const json &json_obj);
int delete_app(const json &json_obj);

#ifndef GLOBALS_H
#define GLOBALS_H

extern char installed_json[];
extern char buildPath[];
extern std::string updateNAME;
extern char binPath[];

#endif
