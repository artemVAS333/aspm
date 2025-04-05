// #include <iostream>

// #include "tools.h"

// #include <string>
// #include <vector>

// using namespace nlohmann;
// using namespace std;

// string updateNAME = "test1";
// char buildPath[] = "./bin/build/";
// char installed_json[] = "./public/installed_app.json";
// char binPath[] = "./bin/";

// void replaceSubstring(char *str, const char *target, const char *replacement)
// {
//   char *pos = strstr(str, target);
//   while (pos)
//   {
//     size_t len = strlen(replacement);
//     size_t target_len = strlen(target);

//     memmove(pos + len, pos + target_len, strlen(pos + target_len) + 1);
//     memcpy(pos, replacement, len);

//     pos = strstr(pos + len, target);
//   }
// }

// int install(const json &json_obj)
// {
//   try
//   {
//     char command[400];

//     json instaled_apps = getjson(installed_json);
//     cout << instaled_apps << endl;
//     cout << json_obj["name"] << endl;

//     if (instaled_apps.contains(json_obj["name"]))
//     {
//       cout << "already latest" << endl;
//       return 0;
//     }

//     string git_url = json_obj["codename"];
//     string name = json_obj["name"];
//     char char_array[200];
//     std::strcpy(char_array, git_url.c_str());

//     if (json_obj["type"] == "git")
//     {
//       get_git(char_array, buildPath);
//     }
//     else
//     {
//       snprintf(command, sizeof(command), "wget -P %s %s", buildPath, char_array);
//       system(command);
//     }

//     if (json_obj["compily_process"][0] == "make")
//     {
//       snprintf(command, sizeof(command), "make -C %s build ;cp %s/build/main %s%s  ;rm -rf %s* ", buildPath, buildPath, binPath, name.c_str(), buildPath);
//       system(command);
//     }
//     else
//     {
//       for (auto &el : json_obj["compily_process"])
//       {
//         string eli = el;
//         std::strcpy(command, eli.c_str());
//         replaceSubstring(command, "$(BBin)", buildPath);
//         replaceSubstring(command, "$(Bin)", binPath);
//         system(command);
//       }
//     }
//     if (json_obj["name"] != updateNAME)
//     {
//       instaled_apps[json_obj["name"]] = json_obj;
//       updatejson(installed_json, instaled_apps);
//     }
//   }
//   catch (const exception &e)
//   {
//     cerr << e.what();
//     return 0;
//   }
//   return 1;
// }

// int update() { return 0; }

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <json.hpp>

#include "tools.h"

using namespace std;
using namespace nlohmann;

const string updateNAME = "test1";
const string buildPath = "./bin/build/";
const string installed_json_path = "./public/installed_app.json";
const string binPath = "./bin/";

void replaceSubstring(string &str, const string &target, const string &replacement)
{
  size_t pos = 0;
  while ((pos = str.find(target, pos)) != string::npos)
  {
    str.replace(pos, target.length(), replacement);
    pos += replacement.length();
  }
}

bool fetchSource(const json &app)
{
  string source = app["codename"];
  string command;

  if (app["type"] == "git")
  {
    return get_git(source.c_str(), buildPath.c_str()) == 0;
  }

  command = "wget -P " + buildPath + " " + source;
  return system(command.c_str()) == 0;
}

bool compileApp(const json &app)
{
  string command;

  if (app["compily_process"][0] == "make")
  {
    command = "make -C " + buildPath + " build ; cp " + buildPath + "build/main " + binPath + app["name"].get<string>() + " ; rm -rf " + buildPath + "*";
    return system(command.c_str()) == 0;
  }

  for (const auto &cmd : app["compily_process"])
  {
    string cmd_str = cmd;
    replaceSubstring(cmd_str, "$(BBin)", buildPath);
    replaceSubstring(cmd_str, "$(Bin)", binPath);
    if (system(cmd_str.c_str()) != 0)
      return false;
  }

  return true;
}

int install(const json &app)
{
  try
  {
    auto installed_apps = getjson(installed_json_path.c_str());

    string app_name = app["name"];
    if (installed_apps.contains(app_name))
    {
      cout << "Already latest version of " << app_name << endl;
      return 0;
    }

    if (!fetchSource(app))
    {
      cerr << "Failed to fetch source\n";
      return 0;
    }

    if (!compileApp(app))
    {
      cerr << "Compilation failed\n";
      return 0;
    }

    if (app_name != updateNAME)
    {
      installed_apps[app_name] = app;
      updatejson(installed_json_path.c_str(), installed_apps);
    }

    cout << "Installed: " << app_name << endl;
  }
  catch (const exception &e)
  {
    cerr << "Install error: " << e.what() << endl;
    return 0;
  }

  return 1;
}

bool uninstall(const string &app_name)
{
  try
  {
    auto installed_apps = getjson(installed_json_path.c_str());
    cout << installed_apps << endl;

    if (!installed_apps.contains(app_name))
    {
      cerr << "Package \"" << app_name << "\" is not installed." << endl;
      return false;
    }

    string binary_path = binPath + app_name;
    if (remove(binary_path.c_str()) != 0)
    {
      cerr << "Failed to remove binary: " << binary_path << endl;
    }
    else
    {
      cout << "Removed binary: " << binary_path << endl;
    }

    installed_apps.erase(app_name);
    updatejson(installed_json_path.c_str(), installed_apps);

    string clean_command = "rm -rf " + buildPath + "*";
    system(clean_command.c_str());

    cout << "Uninstalled package: " << app_name << endl;
    return true;
  }
  catch (const exception &e)
  {
    cerr << "Uninstall error: " << e.what() << endl;
    return false;
  }
}

int update()
{
  return 0;
}
