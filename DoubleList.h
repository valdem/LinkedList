#pragma once
#include <iostream>

using ValueType = double;

class DoubleList
{
    struct Node {
        Node(const ValueType& value, Node* next = nullptr, Node* prev = nullptr);
        ~Node();

        void insertNext(const ValueType& value);
        void removeNext();
        
        void insertPrev(const ValueType& value);
        void removePrev();

        ValueType value;
        Node* next;
        Node* prev;

    };
public:
    ////
    DoubleList();
    DoubleList(const DoubleList& copyList);
    DoubleList& operator=(const DoubleList& copyList);

    DoubleList(DoubleList&& moveList) noexcept;
    DoubleList& operator=(DoubleList&& moveList) noexcept;
    
    ~DoubleList();
    ////
    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos) const;
    // доступ к узлу по индексу
    DoubleList::Node* getNode(const size_t pos) const;
        
    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value);
    // вставка элемента после узла, (O(1))
    void insertAfterNode(Node* node, const ValueType& value);
    //вставка элемента перед узлом
    void insertBeforeNode(Node* node, const ValueType& value);
    // вставка в конец (О(n))
    void pushBack(const ValueType& value);
    // вставка в начало (О(1))
    void pushFront(const ValueType& value);

    // удаление
    void remove(const size_t pos);
    void removeNextNode(Node* node);
    void removePrevNode(Node* node);
    void removeFront();
    void removeBack();
        
    // поиск, О(n)
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;

    // разворот списка
    void reverse();                        // изменение текущего списка
    DoubleList reverse() const;            // полчение нового списка (для константных объектов)
    DoubleList getReverseList() const;    // чтобы неконстантный объект тоже мог возвращать новый развернутый список

    size_t size() const;
        
    void print();
private:
    Node*    _head;
    Node*    _tail;
    size_t   _size;
    
    void forceNodeDelete(Node* node);
};
