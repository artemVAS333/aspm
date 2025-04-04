#include <iostream>
#include "test.h"
#include "tools.h"
#include <string>
#include <vector>
using namespace nlohmann;
using namespace std;

int install(json &json_obj) {
  try {
    json instaled_apps = getjson("./installed_app.json");
    if (instaled_apps.contains(json_obj["name"]) && instaled_apps[json_obj["name"]]["version"] == json_obj["version"]) {
      cout<< "already latest"<<endl;
      return 0;
    }
    string git_url = json_obj["codename"];
    string name = json_obj["name"];
    char char_array[200];
    std::strcpy(char_array, git_url.c_str());
    char path[] = "./build_bin/";
    //system("rm -rf ./build_bin/.git")
    get_git(char_array, path); 
    char command[200];
    if(json_obj["compily_process"][0] == "make"){
      snprintf(command, sizeof(command), "make -C %s build ;cp %s/build/main ./bin/%s  ;rm -rf %s* ", path,path,name.c_str(),path);
      system(command);

    }
    else {
      for( auto& el : json_obj["compily_process"]) {
        
        string eli = el;
        std::strcpy(command, eli.c_str());
        system(command);
      }
    }
    instaled_apps[json_obj["name"]] = json_obj;
    updatejson("./installed_app.json", instaled_apps);
    }
  catch(...){
    return 0;
  }
  return 1;
}
int update(){
  return 0;
}

int main() { 
  cout << "Hello, test!\n";
  json json_obj;
  json_obj["codename"] = "https://github.com/VLazorykOOP/lab2oop-24-UnknownStepan";
  json_obj["name"] = "main";
  json_obj["version"] = "3.0.0";
  std::vector<std::string> arr = {"make"};
  json_obj["compily_process"] = arr;
  install(json_obj);


  return 0;
}
