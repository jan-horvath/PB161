#include "attack.hpp"
#include "md5/hl_md5wrapper.hpp"
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>

// load dictionary with given name
std::vector<std::string> loadDictionary(const std::string& name) {
    std::ifstream file;
    file.open(name);

    if (!file.is_open()) {
        std::cout << strerror(errno);
    };

    std::vector<std::string> dictionary;
    while (file.good()) {
        std::string word;
        file >> word;
        dictionary.push_back(word);
    }

    return dictionary;
}

//for given word counts its MD5 hash
std::string getHash(const std::string& word) {
    md5wrapper wrapper;
    std::string hash;
    try {
        hash = wrapper.getHashFromString(word);

    } catch (hlException& e) {
        std::cerr << "Error: " << e.error_message() << std::endl;
    }
    return hash;
}

// Apply these rules on given word:
// 1. Every e/E replaces with 3
// 2. Every i/I replaces with 1
//Example : dictionary -> d1ct1onary
std::string letterToNum(std::string word) {
    int i = 0;
    for (char letter : word) {
        if ((letter == 'i') || (letter == 'I'))
            word[i] = '1';

        if ((letter == 'e') || (letter == 'E'))
            word[i] = '3';
        i++;
    }

    return word;
}

// Apply this rules on given word:
// 1. Replace every lovercase character with uppercase character [a -> A]
// 2. Replace every uppercase character with uppercase character [A -> a]
//Example : Dictionary -> dICTIONARY
std::string letterChange(std::string word) {
    using namespace std;
    int i = 0;
    for (char letter : word) {
        word[i] = toupper(letter);
        if (word[i] == letter)
            word[i] = tolower(word[i]);
        i++;
    }
    return word;
}

// Apply this rules on given word:
// Adds underscore behind third letter in word. Function doesn't replace anything
// If length of the word is shorter then 3 characters, return original word (without adding underscore)
// Example : dictionary -> dic_tionary
std::string addUnderscore(std::string word) {
    if (word.length() < 3) return word;
    return word.insert(3,1,'_');
}

// Apply this rule on given word:
//Every 'a' replace with string "123"
//Every 'A' replace with string "456"
std::string replaceA(std::string word) {
    for (unsigned int pos = 0; pos<word.length(); ++pos) {
        std::string wordCheck = word;
        if (word[pos] == 'a') {
            word.insert(pos+1, "123");
            word.erase(pos, 1); //CHECK POSITION
        }
        if (word[pos] == 'A') {
            word.insert(pos+1, "456");
            word.erase(pos, 1); //CHECK POSITION
        }
    }
    return word;
}

//Provides MD5 attack on @hash with given @dictionary
std::string attack(const std::string& hash, std::vector<std::string>& dictionary) {
    if (hash.length() != 32) {
        std::cout << "invalid hash" << std::endl;
        return "";
    }

    for (std::string entry : dictionary) {

        if (getHash(entry) == hash)
            return entry;

        if (getHash(letterToNum(entry)) == hash)
            return letterToNum(entry);

        if (getHash(letterChange(entry)) == hash)
            return letterChange(entry);

        if (getHash(addUnderscore(entry)) == hash)
            return addUnderscore(entry);

        if (getHash(replaceA(entry)) == hash)
            return replaceA(entry);
    }
    return "";
}
