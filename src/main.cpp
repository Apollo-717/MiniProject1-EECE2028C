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

// void PrintStudent(Student MyStudent) {
//
//
//     const int width = 38;
//     PrintLine('-', width);
//     //std::string str = std::format("{:.2f}",MyStudent.getGPA());
//
//     PrintField("Student Name", MyStudent.getName(), width);
//     PrintField("Student M-Number", MyStudent.GetM_Number(), width);
//     PrintField("Student GPA",std::format("{:.2f}",MyStudent.getGPA()), width);
//     PrintField("Student age", std::to_string(MyStudent.getAge()), width);
//
//     PrintLine('-', width);
//
//
//
// }


void AddItem(DoubleyLinkedList *myList) {
    std::string FirstName;
    std::string LastName;
    std::string Mnumber;
    int birthYear;
    int birthMonth;
    int dayOfBirth;
    double GPA=0;

    std::cout << "Please enter the students first name: ";
    std::cin >> FirstName;
    std::cout << "Please enter the students last name: ";
    std::cin >> LastName;
    std::cout << "Please enter the students M-Number(Please include the 'M'): ";
    std::cin >> Mnumber;
    std::cout << "Please enter the students GPA (press Enter for 0): ";

    std::cin.ignore();
    if (std::cin.peek() != '\n') {
        std::cin >> GPA;
    }
    std::cin.ignore();

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
        // PrintStudent(*result);
        result -> display();
    }

}

void IsInList(DoubleyLinkedList *myList) {
    std::cout << "Please enter the students Mnumber(Please include the 'M'): " << std::endl;
    std::string Mnumber;
    std::cin >> Mnumber;
    if (myList -> IsInList(Mnumber)) {
        std::cout << "Student is in List" << std::endl;
    }
    else {
        std::cout << "Student is not in List" << std::endl;
    }

}

void IsEmpty(DoubleyLinkedList *myList) {
    bool isEmpty = myList -> IsEmpty();
    if (isEmpty) {
        std::cout << "List is empty" << std::endl;
    }
    else {
        std::cout << "List is not empty" << std::endl;
    }
}

void Size(DoubleyLinkedList *myList) {
    std::cout << "The size of the list is: " << myList -> Size() << std::endl;
}

void SeeNext(DoubleyLinkedList *myList) {
    try {
        Student* result = myList -> SeeNext();
        if (result == nullptr) {
            std::cout << "Reached end of list" << std::endl;
        }
        else {
            // PrintStudent(*result);
            result -> display();
        }
    } catch (std::out_of_range& e) {
        std::cout << "List is empty cannot see next" << std::endl;
    }
}

void SeeAt(DoubleyLinkedList *myList) {
    try {
        int index;
        std::cout << "Please enter the index of the student: " << std::endl;
        std::cin >> index;
        Student* result = myList -> SeeAt(index);
            // PrintStudent(*result);
        result -> display();

    } catch (std::out_of_range& e) {
        std::cout << "Index is out of range" << std::endl;
    }

}

void Reset(DoubleyLinkedList *myList) {
    myList -> Reset();
    std::cout << "Current location reset to index 0" << std::endl;
}


void Exit(DoubleyLinkedList *myList) {
    delete myList;
    std::cout << "Goodbye" << std::endl;
}



int main() {
    bool running = true;
    DoubleyLinkedList *MyList = new DoubleyLinkedList();

    while (running){
        std::cout << "Which function would you like to test?" << std::endl;
        std::cout << "1: Add Item" << std::endl;
        std::cout << "2: Get Item" << std::endl;
        std::cout << "3: Is in List" << std::endl;
        std::cout << "4: Is Empty" << std::endl;
        std::cout << "5: Size" << std::endl;
        std::cout << "6: See Next" << std::endl;
        std::cout << "7: See At" << std::endl;
        std::cout << "8: Reset" << std::endl;
        std::cout << "9: Display List" << std::endl;
        std::cout << "10: Exit" << std::endl;

    int option;
    std::cin >> option;

        switch(option) {
            case 1: AddItem(MyList); break;
            case 2: GetItem(MyList); break;
            case 3: IsInList(MyList); break;
            case 4: IsEmpty(MyList); break;
            case 5: Size(MyList); break;
            case 6: SeeNext(MyList); break;
            case 7: SeeAt(MyList); break;
            case 8: Reset(MyList); break;
            case 9: MyList -> DisplayList(); break;
            case 10: {
                Exit(MyList);
                running = false;
                break;
            }
                //case 9: stu -> display(); break;
            default: {
                std::cout << "Invalid option" << std::endl;
            }
        }}
    return 0;
}






