#include <iostream>

#include "tools.h"
#include "input.h"

#include <string>
#include <vector>
#include <cstring>

using namespace nlohmann;
using namespace std;

string updateNAME  = "test1";


string buildPath = mainPath + "./build/";
string installed_json = mainPath + "./public/installed_app.json";
string binPath = mainPath + "./bin/";

void replaceSubstring(char* str, const char* target, const char* replacement) {
    char* pos = strstr(str, target);
    while (pos) {
        int len = strlen(replacement);
        int target_len = strlen(target);

        memmove(pos + len, pos + target_len, strlen(pos + target_len) + 1);

        memcpy(pos, replacement, len);
      
        pos = strstr(pos + len, target);
    }
}


int install(const json &json_obj) {
  try {
    char command[400];
        
    json instaled_apps = getjson(installed_json.c_str());
    cout << instaled_apps << endl<< json_obj["name"]<<endl;
    if (instaled_apps.contains(json_obj["name"])) {
       cout<< "already latest"<<endl;
       return 0;
     }
    
    string git_url = json_obj["codename"];
    string name = json_obj["name"];
    char char_array[200];
    std::strcpy(char_array, git_url.c_str());
    
    
    if(json_obj["type"] == "git"){
      get_git(char_array, buildPath.data());
    }else{
      snprintf(command, sizeof(command), "wget -P %s %s", buildPath.data(), char_array);
      
      system(command);
    }
    
    if(json_obj["compily_process"][0] == "make"){
      snprintf(command, sizeof(command), "make -C %s build ;cp %s/build/main %s%s  ;rm -rf %s* ", buildPath.c_str(), buildPath.c_str(),binPath.c_str(),name.c_str(), buildPath.c_str());
      system(command);
    }
    else {
      for( auto& el : json_obj["compily_process"]) {
        string eli = el;
        std::strcpy(command, eli.c_str());
        replaceSubstring(command, "$(BBin)", buildPath.c_str());
        replaceSubstring(command, "$(Bin)", binPath.c_str());
        replaceSubstring(command, "$(Home)", mainPath.c_str());
        system(command);
      }
    }
    if (json_obj["name"] != updateNAME) {
      instaled_apps[json_obj["name"]] = json_obj;
      updatejson(installed_json.c_str(), instaled_apps);

    }
   }
  catch(const exception &e){
    cerr << e.what();
    return 0;
  }
  return 1;
}
int update(){
  return 0;
}

// int main() { 
//   cout << "Hello, test!\n";
//   json json_obj;
//   json_obj["codename"] = "https://github.com/VLazorykOOP/lab2oop-24-UnknownStepan";
//   json_obj["name"] = "main";
//   json_obj["version"] = "3.0.0";
//   std::vector<std::string> arr = {"echo \"loser\""};
//   json_obj["compily_process"] = arr;
//   Command r = CMD_LIST;
//   json_obj["name"] = to_string(r);
//
//   install(json_obj);
//
//
//   return 0;
// }
