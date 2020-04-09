#include "DoubleList.h"
#include <cassert>

DoubleList::Node::Node(const ValueType& value, Node* next, Node* prev){
    this->value = value;
    this->next = next;
    this->prev = prev;
}

DoubleList::Node::~Node()
{
    
}

void DoubleList::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next, this);
    this->next = newNode;
    this->next->prev = newNode;
}

void DoubleList::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

void DoubleList::Node::insertPrev(const ValueType& value)
{
    Node* newNode = new Node(value, this, this->prev);
    this->prev = newNode;
    this->prev->next = newNode;
}

void DoubleList::Node::removePrev()
{
    Node* removeNode = this->prev;
    Node* newPrev = removeNode->prev;
    delete removeNode;
    this->prev = newPrev;
    newPrev->next = this;
    
}

DoubleList::DoubleList() 
    : _head(nullptr), _size(0)
{
    
}

DoubleList::DoubleList(const DoubleList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_head = nullptr;
        return;
    }

    this->_head = new Node(copyList._head->value);

    Node* currentNode = this->_head;
    Node* currentCopyNode = copyList._head;

    while (currentCopyNode->next) {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

DoubleList& DoubleList::operator=(const DoubleList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    DoubleList bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;

    return *this;
}

DoubleList::DoubleList(DoubleList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}

DoubleList& DoubleList::operator=(DoubleList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;

    return *this;
}

DoubleList::~DoubleList()
{
    forceNodeDelete(_head);
}

ValueType& DoubleList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

DoubleList::Node* DoubleList::getNode(const size_t pos) const
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    Node* bufNode = this->_head;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}

void DoubleList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    if (pos == 0) {
        pushFront(value);
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

void DoubleList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    _size += 1;
}

void DoubleList::insertBeforeNode(Node* node, const ValueType& value) {
    node->insertPrev(value);
    _size += 1;
}

void DoubleList::pushBack(const ValueType& value)
{
    Node* newNode = new Node(sizeof(struct Node));
    Node* last = _head;
    newNode->value = value;
    newNode->next = nullptr;
    if (_head == nullptr) {
        newNode->prev = nullptr;
        _head = newNode;
    }
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void DoubleList::pushFront(const ValueType& value)
{
    Node* newNode = new Node(value, _head, nullptr);
    if (_head != nullptr) {
        _head->prev = newNode;
    }
    _head = newNode;
    _size++;
}

void DoubleList::remove(const size_t pos)
{
    delete getNode(pos);
    getNode(pos+1)->prev = getNode(pos-1);
    getNode(pos-1)->next = getNode(pos+1);
}

void DoubleList::removeNextNode(Node* node)
{
    node->removeNext();
    _size--;
}

void DoubleList::removePrevNode(Node* node) {
    node->removePrev();
    _size--;
}

void DoubleList::removeFront() {
    _head->next->prev = nullptr;
    delete _head;
    _head = _head->next;
}

void DoubleList::removeBack() {
    delete getNode(_size-1);
    getNode(_size-2)->next = nullptr;
}

long long int DoubleList::findIndex(const ValueType& value) const
{
    Node* findNext = _head->next;
    size_t index = -1;
    size_t i = 1;
    if (_head->value == value) {
        index = 0;
    }
    else {
        while (findNext) {
            if (findNext->value == value) {
                index = i;
            }
            findNext = findNext->next;
            i++;
        }
    }
    return index;
}

DoubleList::Node* DoubleList::findNode(const ValueType& value) const
{
    Node* findNext = _head->next;
    Node* findNode = nullptr;
    size_t i = 1;
    if (_head->value == value) {
        findNode = _head;
    }
    else {
        while (findNext) {
            if (findNext->value == value) {
                findNode = findNext;
            }
            findNext = findNext->next;
            i++;
        }
    }
    return findNode;
}

void DoubleList::reverse()
{
    Node* current = this->_head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != nullptr) {
        temp = temp->prev;
    }
    
}

DoubleList DoubleList:: reverse() const {
    DoubleList newList;
    for (size_t i = 0; i<_size; i++) {
        newList.insert(i, getNode(i)->value);
    }
    Node* current = newList._head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != nullptr) {
        temp = temp->prev;
    }
    return newList;
}
DoubleList DoubleList:: getReverseList() const {
    DoubleList newList;
    for (size_t i = 0; i<_size; i++) {
        newList.insert(i, getNode(i)->value);
    }
    newList.reverse();
    newList.print();
    return newList;
}

size_t DoubleList::size() const
{
    return _size;
}

void DoubleList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

void DoubleList:: print() {
    Node* temp = _head;
    while (temp != nullptr) {
        std::cout<<temp->prev<<" "<<temp->value<<" "<<temp->next<<std::endl;
        temp = temp->next;
    }
}
