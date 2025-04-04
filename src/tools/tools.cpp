#include <iostream>

#include "tools.h"
#include "input.h"

#include <string>
#include <vector>


using namespace nlohmann;
using namespace std;

int install(json &json_obj) {
  try {
    char command[400];
    char app_js[] = "./public/installed_app.json"; 
    char path[] = "./build_bin/";
    cout << "compile"<<endl;
    json instaled_apps = getjson(app_js);
    cout << instaled_apps << endl<< json_obj["name"]<<endl;
    if (instaled_apps.contains(json_obj["name"])) {
       cout<< "already latest"<<endl;
       return 0;
     }
    cout << "preparing"<<endl;
    string git_url = json_obj["codename"];
    string name = json_obj["name"];
    char char_array[200];
    std::strcpy(char_array, git_url.c_str());
    
    //system("rm -rf ./build_bin/.git")
    cout << "installing"<<endl;
    if(json_obj["type"] == "git"){
      get_git(char_array, path);
    }else{
      cout << "another";
      snprintf(command, sizeof(command), "wget -P %s %s", path, char_array);
      system(command);
      sleep(3);
    }
    cout << "compile_it"<<endl;
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
    if (json_obj["name"] != "test1") {
      instaled_apps[json_obj["name"]] = json_obj;
      updatejson(app_js, instaled_apps);

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
