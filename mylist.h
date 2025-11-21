#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <fstream>
using namespace std;

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    int getSize() { return size; }

    void addNode(const string &front, const string &back) {
        Node* newNode = new Node(front, back);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    bool deleteNode(Node* node) {
        if (node == nullptr) return false;

        if (node == head) {                 // Xóa đầu
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } 
        else if (node == tail) {            // Xóa cuối
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
        } 
        else {                              // Xóa giữa
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        size--;
        return true;
    }

    void saveToFile(const string &filename) {
        ofstream file(filename);
        Node* temp = head;
        while (temp) {
            file << temp->front << ";" << temp->back << "\n";
            temp = temp->next;
        }
        file.close();
    }

    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

#endif
