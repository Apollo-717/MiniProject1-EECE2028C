//
// Created by Apollo on 6/10/25.
//

#include <iostream>
#include "../include/DoubleyLinkedList.h"

DoubleyLinkedList::DoubleyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoubleyLinkedList::AddItem(Student* student) {
    Node* newNode = new Node(student);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;

    }
    size++;
}

Student* DoubleyLinkedList::GetItem(int MNumber) {
    int counter = 0;
    Node* current = head;
    while (counter < size) {

    }
}