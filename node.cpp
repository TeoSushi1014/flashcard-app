#include "Node.h"

// Khởi tạo node: data=value, next/prev=nullptr
Node::Node(std::string value) {
    data = value;
    next = nullptr;
    prev = nullptr;
}
