#ifndef NODE_H
#define NODE_H

#include <string>

// Node của danh sách liên kết đôi, chứa dữ liệu của 1 flashcard
class Node {
public:
    std::string data;  // nội dung thẻ từ vựng
    Node* next;        // con trỏ đến node kế tiếp
    Node* prev;        // con trỏ đến node trước đó

    // Constructor
    Node(std::string value);
};

#endif
