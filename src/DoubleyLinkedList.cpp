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
    if (size == 0) {
        head = newNode;
        tail = newNode;
        current_location = newNode;
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

Student* DoubleyLinkedList::SeeNext() {
    if (size == 0) {
        throw std::out_of_range("List is empty. Cannot see next item");
    }
    if (current_location->next == nullptr) {
        return nullptr;
    }
    current_location = current_location->next;
    return current_location->data;
}

Student* DoubleyLinkedList::SeeAt(const int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("index is out of range");
    }
    for (int i=0; i <= index; i++) {
        current_location = current_location->next;
    }
    return current_location->data;
}

void DoubleyLinkedList::Reset() {
    current_location = head;
}

DoubleyLinkedList::~DoubleyLinkedList() {
    Node* current = head;
    for (int i = 0; i < size; i++) {
        delete current->data;
        if (current->next != nullptr) {
            current = current->next;
            delete current->prev;
        }

    }
    delete current;
}
