#include <iostream>

#include "tools.h"
#include "input.h"

#include <string>
#include <vector>

using namespace nlohmann;
using namespace std;

string updateNAME = "test1";
char buildPath[] = "./bin/build/";
char installed_json[] = "./public/installed_packages.json";
char binPath[] = "./bin/";

void replaceSubstring(char *str, const char *target, const char *replacement)
{
  char *pos = strstr(str, target);
  while (pos)
  {
    int len = strlen(replacement);
    int target_len = strlen(target);

    memmove(pos + len, pos + target_len, strlen(pos + target_len) + 1);
    memcpy(pos, replacement, len);

    pos = strstr(pos + len, target);
  }
}

int install(const json &json_obj)
{
  try
  {
    char command[400];

    json instaled_apps = getjson(installed_json);
    cout << instaled_apps << endl
         << json_obj["name"] << endl;
    if (instaled_apps.contains(json_obj["name"]))
    {
      cout << "already latest" << endl;
      return 0;
    }

    string git_url = json_obj["codename"];
    string name = json_obj["name"];
    char char_array[200];
    std::strcpy(char_array, git_url.c_str());

    if (json_obj["type"] == "git")
    {
      get_git(char_array, buildPath);
    }
    else
    {
      snprintf(command, sizeof(command), "wget -P %s %s", buildPath, char_array);
      system(command);
    }

    if (json_obj["compily_process"][0] == "make")
    {
      snprintf(command, sizeof(command), "make -C %s build ;cp %s/build/main %s%s  ;rm -rf %s* ", buildPath, buildPath, binPath, name.c_str(), buildPath);
      system(command);
    }
    else
    {
      for (auto &el : json_obj["compily_process"])
      {
        string eli = el;
        std::strcpy(command, eli.c_str());
        replaceSubstring(command, "$(BBin)", buildPath);
        replaceSubstring(command, "$(Bin)", binPath);
        system(command);
      }
    }
    if (json_obj["name"] != updateNAME)
    {
      instaled_apps[json_obj["name"]] = json_obj;
      updatejson(installed_json, instaled_apps);
    }
  }
  catch (const exception &e)
  {
    cerr << e.what();
    return 0;
  }
  return 1;
}

int delete_app(const json &json_obj)
{
  try
  {
    json instaled_apps = getjson(installed_json);
    instaled_apps.erase(json_obj["name"]);
    updatejson(installed_json, instaled_apps);
  }
  catch (const exception &e)
  {
    cerr << e.what();
    return 0;
  }
  return 1;
}

int update() { return 0; }