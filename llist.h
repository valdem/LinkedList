#pragma once
#include <iostream>

using namespace std;

template <typename ValueType>
class LList
{

    struct Node {
        Node(const ValueType& value, Node* next = nullptr);
        ~Node();

        ValueType value;
        Node* next;
    };
    
public:
    
    LList();                         // construct new collection
    ~LList();                        // free resources

    LList(const LList<ValueType>& copyList);
    LList& operator=(const LList<ValueType>& copyList);

    LList(LList<ValueType>&& moveList) ;
    LList& operator=(LList<ValueType>&& moveList) ;
    
    void* operator new(size_t size);
    void operator delete(void* ptr);
    void* operator new[](size_t size);
    void operator delete[](void* ptr);
    
    void push_back(ValueType val);         // add new value at the end:  [1 2 3 4] -> [1 2 3 4 5]
    void push_front(ValueType val);        // add new value at the begin [1 2 3 4] -> [5 1 2 3 4]
    void pop_back();          // remove at the end          [1 2 3 4] -> [1 2 3]
    void pop_front();         // remove at the front        [1 2 3 4] -> [2 3 4]
    size_t size() const;             // get actual number of items [1 2 3 4] -> 4
    ValueType& operator[](const size_t idx) const;     // get rw access ot specific item addressing by idx
    void erase_at(size_t idx);       // remove item at specific position: [1 2 3 4], 2 -> [1 2 4]
    void insert_at(size_t idx, ValueType val); // insert item at specific position: [1 2 3 4], 1, 5 -> [1 5 2 3 4]
    void reverse();                  // reverse item sequense: [1 2 3 4] -> [4 3 2 1]
    
private:
    
    Node* _head;
    size_t _size;
    void AllNodesDelete(Node* node);
};

template <class ValueType>
LList<ValueType>::Node::Node(const ValueType& value, Node* next) {
    this->value = value;
    this->next = next;
}

template <class ValueType>
LList<ValueType>::Node::~Node() {

}

template <class ValueType>
LList<ValueType>::LList()
    : _head(nullptr), _size(0)
{
    
}

template <class ValueType>
LList<ValueType>::~LList() {
    AllNodesDelete(_head);
}

template <class ValueType>
LList<ValueType>::LList(const LList<ValueType>& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_head = nullptr;
        return;
    }
    else {

        this->_head = new Node(copyList._head->value);

        Node* currentNode = this->_head;
        Node* currentCopyNode = copyList._head;

        while (currentCopyNode->next) {
            currentNode->next = new Node(currentCopyNode->next->value);
            currentCopyNode = currentCopyNode->next;
            currentNode = currentNode->next;
        }
    }
}

template <class ValueType>
LList<ValueType>& LList<ValueType>::operator=(const LList<ValueType>& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    else {
        AllNodesDelete(_head);
        LList bufList(copyList);
        
        this->_size = bufList._size;
        this->_head = bufList._head;
        
        bufList._size = 0;
        bufList._head = nullptr;
        
        return *this;
    }
}

template <class ValueType>
LList<ValueType>::LList(LList<ValueType>&& moveList)
{
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}

template <class ValueType>
LList<ValueType>& LList<ValueType>::operator=(LList<ValueType>&& moveList)
{
    if (this == &moveList) {
        return *this;
    }
    else {
        AllNodesDelete(_head);
        this->_size = moveList._size;
        this->_head = moveList._head;

        moveList._size = 0;
        moveList._head = nullptr;

        return *this;
    }
}

template <class ValueType>
void* LList<ValueType>::operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (ptr) {
        return ptr;
    }
    else {
        throw std::bad_alloc();
    }
}

template <class ValueType>
void LList<ValueType>::operator delete(void* ptr) {
    std::free(ptr);
}

template <class ValueType>
void* LList<ValueType>::operator new[](size_t size) {
    void* ptr = std::malloc(size);
    if (ptr) {
        return ptr;
    }
    else {
        throw std::bad_alloc();
    }
}

template <class ValueType>
void LList<ValueType>::operator delete[](void* ptr) {
    std::free(ptr);
}

template <class ValueType>
void LList<ValueType>::push_back(ValueType val) {
    if (_size == 0) {
        push_front(val);
    }
    else {
        insert_at(_size, val);
    }
}

template <class ValueType>
void LList<ValueType>::push_front(ValueType val) {
    _head = new Node(val, _head);
    ++_size;
}

template <class ValueType>
void LList<ValueType>::pop_back() {
    erase_at(_size-1);
}

template <class ValueType>
void LList<ValueType>::pop_front() {
    if (_head->next == nullptr) {
        delete _head;
        --_size;
        return;
    }
    Node* temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
}

template <class ValueType>
size_t LList<ValueType>::size() const {
    return _size;
}

template <class ValueType>
ValueType& LList<ValueType>::operator[](const size_t idx) const {
    if (idx == 0) {
        return _head->value;
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i<idx; i++) {
            bufNode = bufNode->next;
        }
        return bufNode->value;
    }
}

template <class ValueType>
void LList<ValueType>::erase_at(size_t idx) {
    if (idx == 0) {
        pop_front();
    }
    else {
        Node* temp = this->_head;
        for (size_t i = 0; i<idx-1; i++) {
            temp = temp->next;
        }
        Node* remNode = temp->next;
        temp->next = temp->next->next;
        delete remNode;
        --_size;
    }
}

template <class ValueType>
void LList<ValueType>::insert_at(size_t idx, ValueType val) {
    if (idx == 0) {
        push_front(val);
    }
    else {
       Node* bufNode = this->_head;
        for (size_t i = 0; i<idx-1; i++) {
            bufNode = bufNode->next;
        }
        Node* insertNode = new Node(val, bufNode->next);
        bufNode->next = insertNode;
    }
    ++_size;
}

template <class ValueType>
void LList<ValueType>::reverse() {
    Node* current = _head;
    Node* next = nullptr;
    Node* prev = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    _head = prev;
}

template <class ValueType>
void LList<ValueType>::AllNodesDelete(Node* node) {
    if (node == nullptr) {
        return;
    }
    Node* nextDeleteNode = _head->next;
    Node* deleteNode = _head;
    for (size_t i = 0; i<_size; i++) {
        delete deleteNode;
        deleteNode = nextDeleteNode;
        if (nextDeleteNode->next != nullptr) {
            nextDeleteNode = nextDeleteNode->next;
        }
    }

}

template <class ValueType>
void dump(const LList<ValueType>& l)
{
    for(size_t i = 0; i < l.size(); ++i, cout << " ") cout << l[i];
}
