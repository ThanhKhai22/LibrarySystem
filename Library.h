#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <map>
#include "Book.h"
#include "User.h"

class Library {
private:
    std::vector<Book> books; // Danh sách các cuốn sách trong thư viện
    std::vector<User> users; // Danh sách các người dùng của thư viện

public:
    // Thêm sách mới vào thư viện
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Thêm người dùng mới vào thư viện
    void addUser(const User& user) {
        users.push_back(user);
    }

    // Tìm người dùng theo ID
    User* findUserById(int id) {
        for (auto& user : users) {
            if (user.getId() == id) {
                return &user; // Trả về con trỏ tới người dùng nếu tìm thấy
            }
        }
        return nullptr; // Trả về nullptr nếu không tìm thấy người dùng
    }

    // Tìm sách theo ID
    Book* findBookById(int id) const {
        for (const auto& book : books) {
            if (book.getId() == id) {
                return const_cast<Book*>(&book); // Ép kiểu const_cast để trả về Book*
            }
        }
        return nullptr; // Trả về nullptr nếu không tìm thấy sách
    }

    // Tìm sách theo tiêu đề
    std::vector<Book> searchByTitle(const std::string& title) const {
        std::vector<Book> results;
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                results.push_back(book); // Thêm sách vào kết quả nếu tiêu đề khớp
            }
        }
        return results;
    }

    // Tìm sách theo tác giả
    std::vector<Book> searchByAuthor(const std::string& author) const {
        std::vector<Book> results;
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                results.push_back(book); // Thêm sách vào kết quả nếu tác giả khớp
            }
        }
        return results;
    }

    // Tìm sách theo thể loại
    std::vector<Book> searchByGenre(const std::string& genre) const {
        std::vector<Book> results;
        for (const auto& book : books) {
            if (book.getGenre() == genre) {
                results.push_back(book); // Thêm sách vào kết quả nếu thể loại khớp
            }
        }
        return results;
    }

    // Liệt kê tất cả sách trong thư viện
    void listAllBooks() const {
        std::cout << "Danh sách tất cả sách trong thư viện:\n";
        for (const auto& book : books) {
            std::cout << "ID: " << book.getId() 
                      << ", Tên sách: " << book.getTitle() 
                      << ", Tác giả: " << book.getAuthor() 
                      << ", Thể loại: " << book.getGenre() 
                      << ", Năm xuất bản: " << book.getYear() 
                      << ", Trạng thái: " << (book.getStatus() ? "Còn trong thư viện" : "Đã được mượn") 
                      << std::endl;
        }
    }

    // Liệt kê tất cả người dùng và các sách họ đã mượn
    void listAllUsersAndBorrowedBooks() const {
        std::cout << "Danh sách người dùng và sách đã mượn:\n";
        for (const auto& user : users) {
            std::cout << "Người dùng: " << user.getName() << "\nDanh sách sách đã mượn:\n";
            for (const auto& book : user.getBorrowedBooks()) {
                std::cout << " - " << book->getTitle() << std::endl;
            }
        }
    }

    // Báo cáo các cuốn sách được mượn nhiều nhất
    void reportMostBorrowedBooks() const {
        std::map<int, int> borrowCount; // Lưu số lần mượn mỗi sách

        // Đếm số lần mượn mỗi cuốn sách
        for (const auto& user : users) {
            for (const auto& book : user.getBorrowedBooks()) {
                borrowCount[book->getId()]++;
            }
        }

        // Sắp xếp sách theo số lần mượn giảm dần
        std::vector<std::pair<int, int>> sortedBooks(borrowCount.begin(), borrowCount.end());
        std::sort(sortedBooks.begin(), sortedBooks.end(), [](const auto& a, const auto& b) {
            return a.second > b.second; // Sắp xếp giảm dần theo số lần mượn
        });

        // Hiển thị báo cáo các cuốn sách được mượn nhiều nhất
        std::cout << "Các cuốn sách được mượn nhiều nhất:\n";
        for (const auto& entry : sortedBooks) {
            Book* book = findBookById(entry.first);
            if (book) {
                std::cout << " - " << book->getTitle() << ": " << entry.second << " lần mượn\n";
            }
        }
    }

    // Báo cáo danh sách sách đã mượn nhưng chưa trả quá 30 ngày
    void reportBooksNotReturnedIn30Days() const {
        std::time_t now = std::time(nullptr); // Lấy thời gian hiện tại
        std::cout << "Danh sách sách đã mượn nhưng chưa trả quá 30 ngày:\n";
        for (const auto& book : books) {
            if (!book.getStatus() && book.getBorrowedDate() != 0) {
                // Tính số ngày đã mượn
                double daysBorrowed = std::difftime(now, book.getBorrowedDate()) / (60 * 60 * 24);
                if (daysBorrowed > 30) {
                    std::cout << " - " << book.getTitle() << " (Đã mượn từ " << daysBorrowed << " ngày trước)\n";
                }
            }
        }
    }

    // Lưu dữ liệu sách và người dùng vào file
    void saveDataToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Không thể mở file để ghi");
        }

        // Lưu sách
        for (const auto& book : books) {
            book.saveToFile(outFile);
        }

        // Lưu người dùng
        for (const auto& user : users) {
            user.saveToFile(outFile);
        }

        outFile.close();
    }

    // Tải dữ liệu sách và người dùng từ file
    void loadDataFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Không thể mở file để đọc");
        }

        std::string line;
        std::vector<std::string> userLines;

        // Đọc dữ liệu sách
        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;

            while (std::getline(ss, item, ',')) {
                tokens.push_back(item);
            }

            // Xử lý dữ liệu sách
            if (tokens.size() == 6) {
                int id = std::stoi(tokens[0]);
                std::string title = tokens[1];
                std::string author = tokens[2];
                std::string genre = tokens[3];
                int year = std::stoi(tokens[4]);
                bool status = tokens[5] == "1"; // 1: available, 0: borrowed

                Book book(id, title, author, genre, year);
                book.setStatus(status);
                if (!status) {
                    std::time_t borrowedDate = std::stoll(tokens[6]);
                    std::time_t returnedDate = std::stoll(tokens[7]);
                    book.setBorrowedDate(borrowedDate);
                    book.setReturnedDate(returnedDate);
                }
                books.push_back(book);
            } else if (tokens.size() >= 4) {
                userLines.push_back(line);
            }
        }

        // Đọc dữ liệu người dùng và cập nhật sách đã mượn
        for (const auto& userLine : userLines) {
            std::istringstream ss(userLine);
            std::string item;
            std::vector<std::string> tokens;

            while (std::getline(ss, item, ',')) {
                tokens.push_back(item);
            }

            // Xử lý dữ liệu người dùng
            if (tokens.size() >= 4) {
                int id = std::stoi(tokens[0]);
                std::string name = tokens[1];
                std::string email = tokens[2];
                std::string phoneNumber = tokens[3];

                User user(id, name, email, phoneNumber);
                users.push_back(user);

                // Cập nhật sách đã mượn cho người dùng
                for (size_t i = 4; i < tokens.size(); ++i) {
                    int bookId = std::stoi(tokens[i]);
                    Book* book = findBookById(bookId);
                    if (book) {
                        user.borrowBook(*book); // Cập nhật sách đã mượn cho người dùng
                    }
                }
            }
        }

        inFile.close();
    }
};

#endif
