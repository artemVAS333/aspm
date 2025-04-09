#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;


string updateNAME  = "test1";

string mainPath;
string buildPath = "./build_bin/";
string installed_json = "./public/installed_app.json";
string binPath = "./bin/";
string toinstall_json = "./public/test.json";

void mainPathInit(){
  char buffer[1024];
  
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
  if (len != -1) {
      buffer[len] = '\0';
      std::string exe_path = std::string(buffer);
      size_t last_slash_pos = exe_path.find_last_of("/\\");
      mainPath = exe_path.substr(0, last_slash_pos) + "/../"; 
  }
  buildPath = mainPath + buildPath;
  installed_json = mainPath + installed_json;
  binPath = mainPath + binPath;
  toinstall_json = mainPath + toinstall_json;

  
}
