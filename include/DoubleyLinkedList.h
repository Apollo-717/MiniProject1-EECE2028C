//
// Created by Apollo on 6/10/25.
//

#ifndef DOUBLEYLINKEDLIST_H
#define DOUBLEYLINKEDLIST_H
#include "Student.h"
#include "Node.h"
#include <iostream>


class DoubleyLinkedList {
public:
    //constructor
    DoubleyLinkedList();

    //Method to add an item
    void AddItem(Student* student);

    //Method to get an item and remove it from the list
    Student* GetItem(const std::string& MNumber);

    //Method to check if item is in list
    [[nodiscard]] bool IsInList(const std::string& MNumber) const;

    //Method to check if list is empty
    [[nodiscard]] bool IsEmpty() const;

    //method to get size
    [[nodiscard]] int Size() const;

    //method to track and see next item in list
    Student* SeeNext();

    //method to find an item at a location in the list, and return the item without removing
    Student* SeeAt(int index);

    //method to display all contents in the list and information about them
    void DisplayList() const;

    //method to reset SeeNext to beginning
    void Reset();

    //Destructor
    ~DoubleyLinkedList();



private:
    int size;
    Node* current_location;
    Node* head;
    Node* tail;



};



#endif //DOUBLEYLINKEDLIST_H