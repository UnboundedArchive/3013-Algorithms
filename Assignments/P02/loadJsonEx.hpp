#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using json = nlohmann::json;

json loadJsonFile(string filePath) {

    // Load JSON object
    ifstream fileStream(filePath);
    string partialKey = " ";
    json myJson;

    if (fileStream.is_open()) {
        fileStream >> myJson;
        fileStream.close();
    }
    else {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    return myJson;
}