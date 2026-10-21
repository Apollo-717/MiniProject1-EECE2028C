#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iosfwd>

class Student {
private:
    std::string FirstName;
    std::string LastName;
    std::string M_Number;
    double gpa = 0.0;
    int year = 2000, month = 1, day = 1;
public:
    Student() = default;
    explicit Student(const std::string& MNumber);
    Student(std::string FirstName, std::string LastName, std::string M_Number,
            int year, int month, int day, double gpa = 0.0);

    std::string getName() const;
    std::string GetM_Number() const;
    double getGPA() const;
    int getAge() const;
    void display() const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator==(const Student& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Student& student);
    friend std::istream& operator>>(std::istream& in, Student& student);
};

#endif
