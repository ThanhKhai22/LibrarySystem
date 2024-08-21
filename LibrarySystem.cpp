#include <iostream>
#include "Library.h"

int main() {
    Library library; // Tạo đối tượng thư viện

    // Thêm sách vào thư viện
    library.addBook(Book(1, "Cuốn sách đầu tiên", "Tác giả A", "Thể loại X", 2024));
    library.addBook(Book(2, "Cuốn sách thứ hai", "Tác giả B", "Thể loại Y", 2024));
    library.addBook(Book(3, "Cuốn sách thứ ba", "Tác giả A", "Thể loại X", 2024));
    library.addBook(Book(4, "Cuốn sách thứ tư", "Tác giả C", "Thể loại Z", 2024));

    // Thêm người dùng vào thư viện
    library.addUser(User(1, "Nguyễn Văn A", "a@gmail.com", "0123456789"));
    library.addUser(User(2, "Trần Thị B", "b@gmail.com", "0987654321"));

    // Mượn sách cho người dùng với ID 1
    User* userA = library.findUserById(1);
    Book* book1 = library.findBookById(1);
    Book* book2 = library.findBookById(2);
    Book* book4 = library.findBookById(4);
    
    // Kiểm tra nếu người dùng và sách tồn tại trước khi thực hiện mượn sách
    if (userA && book1 && book2 && book4) {
        userA->borrowBook(*book1); // Người dùng mượn sách 1
        userA->borrowBook(*book2); // Người dùng mượn sách 2
        userA->borrowBook(*book4); // Người dùng mượn sách 4
    }

    // Đặt ngày mượn sách cho sách đã được mượn (giả định đã mượn 40 và 10 ngày trước)
    std::time_t now = std::time(nullptr); // Lấy thời gian hiện tại
    if (book1) book1->setBorrowedDate(now - 40 * 24 * 60 * 60); // Sách 1 đã mượn 40 ngày trước
    if (book2) book2->setBorrowedDate(now - 10 * 24 * 60 * 60); // Sách 2 đã mượn 10 ngày trước

    // Trả sách
    userA->returnBook(*book1); // Trả sách 1
    book1->setReturnedDate(now); // Cập nhật ngày trả sách 1

    // Tìm kiếm sách theo tên sách
    std::cout << "Tìm kiếm sách theo tên 'Cuốn sách thứ hai':\n";
    auto booksByTitle = library.searchByTitle("Cuốn sách thứ hai");
    for (const auto& book : booksByTitle) {
        std::cout << " - " << book.getTitle() << "\n";
    }

    // Tìm kiếm sách theo tác giả
    std::cout << "Tìm kiếm sách theo tác giả 'Tác giả A':\n";
    auto booksByAuthor = library.searchByAuthor("Tác giả A");
    for (const auto& book : booksByAuthor) {
        std::cout << " - " << book.getTitle() << "\n";
    }

    // Tìm kiếm sách theo thể loại
    std::cout << "Tìm kiếm sách theo thể loại 'Thể loại X':\n";
    auto booksByGenre = library.searchByGenre("Thể loại X");
    for (const auto& book : booksByGenre) {
        std::cout << " - " << book.getTitle() << "\n";
    }

    // Liệt kê tất cả các sách trong thư viện
    std::cout << "\nDanh sách tất cả sách trong thư viện:\n";
    library.listAllBooks();

    // Liệt kê tất cả các người dùng và sách mà họ đang mượn
    std::cout << "\nDanh sách người dùng và sách đã mượn:\n";
    library.listAllUsersAndBorrowedBooks();

    // Báo cáo các cuốn sách đang được mượn nhiều nhất
    std::cout << "\nBáo cáo các cuốn sách đang được mượn nhiều nhất:\n";
    library.reportMostBorrowedBooks();

    // Báo cáo danh sách các cuốn sách đã mượn nhưng chưa trả quá 30 ngày
    // std::cout << "\nBáo cáo danh sách các cuốn sách đã mượn nhưng chưa trả quá 30 ngày:\n";
    // library.reportBooksNotReturnedIn30Days();

    // Lưu dữ liệu vào file
    library.saveDataToFile("library_data.txt");

    // Tải dữ liệu từ file (bình luận ra ngoài nếu chưa cần sử dụng)
    // Library newLibrary;
    // newLibrary.loadDataFromFile("library_data.txt");

    // // Hiển thị dữ liệu đã tải từ file
    // std::cout << "\nDanh sách tất cả sách trong thư viện (sau khi tải từ file):\n";
    // newLibrary.listAllBooks();

    // std::cout << "\nDanh sách người dùng và sách đã mượn (sau khi tải từ file):\n";
    // newLibrary.listAllUsersAndBorrowedBooks();

    return 0;
}
