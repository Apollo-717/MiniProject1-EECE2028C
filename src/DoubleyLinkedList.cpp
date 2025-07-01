//
// Created by Apollo on 6/10/25.
//

#include "../include/DoubleyLinkedList.h"


DoubleyLinkedList::DoubleyLinkedList() {
    head = nullptr;
    current_location = nullptr;
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
    while (current != nullptr) {

        if (*current->data == MNumber) {
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
    return nullptr;
}

bool DoubleyLinkedList::IsInList(const std::string& MNumber) const {
    Node* current = head;
    while (current != nullptr) {
        if (*current->data == MNumber) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool DoubleyLinkedList::IsEmpty() const {
    if (size == 0) {
        return true;
    }
    return false;
}

int DoubleyLinkedList::Size() const {
    return size;
}





