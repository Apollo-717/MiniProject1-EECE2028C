#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T* data;
    Node* prev;
    Node* next;

    explicit Node(T* item) : data(item), prev(nullptr), next(nullptr) {}
};

#endif
