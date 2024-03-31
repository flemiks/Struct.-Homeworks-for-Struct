// Struct2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdlib.h>
#include <algorithm> 
#include<string>
#include <cctype>
#include <sstream>
#include <vector>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include "files.h"

using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m";

struct Employee {
	string surname;
	string name;
	string age;
};

int validateDigitInput(int selection) {
	while (!(cin >> selection)) {
		if (cin.eof()) {
			cout << "Entry completed unexpectedly." << endl;
			return 1;
		}
		else if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << RED << "Wrong input. Please enter 1, 2, 3 or 3 to exit" << RESET << endl;
		}
	}
	return selection;
}

bool validateAge(const string& age) {
	for (const char c : age) {
		if (!isdigit(c)) {
			cout << RED << "Please enter only digit 0-9 to enter age. Enter all data for employee again " << RESET << endl;
			return false;
		}
	}
	int ageNum = stoi(age);
	if (ageNum < 18 || ageNum > 65) {
		cout << RED << "The employee can be between 18 and 65 years of age" << RESET << endl;
		return false;
	}
	return true;
}

vector<Employee> stringToVector(const string& fileData) {
	vector<Employee> items;
	istringstream stream(fileData);
	string surname, name, age;

	while (getline(stream, surname) && getline(stream, name) && getline(stream, age)) {
		items.push_back({ surname, name,age });
	}

	return items;
}

string vectorToString(vector<Employee>& employeeList) {
	stringstream stream;
	for (const auto& employee : employeeList) {
		stream << employee.surname << "\n" << employee.name << "\n" << employee.age << "\n";
	}
	return stream.str();
}

vector<Employee> getEmployeeListFromFileName(const string& fileName) {
	string fileData = getTextFromFile(fileName);
	vector<Employee> employeeList = stringToVector(fileData);
	return employeeList;
}

void writeEmployeeListToFile(vector<Employee>& employeeList, const string& fileName) {
	string strEmployeeList = vectorToString(employeeList);
	writeTextToFile(fileName, strEmployeeList);
}

void printEmployeeList(const vector<Employee> employeeList) {
	int maxLengthSurname = 0;
	int maxLengthName = 0;
	for (const auto& employee : employeeList) {
		maxLengthSurname = (maxLengthSurname > employee.surname.size()) ? maxLengthSurname : employee.surname.size();
		maxLengthName = (maxLengthName > employee.name.size()) ? maxLengthName : employee.name.size();
	}
	cout << left;
	for (const auto& employee : employeeList) {
		cout << MAGENTA << setw(11) << "Surname: " << RESET << setw(maxLengthSurname + 1) << employee.surname << MAGENTA << setw(7) << " Name: " << RESET
			<< setw(maxLengthName + 1) << employee.name << CYAN << setw(6) << "Age: " << employee.age << endl;
	}
	cout << endl;
}


void addNewEmployeeToList(vector<Employee>& employeeList) {
	string surname, name, age, preCin;
	cout << endl;
	cout << GREEN << "Add Surname Name and Age for example \"Shevchenko\" \"Taras\" \"55\"" << RESET << endl;
	cout << YELLOW << "To exit data entry mode, enter" << RED << " \"exit\" " << RESET << endl;
	cout << endl;
	do
	{
		cout << MAGENTA << "Enter Surname: " << RESET;
		cin >> preCin;
		if (preCin == "exit") break;
		surname = preCin;
		cout << MAGENTA << "Enter Name: " << RESET;
		cin >> preCin;
		if (preCin == "exit") break;
		name = preCin;
		cout << BLUE << "Enter Age: " << RESET;
		cin >> preCin;
		if (preCin == "exit") break;
		if (!validateAge(preCin))break;
		age = preCin;
		employeeList.push_back({ surname, name, age });
	} while (true);
}

void deleteEmployeeFromList(vector<Employee>& employeeList, const string& surnameForFind) {
	auto originalSize = employeeList.size();
	employeeList.erase(remove_if(employeeList.begin(), employeeList.end(),
		[&surnameForFind](const Employee& employee) {
			return employee.surname == surnameForFind;
		}),
		employeeList.end());
	if (employeeList.size() == originalSize) {
		cout << RED << "Resource does not exist. Nothing has been deleted" << RESET << endl;
	}
}

void editEmployeeFromList(vector<Employee>& employeeList, const string& surnameForFind, const string& nameForFind) {
	string surname, name, age, preCin;
	for (auto& employee : employeeList) {
		if (employee.surname == surnameForFind && employee.name == nameForFind) {
			cout << MAGENTA << "Surname: " << RESET << employee.surname << MAGENTA << " Name: " << RESET << employee.name << CYAN << "Age: " << employee.age << endl;
			cout << endl;
			cout << MAGENTA << "Enter Surname: " << RESET;
			cin >> surname;
			cout << MAGENTA << "Enter Name: " << RESET;
			cin >> name;
			cout << BLUE << "Enter Age: " << RESET;
			cin >> age;
			if (!validateAge(age)) return;
			employee.surname = surname;
			employee.name = name;
			employee.age = age;
			return;
		}
	}
	cout << "Employee not found." << endl;
}

void findEmployeeBySurname(vector<Employee>& employeeList, const string& surnameForFind) {
	string surname, name, age, preCin;
	for (auto& employee : employeeList) {
		if (employee.surname == surnameForFind) {
			cout << MAGENTA  << "Surname: " << RESET << employee.surname << MAGENTA  << " Name: " << RESET << employee.name << CYAN << " Age: " << employee.age << endl;
			return;
		}
	}
	cout << "Employee not found." << endl;
}

