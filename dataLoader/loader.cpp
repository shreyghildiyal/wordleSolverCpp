// #include <json/json.h>
#include "loader.h"
// #include "../rapidjson/include/rapidjson/rapidjson.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
// #include <map>

void getDictionaryWordsOfLength(int len, std::map<std::string, int>* results) {

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
                std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });
                if (word.length() == len) {
                    (*results)[word] = 0;
                }
                
            }
        }
    }
}

std::map<std::string, int> getFilteredWordsByFrequency(std::map<std::string, int> words, int minFrequency) {

    std::string frequencyFile = "/mnt/d/cppProjects/wordleSolver/data/unigram_freq.csv";

    std::ifstream ifs(frequencyFile);
    std::string line;
     std::map<std::string, int> result;
    while (std::getline(ifs, line)) {
        int delimPos = line.find(",");
        std::string word = line.substr(0, delimPos);
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });
        std::string countStr = line.substr(delimPos + 1, line.length());
        int count = atoi(countStr.c_str());
        // std::cout << word << " " << count << std::endl;
        if (count >= minFrequency) {
            
            if (words.find(word) != words.end()) {
                // std::cout << word << " " << count << std::endl;
                // words[word] = count;
                result[word] = count;
            }
        }
    }

   

    // for (std::map<std::string, int>::iterator i = words.begin(); i != words.end(); i++) {
    //     if (i->second != 0) {
    //         result[i->first] = i->second;
    //     }
        
    // }

    return result;
}
