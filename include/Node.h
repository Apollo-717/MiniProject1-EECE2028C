//
// Created by Apollo on 6/12/25.
//

#ifndef NODE_H
#define NODE_H
#include "Student.h"
#include <iostream>

struct Node {
    Student* data;
    Node* prev;
    Node* next;

    explicit Node(Student* student) : data(student), prev(nullptr), next(nullptr) {
        std::cout << "Node created" << std::endl;
    }
    ~Node() {
        std::cout << "Node destroyed: " << data << std::endl;
    }
};



#endif //NODE_H
