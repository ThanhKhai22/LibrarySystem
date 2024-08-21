#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include "Book.h"

class User {
private:
    int id; // Mã định danh của người dùng
    std::string name; // Tên của người dùng
    std::string email; // Email của người dùng
    std::string phoneNumber; // Số điện thoại của người dùng
    std::vector<Book*> borrowedBooks; // Danh sách các cuốn sách đã mượn

public:
    // Constructor để khởi tạo người dùng với các thông tin cơ bản
    User(int id, const std::string& name, const std::string& email, const std::string& phoneNumber)
        : id(id), name(name), email(email), phoneNumber(phoneNumber) {}

    // Getter cho mã người dùng
    int getId() const { return id; }

    // Getter cho tên người dùng
    std::string getName() const { return name; }

    // Getter cho email người dùng
    std::string getEmail() const { return email; }

    // Getter cho số điện thoại người dùng
    std::string getPhoneNumber() const { return phoneNumber; }

    // Getter cho danh sách sách đã mượn
    const std::vector<Book*>& getBorrowedBooks() const { return borrowedBooks; }

    // Phương thức mượn sách
    void borrowBook(Book& book) {
        // Kiểm tra nếu sách có sẵn (trạng thái là còn trong thư viện)
        if (book.getStatus()) {
            borrowedBooks.push_back(&book); // Thêm sách vào danh sách đã mượn
            book.setStatus(false); // Cập nhật trạng thái của cuốn sách là đã mượn
            std::time_t now = std::time(nullptr); // Lấy thời gian hiện tại
            book.setBorrowedDate(now); // Lưu ngày mượn
            std::cout << name << " đã mượn sách: " << book.getTitle() << std::endl;
        } else {
            // Ném lỗi nếu sách đã được mượn
            throw std::runtime_error("Sách đã được mượn");
        }
    }

    // Phương thức trả sách
    void returnBook(Book& book) {
        // Tìm sách trong danh sách đã mượn
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), &book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it); // Xóa sách khỏi danh sách đã mượn
            book.setStatus(true); // Cập nhật trạng thái của cuốn sách là còn trong thư viện
            std::time_t now = std::time(nullptr); // Lấy thời gian hiện tại
            book.setReturnedDate(now); // Lưu ngày trả
            std::cout << name << " đã trả sách: " << book.getTitle() << std::endl;
        } else {
            // Ném lỗi nếu sách không nằm trong danh sách đã mượn
            throw std::runtime_error("Không tìm thấy sách trong danh sách mượn");
        }
    }

    // Hiển thị danh sách sách đã mượn
    void displayBorrowedBooks() const {
        std::cout << "Người dùng: " << name << "\nDanh sách sách đã mượn:\n";
        for (const auto& book : borrowedBooks) {
            std::cout << " - " << book->getTitle() << std::endl; // Hiển thị tên sách
        }
    }

    // Lưu thông tin người dùng và các sách đã mượn vào file
    void saveToFile(std::ofstream& outFile) const {
        outFile << id << "," << name << "," << email << "," << phoneNumber;
        for (const auto& book : borrowedBooks) {
            outFile << "," << book->getId(); // Ghi mã sách vào file
        }
        outFile << "\n"; // Kết thúc dòng
    }
};

#endif
