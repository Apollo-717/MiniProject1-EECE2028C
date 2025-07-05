//
// Created by Apollo on 6/10/25.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <string>



class Student {
private:
    std::string FirstName;
    std::string LastName;
    std::string M_Number;
    double gpa;
    int year, month, day;
public:
    Student(std::string FirstName, std::string LastName, std::string M_Number, int year, int month, int day, double gpa = 0.0);

    std::string getName();
    std::string GetM_Number();
    double getGPA();
    int getAge();
    bool operator<(const std::string M_num) const;
    bool operator>(const std::string M_num) const;
    bool operator==(const std::string M_num) const;
};



#endif //STUDENT_H
