#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

struct Student {
    string name;
    bitset<10> grades;
};

void fillStudent(Student& student, string name, bitset<10> grades) {
    student.name = name;
    student.grades = grades;
}

void printStudentInfo(const Student& student) {
    cout << "Name: " << student.name << ", Grades: " << student.grades << endl;
}

void printStudentAverage(const Student& student) {
    double average = student.grades.count() / 10.0;
    cout << "Average grade for " << student.name << " is: " << average << endl;
}

void addStudent(vector<Student>& students, const Student& student) {
    students.push_back(student);
}

void setStudentGrades(vector<Student>& students, string name, bitset<10> grades) {
    for (Student& student : students) {
        if (student.name == name) {
            student.grades = grades;
            break;
        }
    }
}

void printStudentsList(const vector<Student>& students) {
    for (const Student& student : students) {
        printStudentInfo(student);
    }
}

void printGradesForStudent(const vector<Student>& students, string name) {
    for (const Student& student : students) {
        if (student.name == name) {
            printStudentInfo(student);
            break;
        }
    }
}

void printDebtors(const vector<Student>& students) {
    for (const Student& student : students) {
        if (student.grades.count() < 10) {
            cout << "Debtor: " << student.name << endl;
        }
    }
}

int main() {
    vector<Student> students;
    Student newStudent;
    fillStudent(newStudent, "Josh Nick Silman", bitset<10>("1111101111"));
    addStudent(students, newStudent);

    printStudentsList(students);
    printGradesForStudent(students, "Josh Nick Silman");
    printDebtors(students);

    return 0;
}
