#include "Node.h"
#include "DoublyLinkedList.h"
#include <iostream>
#include <string>

void printMenu() {
    std::cout << "\n=== FLASHCARD APP - DOUBLY LINKED LIST ===\n";
    std::cout << "1. Thêm thẻ từ vựng vào cuối (append)\n";
    std::cout << "2. Thêm thẻ từ vựng vào đầu (prepend)\n";
    std::cout << "3. Xóa thẻ từ vựng (deleteNode)\n";
    std::cout << "4. Tìm thẻ theo vị trí (findByIndex)\n";
    std::cout << "5. Duyệt danh sách xuôi (traverseForward)\n";
    std::cout << "6. Duyệt danh sách ngược (traverseBackward)\n";
    std::cout << "7. Demo đầy đủ các chức năng\n";
    std::cout << "0. Thoát\n";
    std::cout << "Chọn: ";
}

void demoFull(DoublyLinkedList& dll) {
    std::cout << "\n=== DEMO ĐẦY ĐỦ CÁC CHỨC NĂNG ===\n\n";
    
    std::cout << "1. Thêm 3 thẻ vào cuối:\n";
    dll.append("hello");
    dll.append("world");
    dll.append("goodbye");
    std::cout << "   Danh sách sau khi append: ";
    dll.traverseForward();
    
    std::cout << "\n2. Thêm 1 thẻ vào đầu:\n";
    dll.prepend("first");
    std::cout << "   Danh sách sau khi prepend: ";
    dll.traverseForward();
    
    std::cout << "\n3. Duyệt xuôi:\n   ";
    dll.traverseForward();
    
    std::cout << "\n4. Duyệt ngược:\n   ";
    dll.traverseBackward();
    
    std::cout << "\n5. Tìm thẻ ở vị trí 2:\n";
    Node* found = dll.findByIndex(2);
    if (found) {
        std::cout << "   Tìm thấy: " << found->data << std::endl;
    } else {
        std::cout << "   Không tìm thấy\n";
    }
    
    std::cout << "\n6. Xóa thẻ 'world':\n";
    if (dll.deleteNode("world")) {
        std::cout << "   Đã xóa thành công!\n";
        std::cout << "   Danh sách sau khi xóa: ";
        dll.traverseForward();
    } else {
        std::cout << "   Không tìm thấy để xóa\n";
    }
    
    std::cout << "\n7. Duyệt ngược sau khi xóa:\n   ";
    dll.traverseBackward();
    
    std::cout << "\n=== KẾT THÚC DEMO ===\n";
}

int main() {
    DoublyLinkedList dll;
    int choice;
    std::string value;
    int index;
    
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: {
                std::cout << "Nhập từ vựng cần thêm vào cuối: ";
                std::getline(std::cin, value);
                dll.append(value);
                std::cout << "Đã thêm '" << value << "' vào cuối danh sách.\n";
                break;
            }
            case 2: {
                std::cout << "Nhập từ vựng cần thêm vào đầu: ";
                std::getline(std::cin, value);
                dll.prepend(value);
                std::cout << "Đã thêm '" << value << "' vào đầu danh sách.\n";
                break;
            }
            case 3: {
                std::cout << "Nhập từ vựng cần xóa: ";
                std::getline(std::cin, value);
                if (dll.deleteNode(value)) {
                    std::cout << "Đã xóa '" << value << "' thành công!\n";
                } else {
                    std::cout << "Không tìm thấy '" << value << "' trong danh sách.\n";
                }
                break;
            }
            case 4: {
                std::cout << "Nhập vị trí cần tìm (bắt đầu từ 0): ";
                std::cin >> index;
                Node* found = dll.findByIndex(index);
                if (found) {
                    std::cout << "Tìm thấy tại vị trí " << index << ": " << found->data << std::endl;
                } else {
                    std::cout << "Không tìm thấy tại vị trí " << index << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Danh sách từ đầu đến cuối:\n";
                dll.traverseForward();
                break;
            }
            case 6: {
                std::cout << "Danh sách từ cuối về đầu:\n";
                dll.traverseBackward();
                break;
            }
            case 7: {
                DoublyLinkedList demoList;
                demoFull(demoList);
                break;
            }
            case 0: {
                std::cout << "Cảm ơn bạn đã sử dụng Flashcard App!\n";
                break;
            }
            default: {
                std::cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                break;
            }
        }
    } while (choice != 0);
    
    return 0;
}

