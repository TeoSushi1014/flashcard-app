#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "mylist.h"

using namespace std;

const string FILENAME = "data.txt";

// Hàm cắt chuỗi "front;back"
bool splitString(const string &str, string &f, string &b) {
    size_t pos = str.find(';');
    if (pos == string::npos) return false;
    f = str.substr(0, pos);
    b = str.substr(pos + 1);
    return true;
}

// Đọc file vào danh sách
void loadData(DoublyLinkedList &deck) {
    ifstream file(FILENAME);
    if (!file.is_open()) {
        cout << "Khong the mo file " << FILENAME << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string f, b;
        if (splitString(line, f, b)) {
            deck.addNode(f, b);
        }
    }
    file.close();
}

int main() {

    DoublyLinkedList deck;
    loadData(deck);

    Node* currentCard = deck.getHead();

    char choice;
    bool showFront = true;

    while (true) {

        system("cls");
        cout << "============= FLASHCARD (" << deck.getSize() << " the) =============" << endl;

        if (currentCard == nullptr) {
            if (deck.getHead() != nullptr) {
                currentCard = deck.getHead();
            } else {
                cout << "\n     [ BAN DA HET THE! ]\n\n";
                cout << "[Q] Thoat\n";
                cin >> choice;
                return 0;
            }
        }

        if (showFront)
            cout << "\n[ MAT TRUOC ]\n\n   " << currentCard->front << "\n\n";
        else
            cout << "\n[ MAT SAU ]\n\n   " << currentCard->back << "\n\n";

        cout << "====================================================\n";
        cout << "[F] Lat the  |  [N] Tiep theo  |  [P] Quay lai\n";
        cout << "[D] Xoa the  |  [Q] Thoat\n";
        cout << "Nhap lua chon: ";
        
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (tolower(choice)) {

        case 'f':
            showFront = !showFront;
            break;

        case 'n':
            if (currentCard->next) {
                currentCard = currentCard->next;
                showFront = true;
            } else {
                cout << "\n>> Day la the cuoi cung! <<\n";
                system("pause");
            }
            break;

        case 'p':
            if (currentCard->prev) {
                currentCard = currentCard->prev;
                showFront = true;
            } else {
                cout << "\n>> Day la the dau tien! <<\n";
                system("pause");
            }
            break;

        case 'd': {
            Node* toDelete = currentCard;

            if (toDelete->next) currentCard = toDelete->next;
            else currentCard = toDelete->prev;

            deck.deleteNode(toDelete);
            deck.saveToFile(FILENAME);  // <-- LƯU LẠI FILE

            showFront = true;
            cout << "\n>> Da xoa the! <<\n";
            Sleep(500);
            break;
        }

        case 'q':
            cout << "Tam biet!\n";
            return 0;

        default:
            cout << "Lua chon khong hop le!\n";
            system("pause");
        }
    }
}
