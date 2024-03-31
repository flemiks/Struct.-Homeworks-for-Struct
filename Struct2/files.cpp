#include <iostream>
#include <sstream>
#include <fstream>
#include "files.h"

using namespace std;

string getTextFromFile(const string& fileName) {
    fstream file(fileName, ios::in);
    if (!file.is_open()) {
        return "Unable to open file";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void writeTextToFile(const string& fileName, const string& buffer) {
    fstream file(fileName, ios::out);
    if (!file.is_open()) {
        cout << "Unable to open file";
        return;
    }
    file << buffer << endl;
    file.close();
}