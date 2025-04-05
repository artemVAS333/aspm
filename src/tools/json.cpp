#include <iostream>
#include <fstream>
#include "tools.h"

using namespace std;
using namespace nlohmann;

json getjson(const char *path)
{
    ifstream file(path);
    if (!file)
    {
        cerr << "Failed to open file: " << path << endl;
        return json{};
    }

    json json_obj;
    try
    {
        file >> json_obj;
    }
    catch (const exception &e)
    {
        cerr << "JSON parse error: " << e.what() << endl;
        return json{};
    }

    file.close();
    return json_obj;
}

json updatejson(const char *path, json &new_data)
{
    json json_obj = getjson(path);

    for (auto it = new_data.begin(); it != new_data.end(); ++it)
        json_obj[it.key()] = it.value();

    ofstream file(path);
    if (!file)
    {
        cerr << "Failed to open file for writing: " << path << endl;
        return json_obj;
    }

    file << json_obj.dump(4);
    file.close();

    return json_obj;
}
