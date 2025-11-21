#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"

class DoublyLinkedList {
private:
    Node* head; // node đầu
    Node* tail; // node cuối

public:
    DoublyLinkedList();

    void append(std::string value);        // thêm cuối
    void prepend(std::string value);       // thêm đầu
    bool deleteNode(std::string value);    // xóa theo value
    Node* findByIndex(int index);          // tìm theo chỉ số
    void traverseForward();                // duyệt xuôi
    void traverseBackward();               // duyệt ngược
};

#endif
