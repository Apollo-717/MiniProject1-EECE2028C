#ifndef DOUBLEYLINKEDLIST_H
#define DOUBLEYLINKEDLIST_H
#include "Node.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <utility>

template <typename T>
class DoubleyLinkedList {
public:
    DoubleyLinkedList() = default;
    DoubleyLinkedList(const DoubleyLinkedList& other);
    DoubleyLinkedList& operator=(const DoubleyLinkedList& other);
    ~DoubleyLinkedList() { RemoveAll(); }

    // The list owns items after adding them.
    void AddItem(T* item);
    T* GetItem(const T* item);
    [[nodiscard]] bool IsInList(const T* item) const;
    [[nodiscard]] bool IsEmpty() const { return size == 0; }
    [[nodiscard]] int Size() const { return size; }
    T* SeeNext();
    T* SeeAt(int index);
    void Reset() { current_location = head; }
    void DisplayList() const;
    void DisplayAll() const { DisplayList(); }
    void RemoveAll();
    T* GetLargest() const;
    T* GetSmallest() const;
    void Reverse();
    bool SaveToFile(const std::string& filename) const;
    bool LoadFromFile(const std::string& filename);

private:
    int size = 0;
    Node<T>* current_location = nullptr;
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    bool reversed = false;
    void Swap(DoubleyLinkedList& other);
};

#include "DoubleyLinkedList.tpp"
#endif
