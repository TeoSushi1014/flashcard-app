#include "DoublyLinkedList.h"
#include <iostream>

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Thêm vào cuối
void DoublyLinkedList::append(std::string value) {
    Node* newNode = new Node(value);

    if (!head) { // list rỗng
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

// Thêm vào đầu
void DoublyLinkedList::prepend(std::string value) {
    Node* newNode = new Node(value);

    if (!head) { // list rỗng
        head = tail = newNode;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

// Xóa node theo giá trị
bool DoublyLinkedList::deleteNode(std::string value) {
    Node* current = head;

    while (current) {
        if (current->data == value) {

            // cập nhật head/tail
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;

            // nối node trước và sau
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;

            delete current;
            return true;
        }
        current = current->next;
    }
    return false; // không tìm thấy
}

// Tìm node bằng index
Node* DoublyLinkedList::findByIndex(int index) {
    Node* current = head;
    int i = 0;

    while (current) {
        if (i == index) return current;
        current = current->next;
        i++;
    }
    return nullptr;
}

// Duyệt xuôi
void DoublyLinkedList::traverseForward() {
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Duyệt ngược
void DoublyLinkedList::traverseBackward() {
    Node* current = tail;
    while (current) {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}
