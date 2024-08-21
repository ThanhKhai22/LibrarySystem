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