void getEmployeeListByAge(vector<Employee>& employeeList, const string& ageForFind) {
	vector<Employee> newEmployeeList;
	for (auto& employee : employeeList) {
		if (employee.age == ageForFind) {
			newEmployeeList.push_back({ employee.surname, employee.name, employee.age });
		}
	}
	if (newEmployeeList.size() == 0) {
		cout << "Employee not found." << endl;
		return;
	}
	printEmployeeList(newEmployeeList);
}

void getEmployeeListByFistSurnameLetter(vector<Employee>& employeeList, const char& fistSurnameLetterForFind) {
	vector<Employee> newEmployeeList;
	for (auto& employee : employeeList) {
		if (employee.surname[0] == fistSurnameLetterForFind) {
			newEmployeeList.push_back({ employee.surname, employee.name, employee.age });
		}
	}
	if (newEmployeeList.size() == 0) {
		cout << "Employee not found." << endl;
		return;
	}
	printEmployeeList(newEmployeeList);
}

void runMenuForUseEmployeeList( vector<Employee> employeeList, const string& fileName) {
	int selection = 0;
	string surnameForFind, nameForFind, ageForFind;
	char fistSurnameLetterForFind;

	do {
		cout << RED << "Select Menu item:" << RESET << endl;
		cout << GREEN << "1. To add new Employee." << endl;
		cout << "2. To delete Employee."  << endl;
		cout << "3. To edit Employee data." << endl;
		cout << "4. To find Employee by Surname." << endl;
		cout << "5. To get Employee list by Age." << endl;
		cout << "6. To get Employee list by Fist surname letter." << RESET << endl;
		cout << YELLOW << "7. Exit." << RESET << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << GREEN << "Enter Menu number: " << RESET;
		selection = validateDigitInput(selection);
		switch (selection) {
		case 1:
			addNewEmployeeToList(employeeList);
			printEmployeeList(employeeList);
			writeEmployeeListToFile(employeeList, fileName);
			cout << endl;
			break;
		case 2:
			printEmployeeList(employeeList);
			cout << GREEN << "Enter Surname to delete: " << RESET;
			cin >> surnameForFind;
			deleteEmployeeFromList(employeeList, surnameForFind);
			printEmployeeList(employeeList);
			writeEmployeeListToFile(employeeList, fileName);
			cout << endl;
			break;
		case 3:
			printEmployeeList(employeeList);
			cout << GREEN << "Enter Surname to ecit data: " << RESET;
			cin >> surnameForFind;
			cout << GREEN << "Enter Name to ecit data: " << RESET;
			cin >> nameForFind;
			editEmployeeFromList(employeeList, surnameForFind, nameForFind);
			writeEmployeeListToFile(employeeList, fileName);
			printEmployeeList(employeeList);
			cout << endl;
			break;
		case 4:
			cout << GREEN << "Enter Surname to find: " << RESET;
			cin >> surnameForFind;
			findEmployeeBySurname(employeeList, surnameForFind);
			cout << endl;
			break;
		case 5:
			cout << GREEN << "Enter Age to get list of employee: " << RESET;
			cin >> ageForFind;
			getEmployeeListByAge(employeeList, ageForFind);
			cout << endl;
			break;
		case 6:
			cout << GREEN << "Enter the First letter of Surname get list of employee: " << RESET;
			cin >> fistSurnameLetterForFind;
			getEmployeeListByFistSurnameLetter(employeeList, fistSurnameLetterForFind);
			cout << endl;
			break;
		case 7:
			cout << "Exiting program." << endl;
			exit(0);
			cout << RED << "Wrong input. Please enter 1, 2, 3, 4, 5, 6 or 7 to exit" << RESET << endl;
			cout << endl;
			break;
		}
	} while (true);
}

int main()
{
	vector<Employee> employeeList;
	string fileName;
	string resourceNameToDelete;
	int selection = 0;
	do {
		cout << RED << "Select Menu item:" << RESET << endl;
		cout << GREEN << "1. To Enter a name for the Employee list file." << endl;
		cout << "2. To Create new Employee list file." << RESET << endl;
		cout << YELLOW << "3. Exit." << RESET << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << GREEN << "Enter Menu number: " << RESET;
		selection = validateDigitInput(selection);
		switch (selection) {
		case 1:
			cout << GREEN << "1. Enter file name to get Employee list: ";
			cin >> fileName;
			employeeList = getEmployeeListFromFileName(fileName);
			if (fileName == "") {
				cout << RED << "Unable to open " << fileName << ". Be sure that file exist" << RESET << endl;
				cout << endl;
				break;
			}
			printEmployeeList(employeeList);
			runMenuForUseEmployeeList(employeeList, fileName);
			cout << endl;
			break;
		case 2:
			cout << GREEN << "1. Enter file name for NEW Employee list: ";
			cin >> fileName;
			writeTextToFile(fileName, "");
			employeeList.clear();
			addNewEmployeeToList(employeeList);
			printEmployeeList(employeeList);
			writeEmployeeListToFile(employeeList, fileName);
			break;
		case 3:
			cout << "Exiting program." << endl;
			exit(0);
			cout << RED << "Wrong input. Please enter 1, 2, 3, 4 or 5 to exit" << RESET << endl;
			cout << endl;
			break;
		}
	} while (true);
}


