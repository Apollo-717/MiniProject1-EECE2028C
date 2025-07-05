//
// Created by Apollo on 6/10/25.
//

#include "../include/Student.h"
#include <string>
#include <ctime>
#include <iostream>
#include <format>

void PrintField(const std::string& label, const std::string& value, int totalWidth);
void PrintLine(char ch, int length);

Student::Student(std::string First_Name, std::string Last_Name, std::string M_Num, int Birth_year, int Birth_month, int Birth_day, double Grade_Point_Average) {
    FirstName = First_Name;
    LastName = Last_Name;
    M_Number = M_Num;
    year = Birth_year;
    month = Birth_month;
    day = Birth_day;
    gpa = Grade_Point_Average;
}
void Student::display() {
    const int width = 38;
    PrintLine('-', width);
    //std::string str = std::format("{:.2f}",MyStudent.getGPA());

    PrintField("Student Name", this -> getName(), width);
    PrintField("Student M-Number", this -> GetM_Number(), width);
    PrintField("Student GPA",std::format("{:.2f}",this -> getGPA()), width);
    PrintField("Student age", std::to_string(this -> getAge()), width);

    PrintLine('-', width);
}
double Student::getGPA() {
    return gpa;
}
std::string Student::getName() {
    return FirstName + " " + LastName;
}

std::string Student::GetM_Number() {
    return M_Number;
}

int Student::getAge() {
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    int age = now.tm_year + 1900 - year;
    if (now.tm_mon + 1 < month || (now.tm_mon + 1 == month && now.tm_mday < day)) age--;
    return int(age);
}

bool Student::operator<(const std::string M_num) const {
    return M_Number < M_num;
}
bool Student::operator>(const std::string M_num) const {
    return M_Number > M_num;
}
bool Student::operator==(const std::string M_num) const {
    return M_Number == M_num;
}

