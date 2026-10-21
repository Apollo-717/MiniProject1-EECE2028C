template <typename T>
DoubleyLinkedList<T>::DoubleyLinkedList(const DoubleyLinkedList& other) {
    reversed = other.reversed;
    try {
        for (Node<T>* node = other.head; node; node = node->next) {
            auto item = std::make_unique<T>(*node->data);
            Node<T>* copy = new Node<T>(item.get());
            item.release();
            copy->prev = tail;
            if (tail) tail->next = copy;
            else head = copy;
            tail = copy;
            ++size;
            if (node == other.current_location) current_location = copy;
        }
    } catch (...) {
        RemoveAll();
        throw;
    }
}

template <typename T>
void DoubleyLinkedList<T>::Swap(DoubleyLinkedList& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(current_location, other.current_location);
    std::swap(size, other.size);
    std::swap(reversed, other.reversed);
}

template <typename T>
DoubleyLinkedList<T>& DoubleyLinkedList<T>::operator=(const DoubleyLinkedList& other) {
    if (this != &other) {
        DoubleyLinkedList copy(other);
        Swap(copy);
    }
    return *this;
}

template <typename T>
void DoubleyLinkedList<T>::AddItem(T* item) {
    if (!item) throw std::invalid_argument("Cannot add a null item.");
    if (IsInList(item)) throw std::invalid_argument("Item already exists. Item was not added.");
    Node<T>* position = head;
    while (position && (reversed ? *position->data > *item : *position->data < *item))
        position = position->next;
    Node<T>* node = new Node<T>(item);
    node->next = position;
    node->prev = position ? position->prev : tail;
    if (node->prev) node->prev->next = node;
    else head = node;
    if (position) position->prev = node;
    else tail = node;
    ++size;
    Reset();
}

template <typename T>
T* DoubleyLinkedList<T>::GetItem(const T* item) {
    if (!item) return nullptr;
    for (Node<T>* node = head; node; node = node->next) {
        if (*node->data == *item) {
            if (current_location == node) current_location = node->next;
            if (node->prev) node->prev->next = node->next;
            else head = node->next;
            if (node->next) node->next->prev = node->prev;
            else tail = node->prev;
            T* result = node->data;
            delete node;
            --size;
            return result;
        }
    }
    return nullptr;
}

template <typename T>
bool DoubleyLinkedList<T>::IsInList(const T* item) const {
    if (!item) return false;
    for (Node<T>* node = head; node; node = node->next)
        if (*node->data == *item) return true;
    return false;
}

template <typename T>
T* DoubleyLinkedList<T>::SeeNext() {
    if (IsEmpty()) throw std::out_of_range("List is empty.");
    if (!current_location) return nullptr;
    T* result = current_location->data;
    current_location = current_location->next;
    return result;
}

template <typename T>
T* DoubleyLinkedList<T>::SeeAt(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index is out of range.");
    Node<T>* node = head;
    for (int i = 0; i < index; ++i) node = node->next;
    current_location = node->next;
    return node->data;
}

template <typename T>
void DoubleyLinkedList<T>::DisplayList() const {
    for (Node<T>* node = head; node; node = node->next) node->data->display();
}

template <typename T>
void DoubleyLinkedList<T>::RemoveAll() {
    while (head) {
        Node<T>* node = head;
        head = head->next;
        delete node->data;
        delete node;
    }
    tail = current_location = nullptr;
    size = 0;
    reversed = false;
}

template <typename T>
T* DoubleyLinkedList<T>::GetLargest() const {
    return IsEmpty() ? nullptr : (reversed ? head : tail)->data;
}

template <typename T>
T* DoubleyLinkedList<T>::GetSmallest() const {
    return IsEmpty() ? nullptr : (reversed ? tail : head)->data;
}

template <typename T>
void DoubleyLinkedList<T>::Reverse() {
    Node<T>* node = head;
    while (node) {
        std::swap(node->prev, node->next);
        node = node->prev;
    }
    std::swap(head, tail);
    reversed = !reversed;
    Reset();
}

template <typename T>
bool DoubleyLinkedList<T>::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return false;
    for (Node<T>* node = head; node; node = node->next) file << *node->data << '\n';
    file.close();
    return !file.fail();
}

template <typename T>
bool DoubleyLinkedList<T>::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;
    DoubleyLinkedList loaded;
    std::string line;
    try {
        while (std::getline(file, line)) {
            std::istringstream row(line);
            if (row >> std::ws; row.eof()) continue;
            auto item = std::make_unique<T>();
            if (!(row >> *item)) return false;
            row >> std::ws;
            if (!row.eof()) return false;
            loaded.AddItem(item.get());
            item.release();
        }
        if (file.bad()) return false;
    } catch (const std::invalid_argument&) {
        return false;
    }
    Swap(loaded);
    return true;
}
