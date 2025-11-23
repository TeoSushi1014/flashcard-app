#include "DoublyLinkedList.h"
#include <chrono>
#include <fstream>
#include <iostream>

void TestPerformance(int cardCount) {
    DoublyLinkedList list;
    
    // Test 1: Thêm thẻ vào cuối
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < cardCount; i++) {
        std::string card = "Question " + std::to_string(i) + " / Answer " + std::to_string(i);
        list.append(card);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto appendTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    // Test 2: Tìm thẻ giữa
    start = std::chrono::high_resolution_clock::now();
    auto midCard = list.findByIndex(cardCount / 2);
    end = std::chrono::high_resolution_clock::now();
    auto findTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // Test 3: Xóa thẻ đầu
    // Tìm thẻ đầu tiên để xóa
    Node* firstCard = list.findByIndex(0);
    start = std::chrono::high_resolution_clock::now();
    if (firstCard) {
        list.deleteNode(firstCard->data);
    }
    end = std::chrono::high_resolution_clock::now();
    auto deleteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // In kết quả
    std::cout << "\n=== Test với " << cardCount << " thẻ ===" << std::endl;
    std::cout << "Thời gian thêm: " << appendTime << " ms" << std::endl;
    std::cout << "Thời gian tìm: " << findTime << " μs" << std::endl;
    std::cout << "Thời gian xóa: " << deleteTime << " μs" << std::endl;
}

int main() {
    // Test với 3 kích thước khác nhau
    TestPerformance(10);
    TestPerformance(100);
    TestPerformance(1000);
    
    return 0;
}

