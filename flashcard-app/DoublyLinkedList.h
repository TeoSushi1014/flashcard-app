#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void append(std::wstring value);
    void prepend(std::wstring value);
    bool deleteNode(std::wstring value);
    Node* findByIndex(int index);
    void traverseForward();
    void traverseBackward();
    
    // Helper methods for UI
    int getSize();
    Node* getCurrent();
    void setCurrentIndex(int index);
    int getCurrentIndex();
    std::wstring getAllCardsAsString();
    std::wstring getAllCardsAsStringReverse();
    
private:
    int currentIndex;
    Node* currentNode;
};

#endif

