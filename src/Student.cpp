#include "../include/Student.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace {
void ValidateMNumber(const std::string& number) {
    if (number.size() != 9 || number[0] != 'M' ||
        !std::all_of(number.begin() + 1, number.end(), [](unsigned char ch) { return ch >= '0' && ch <= '9'; }))
        throw std::invalid_argument("M Number must be M followed by 8 digits.");
}

bool Blank(const std::string& text) {
    return std::all_of(text.begin(), text.end(), [](unsigned char ch) { return std::isspace(ch); });
}

void PrintLine(int width) {
    std::cout << '+' << std::string(width, '-') << "+\n";
}
void PrintField(const std::string& label, const std::string& value, int width) {
    std::cout << "| " << std::left << std::setw(width - 2) << (label + " : " + value) << " |\n";
}
}

Student::Student(const std::string& MNumber) : M_Number(MNumber) {
    ValidateMNumber(M_Number);
}

Student::Student(std::string first, std::string last, std::string number,
                 int birthYear, int birthMonth, int birthDay, double grade)
    : FirstName(first), LastName(last), M_Number(number), gpa(grade),
      year(birthYear), month(birthMonth), day(birthDay) {
    if (Blank(first) || Blank(last)) throw std::invalid_argument("First and last name cannot be empty.");
    ValidateMNumber(number);
    if (!std::isfinite(gpa) || gpa < 0 || gpa > 4)
        throw std::invalid_argument("GPA must be between 0.0 and 4.0.");
    const bool leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    const int days[] = {31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > days[month - 1])
        throw std::invalid_argument("Invalid birthday.");
    const std::time_t time = std::time(nullptr);
    const std::tm now = *std::localtime(&time);
    if (year > now.tm_year + 1900 || (year == now.tm_year + 1900 &&
        (month > now.tm_mon + 1 || (month == now.tm_mon + 1 && day > now.tm_mday))))
        throw std::invalid_argument("Birthday cannot be in the future.");
}

void Student::display() const {
    const int width = std::max(40, static_cast<int>(getName().size()) + 18);
    std::ostringstream grade;
    grade << std::fixed << std::setprecision(2) << gpa;
    PrintLine(width);
    PrintField("Student Name", getName(), width);
    PrintField("M Number", GetM_Number(), width);
    PrintField("GPA", grade.str(), width);
    PrintField("Age (years)", std::to_string(getAge()), width);
    PrintLine(width);
}

double Student::getGPA() const { return gpa; }
std::string Student::getName() const { return FirstName + " " + LastName; }
std::string Student::GetM_Number() const { return M_Number; }

int Student::getAge() const {
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    int age = now.tm_year + 1900 - year;
    if (now.tm_mon + 1 < month || (now.tm_mon + 1 == month && now.tm_mday < day)) --age;
    return age;
}

bool Student::operator<(const Student& other) const { return M_Number < other.M_Number; }
bool Student::operator>(const Student& other) const { return M_Number > other.M_Number; }
bool Student::operator==(const Student& other) const { return M_Number == other.M_Number; }

std::ostream& operator<<(std::ostream& out, const Student& student) {
    return out << std::quoted(student.FirstName) << ' ' << std::quoted(student.LastName) << ' '
               << student.M_Number << ' ' << student.year << ' ' << student.month << ' '
               << student.day << ' ' << std::setprecision(17) << student.gpa;
}

std::istream& operator>>(std::istream& in, Student& student) {
    std::string first, last, number;
    int year, month, day;
    double gpa;
    if (in >> std::quoted(first) >> std::quoted(last) >> number >> year >> month >> day >> gpa) {
        try {
            student = Student(first, last, number, year, month, day, gpa);
        } catch (const std::invalid_argument&) {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}
