#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

class Book {
private:
    int id; // Mã định danh của sách
    std::string title; // Tên sách
    std::string author; // Tác giả của sách
    std::string genre; // Thể loại của sách
    int year; // Năm xuất bản
    bool isAvailable; // Trạng thái của sách (còn trong thư viện hay đã được mượn)
    std::time_t borrowedDate; // Thời gian sách được mượn
    std::time_t returnedDate; // Thời gian sách được trả

public:
    // Constructor để khởi tạo sách với các thông tin cơ bản
    Book(int id, const std::string& title, const std::string& author, const std::string& genre, int year)
        : id(id), title(title), author(author), genre(genre), year(year), isAvailable(true), borrowedDate(0), returnedDate(0) {}

    // Getter cho mã sách
    int getId() const { return id; }

    // Getter cho tên sách
    std::string getTitle() const { return title; }

    // Getter cho tác giả sách
    std::string getAuthor() const { return author; }

    // Getter cho thể loại sách
    std::string getGenre() const { return genre; }

    // Getter cho năm xuất bản
    int getYear() const { return year; }

    // Getter cho trạng thái sách (còn trong thư viện hay đã được mượn)
    bool getStatus() const { return isAvailable; }

    // Setter cho trạng thái sách
    void setStatus(bool status) { isAvailable = status; }

    // Getter cho thời gian mượn sách
    std::time_t getBorrowedDate() const { return borrowedDate; }

    // Setter cho thời gian mượn sách
    void setBorrowedDate(std::time_t date) { borrowedDate = date; }

    // Getter cho thời gian trả sách
    std::time_t getReturnedDate() const { return returnedDate; }

    // Setter cho thời gian trả sách
    void setReturnedDate(std::time_t date) { returnedDate = date; }

    // Hiển thị thông tin sách
    void display() const {
        std::cout << "Mã sách: " << id << "\nTên sách: " << title
                  << "\nTác giả: " << author << "\nThể loại: " << genre
                  << "\nNăm xuất bản: " << year
                  << "\nTrạng thái: " << (isAvailable ? "Còn trong thư viện" : "Đã được mượn") << std::endl;
    }

    // Lưu thông tin sách vào file
    void saveToFile(std::ofstream& outFile) const {
        outFile << id << "," << title << "," << author << "," << genre
                << "," << year << "," << isAvailable << ",";
        // Nếu sách đang có trong thư viện (chưa được mượn), ghi "0,0" cho ngày mượn và trả
        if (isAvailable) {
            outFile << "0,0\n";
        } else {
            // Nếu sách đã được mượn, ghi ngày mượn và ngày trả
            outFile << borrowedDate << "," << returnedDate << "\n";
        }
    }
};

#endif
