#include "../include/Student.h"
#include "../include/DoubleyLinkedList.h"
#include <iostream>
#include <sstream>
#include <memory>

using StudentList = DoubleyLinkedList<Student>;

std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) throw std::runtime_error("Input closed.");
    return line;
}

template <typename T>
T ReadNumber(const std::string& prompt, bool optional = false) {
    std::string line = ReadLine(prompt);
    if (optional && line.find_first_not_of(" \t\r") == std::string::npos) return T{};
    std::istringstream input(line);
    T value;
    if (!(input >> value)) throw std::invalid_argument("Please enter a valid number.");
    input >> std::ws;
    if (!input.eof()) throw std::invalid_argument("Please enter a valid number.");
    return value;
}

void AddItem(StudentList* list) {
    std::string first = ReadLine("First name: ");
    std::string last = ReadLine("Last name: ");
    std::string number = ReadLine("M Number (M and 8 digits): ");
    Student key(number);
    if (list->IsInList(&key)) {
        std::cout << "Error: A student with " << number << " already exists.\nStudent was not added.\n";
        return;
    }
    double gpa = ReadNumber<double>("GPA (Enter for 0): ", true);
    int year = ReadNumber<int>("Birth year: ");
    int month = ReadNumber<int>("Birth month: ");
    int day = ReadNumber<int>("Birth day: ");
    auto student = std::make_unique<Student>(first, last, number, year, month, day, gpa);
    list->AddItem(student.get());
    student.release();
    std::cout << "Student added.\n";
}

void GetItem(StudentList* list) {
    Student key(ReadLine("M Number to remove: "));
    std::unique_ptr<Student> result(list->GetItem(&key));
    if (result) result->display();
    else std::cout << "M Number not found.\n";
}

void IsInList(StudentList* list) {
    Student key(ReadLine("M Number to search for: "));
    std::cout << (list->IsInList(&key) ? "Student is in list.\n" : "Student is not in list.\n");
}

void DisplayStudent(Student* student) {
    if (student) student->display();
    else std::cout << "No student to display.\n";
}

int main() {
    StudentList list;
    while (true) {
        std::cout << "\n1: Add Student\n2: Get Student (removes student)\n3: Search for Student\n"
                     "4: Display All Students\n5: Display Student at Location\n6: Remove All Students\n"
                     "7: Save Students to File\n8: Load Students from File\n9: Display Smallest M Number\n"
                     "10: Display Largest M Number\n11: Reverse List\n12: Exit\n"
                     "13: Is Empty\n14: Size\n15: See Next\n16: Reset\n";
        try {
            int option = ReadNumber<int>("Choice: ");
            switch (option) {
                case 1: AddItem(&list); break;
                case 2: GetItem(&list); break;
                case 3: IsInList(&list); break;
                case 4: list.DisplayAll(); break;
                case 5: DisplayStudent(list.SeeAt(ReadNumber<int>("Index (starts at 0): "))); break;
                case 6: list.RemoveAll(); std::cout << "All students removed.\n"; break;
                case 7:
                    std::cout << (list.SaveToFile(ReadLine("Filename: ")) ? "Students saved.\n" : "Error: Unable to write file.\n");
                    break;
                case 8:
                    std::cout << (list.LoadFromFile(ReadLine("Filename: ")) ? "Students loaded.\n" : "Error: Unable to open file or invalid student data.\n");
                    break;
                case 9: DisplayStudent(list.GetSmallest()); break;
                case 10: DisplayStudent(list.GetLargest()); break;
                case 11: list.Reverse(); std::cout << "List reversed.\n"; break;
                case 12: std::cout << "Goodbye.\n"; return 0;
                case 13: std::cout << (list.IsEmpty() ? "List is empty.\n" : "List is not empty.\n"); break;
                case 14: std::cout << "Size: " << list.Size() << '\n'; break;
                case 15: DisplayStudent(list.SeeNext()); break;
                case 16: list.Reset(); std::cout << "Location reset.\n"; break;
                default: std::cout << "Invalid option.\n";
            }
        } catch (const std::exception& error) {
            if (std::cin.eof()) return 0;
            std::cout << "Error: " << error.what() << '\n';
        }
    }
}
