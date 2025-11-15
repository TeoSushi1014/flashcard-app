#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// Thêm thư viện này để dùng try-catch cho stoi
#include <stdexcept> 

using namespace std;

struct Flashcard {
    string front;
    string back;
};

vector<Flashcard> cards;
int cur = 0;
const string FILE_NAME = "data.txt";

// ---------------- FILE I/O ----------------
void loadFile() {
    cards.clear();
    ifstream f(FILE_NAME);
    string line;

    while (getline(f, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            Flashcard c;
            c.front = line.substr(0, pos);
            c.back  = line.substr(pos + 1);
            cards.push_back(c);
        }
    }
}

void saveFile() {
    ofstream f(FILE_NAME);
    for (auto &c : cards) {
        f << c.front << "|" << c.back << "\n";
    }
}

// ---------------- FUNCTION ----------------

// ***** HÀM MỚI *****
void addCard() {
    Flashcard c;
    cout << "Nhập mặt trước: ";
    getline(cin, c.front);
    cout << "Nhập mặt sau : ";
    getline(cin, c.back);

    cards.push_back(c);
    // Tự động trỏ tới thẻ vừa thêm
    cur = cards.size() - 1; 
    cout << "Đã thêm thẻ mới. Tổng số thẻ: " << cards.size() << "\n";
}

void showCard() {
    if (cards.empty()) {
        cout << "Không có thẻ. Hãy thêm thẻ mới (chọn 5).\n";
        return;
    }
    cout << "\n--- Thẻ " << cur + 1 << "/" << cards.size() << " ---\n";
    cout << "Front: " << cards[cur].front << "\n";
    cout << "Back : " << cards[cur].back << "\n";
}

void nextCard() {
    if (!cards.empty()) cur = (cur + 1) % cards.size();
}

void prevCard() {
    if (!cards.empty()) cur = (cur - 1 + cards.size()) % cards.size();
}

void searchCard() {
    cout << "Nhập từ khóa: ";
    string key; 
    getline(cin, key);

    bool found = false;
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].front.find(key) != string::npos ||
            cards[i].back.find(key) != string::npos) {
            cout << "Tìm thấy ở thẻ " << i + 1 << ": "
                 << cards[i].front << " - " << cards[i].back << "\n";
            found = true;
        }
    }

    if (!found) cout << "Không tìm thấy.\n";
}

void updateCard() {
    if (cards.empty()) {
        cout << "Không có thẻ để sửa.\n";
        return;
    }

    cout << "Nhập số thẻ muốn sửa (1 đến " << cards.size() << "): ";
    string s;
    getline(cin, s);

    int n;
    try { n = stoi(s); } 
    catch (...) { cout << "Sai định dạng.\n"; return; }

    n--;
    if (n < 0 || n >= cards.size()) {
        cout << "Sai số thẻ.\n";
        return;
    }

    cout << "Front cũ: " << cards[n].front << "\n";
    cout << "Front mới: ";
    getline(cin, cards[n].front);

    cout << "Back cũ : " << cards[n].back << "\n";
    cout << "Back mới : ";
    getline(cin, cards[n].back);

    cout << "Đã cập nhật.\n";
}

void deleteCard() {
    if (cards.empty()) {
        cout << "Không có thẻ để xóa.\n";
        return;
    }

    cout << "Nhập số thẻ muốn xóa (1 đến " << cards.size() << "): ";
    string s;
    getline(cin, s);

    int n;
    try { n = stoi(s); } 
    catch (...) { cout << "Sai định dạng.\n"; return; }

    n--;

    if (n < 0 || n >= cards.size()) {
        cout << "Sai số thẻ.\n";
        return;
    }

    // Thêm xác nhận
    cout << "Bạn có chắc muốn xóa thẻ " << n + 1 << ": '" << cards[n].front << "'? (y/n): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y") {
        cards.erase(cards.begin() + n);
        cout << "Đã xóa.\n";

        // Cập nhật vị trí hiện tại
        if (cards.empty()) cur = 0;
        else if (cur >= cards.size()) cur = cards.size() - 1;
    } else {
        cout << "Đã hủy xóa.\n";
    }
}
void showAllCards() {
    if (cards.empty()) {
        cout << "Không có thẻ.\n";
        return;
    }

    cout << "\n===== DANH SÁCH TOÀN BỘ THẺ =====\n";
    for (int i = 0; i < cards.size(); i++) {
        cout << i + 1 << ". " 
             << cards[i].front 
             << " - " 
             << cards[i].back << "\n";
    }
    cout << "=================================\n";
}

// ---------------- MENU ----------------
void menu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Xem thẻ hiện tại\n";
    cout << "2. Next\n";
    cout << "3. Previous\n";
    cout << "4. Tìm kiếm\n";
    cout << "5. Thêm thẻ mới\n";       
    cout << "6. Xóa thẻ\n";         
    cout << "7. Cập nhật nội dung thẻ\n"; 
    cout << "8. Đếm số thẻ\n";       
    cout << "9. Lưu dữ liệu\n";  
    cout << "10. Hiển thị tất cả thẻ\n";
    cout << "0. Thoát\n";
    cout << "Chọn: ";
}

int main() {
    loadFile();
    cout << "Tải xong " << cards.size() << " thẻ.\n";

    while (true) {
        menu();
        string c;
        getline(cin, c);

        if (c == "1") showCard();
        else if (c == "2") nextCard();
        else if (c == "3") prevCard();
        else if (c == "4") searchCard();
        else if (c == "5") addCard();      
        else if (c == "6") deleteCard();
        else if (c == "7") updateCard();   
        else if (c == "8") cout << "Tổng số thẻ: " << cards.size() << "\n"; 
        else if (c == "9") { saveFile(); cout << "Đã lưu.\n"; }         
        else if (c == "10") showAllCards();
        else if (c == "0") break;
        else cout << "Sai lựa chọn.\n";
    }

    return 0;
}