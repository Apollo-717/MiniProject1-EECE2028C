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
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;

    }
    size++;
}

Student* DoubleyLinkedList::GetItem(const std::string& MNumber) {
    Node* current = head;
    while (true) {
        if (current == nullptr) {
            return nullptr;
        }

        if (current->data == MNumber) {
            Student* found_student = current -> data;
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }
            delete current;
            size--;
            return found_student;
        }

        current = current->next;
    }
}
