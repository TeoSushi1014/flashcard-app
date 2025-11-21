#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

struct Node {
    string front;
    string back;
    Node* prev;
    Node* next;

    Node(const string &f, const string &b)
        : front(f), back(b), prev(nullptr), next(nullptr) {}
};

#endif
