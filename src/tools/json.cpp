#include <iostream>
#include <fstream>
#include "tools.h"

nlohmann::json getjson(char *path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return nlohmann::json{};  
    }

    nlohmann::json json_obj;
    try {
        file >> json_obj;  
    } catch (const std::exception &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return nlohmann::json{};  
    }
    
    file.close();
    return json_obj;
}

nlohmann::json updatejson(char *path, nlohmann::json &new_data) {
    nlohmann::json json_obj = getjson(path);

    for (auto it = new_data.begin(); it != new_data.end(); ++it) {
        json_obj[it.key()] = it.value();  
    }

    std::ofstream file(path);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << path << std::endl;
        return json_obj;
    }

    file << json_obj.dump(4);
    file.close();

    return json_obj;
}


// int main(int argc, char * argv[]) {
//     nlohmann::json json_obj = getjson(argv[1]);
//     std::cout << json_obj["name"] << std::endl;
//     nlohmann::json test_js;
//     test_js["local"]["name00"] = "test";
//     nlohmann::json json_new = updatejson(argv[1], test_js);
//     return 0;
// }

