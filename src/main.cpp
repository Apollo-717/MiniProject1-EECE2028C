#include "../include/Student.h"
#include <string>
#include "../include/DoubleyLinkedList.h"
#include <iostream>
#include <format>
#include <cmath>
#include <vector>
void PrintLine(char ch, int length) {
    std::cout << "+";  // left border
    for (int i = 0; i < length; ++i) std::cout << ch;
    std::cout << "+\n";  // right border
}
void PrintField(const std::string& label, const std::string& value, int totalWidth) {
    std::cout << "| " << label << " : " << value;

    int currentLength = 2 + label.length() + 3 + value.length();  // " |label : value"
    int remainingSpaces = totalWidth - currentLength;

    for (int i = 0; i < remainingSpaces; ++i) std::cout << " ";
    std::cout << "|\n";
}

void PrintStudent(Student MyStudent) {


    const int width = 38;
    PrintLine('-', width);
    //std::string str = std::format("{:.2f}",MyStudent.getGPA());

    PrintField("Student Name", MyStudent.getName(), width);
    PrintField("Student M-Number", MyStudent.GetM_Number(), width);
    PrintField("Student GPA",std::format("{:.2f}",MyStudent.getGPA()), width);
    PrintField("Student age", std::to_string(MyStudent.getAge()), width);

    PrintLine('-', width);



}


void AddItem(DoubleyLinkedList *myList) {
    std::string FirstName;
    std::string LastName;
    std::string Mnumber;
    int birthYear;
    int birthMonth;
    int dayOfBirth;
    double GPA;

    std::cout << "Please enter the students first name: ";
    std::cin >> FirstName;
    std::cout << "Please enter the students last name: ";
    std::cin >> LastName;
    std::cout << "Please enter the students M-Number: ";
    std::cin >> Mnumber;
    std::cout << "Please enter the students GPA: ";
    std::cin >> GPA;
    std::cout << "Please enter the students birth year: ";
    std::cin >> birthYear;;
    std::cout << "Please enter the students birth month: ";
    std::cin >> birthMonth;
    std::cout << "Please enter the students day of Birth: ";
    std::cin >> dayOfBirth;
    Student *student = new Student(FirstName, LastName, Mnumber, birthYear, birthMonth, dayOfBirth, GPA);

    myList -> AddItem(student);
}

void GetItem(DoubleyLinkedList *myList) {
    std::cout << "Please enter to M-Number to search for(Please include the 'M'): ";
    std::string Mnumber;
    std::cin >> Mnumber;
    Student* result = myList -> GetItem(Mnumber);
    if (result == nullptr) {
        std::cout << "M Number not Found" << std::endl;
    }
    else {
        PrintStudent(*result);
    }

}














int main() {
    std::cout << "Which function would you like to test?" << std::endl;
    std::cout << "1: Add Item" << std::endl;
    std::cout << "2: Get Item" << std::endl;
    std::cout << "3: Is in List" << std::endl;
    std::cout << "4: Is Empty" << std::endl;
    std::cout << "5: Size" << std::endl;
    std::cout << "6: See Next" << std::endl;
    std::cout << "7: See At" << std::endl;
    std::cout << "8: Exit" << std::endl;
    int option;
    //std::cin >> option;
    DoubleyLinkedList *MyList = new DoubleyLinkedList();
    Student *ExampleStu = new Student("Fill", "McCrack", "M123456789", 1969, 4, 20);
    AddItem(MyList);
    GetItem(MyList);
    //PrintStudent(*ExampleStu);
    //switch(option) {}
    return 0;
}






