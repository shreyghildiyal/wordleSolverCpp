// #include <json/json.h>
#include "loader.h"
// #include "../rapidjson/include/rapidjson/rapidjson.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>


// using json = nlohmann::json;

std::string streamToString(std::ifstream& in) {
    std::stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

void getWordsOfLength(int len, std::vector<std::string>* results) {

    std::string dictionaryFile = "/mnt/d/cppProjects/wordleSolver/data/EDMTDictionary.json";

    std::ifstream ifs(dictionaryFile);

    if (ifs.fail()) {
        std::cout << "Failed to read the file \n" ;
        return;
    }
    nlohmann::json jf = nlohmann::json::parse(ifs);

    if (jf.is_array()) {
        for (int i = 0; i < jf.size(); i++) {
            nlohmann::json wordObject = jf[i];
            if (wordObject.is_object()) {
                // wordObject.
                std::string word = wordObject["word"];
                results->push_back(word);
            }
        }
    }
}

