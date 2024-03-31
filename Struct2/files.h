#pragma once
#include <iostream>
#include <sstream>
#include <fstream>;

using namespace std;

string getTextFromFile(const string& fileName);
void writeTextToFile(const string& fileName, const string& encryptedBuffer);