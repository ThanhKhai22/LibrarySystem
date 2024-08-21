# Hướng Dẫn Sử Dụng Hệ Thống Quản Lý Thư Viện Sách

## Mô Tả
Hệ thống quản lý thư viện sách cho phép bạn thực hiện các thao tác cơ bản như thêm sách, thêm người dùng, mượn và trả sách, tìm kiếm sách theo các tiêu chí khác nhau, và báo cáo tình trạng sách.

## Cài Đặt

### Clone Repository
Clone repository về máy tính của bạn:
```bash
git clone https://github.com/ThanhKhai22/LibrarySystem.git
```

## Sử Dụng

### 1. Thêm Sách vào Thư Viện
Để thêm sách vào hệ thống, bạn có thể sử dụng hàm addBook của lớp Library. Ví dụ: 
```bash
library.addBook(Book(1, "Cuốn sách đầu tiên", "Tác giả A", "Thể loại X", 2024));
```

### 2. Thêm Người Dùng vào Thư Viện
Thêm người dùng mới vào hệ thống bằng cách sử dụng hàm addUser:
```bash
library.addUser(User(1, "Nguyễn Văn A", "a@gmail.com", "0123456789"));
```

### 3. Mượn Sách
Để cho một người dùng mượn sách, tìm người dùng và sách theo ID và gọi hàm borrowBook:
```bash
User* userA = library.findUserById(1);
Book* book1 = library.findBookById(1);
if (userA && book1) {
    userA->borrowBook(*book1);
}

```

### 4. Trả Sách
Khi người dùng trả sách, sử dụng hàm returnBook và cập nhật ngày trả sách:
```bash
userA->returnBook(*book1);
book1->setReturnedDate(std::time(nullptr));
```

### Tìm Kiếm Sách
Theo tên sách:
```bash
auto booksByTitle = library.searchByTitle("Cuốn sách thứ hai");
```

Theo tác giả:
```bash
auto booksByAuthor = library.searchByAuthor("Tác giả A");
```

Theo thể loại:
```bash
auto booksByGenre = library.searchByGenre("Thể loại X");
```

### 6. Liệt Kê Tất Cả Các Sách và Người Dùng

Danh sách tất cả sách:
```bash
library.listAllBooks();
```

Danh sách người dùng và sách đã mượn:
```bash
library.listAllUsersAndBorrowedBooks();
```

### 7. Báo Cáo

Các cuốn sách đang được mượn nhiều nhất:

```bash
library.reportMostBorrowedBooks();
```







