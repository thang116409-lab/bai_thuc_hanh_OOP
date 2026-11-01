# Danh Sách Bài Con Đã Triển Khai

## 1. Thiết kế lớp `Vehicle`

### 1.1. Khai báo thuộc tính riêng tư (Encapsulation)

- `vehicleID`
- `vehicleType`
- `entryTime`
- `parkingDuration`
- `parkingFee`
- `isOccupied`

### 1.2. Xây dựng Constructor

- Constructor mặc định
- Constructor có tham số

### 1.3. Xây dựng Getter / Setter

- Lấy và cập nhật thông tin xe
- Kiểm tra dữ liệu hợp lệ trước khi cập nhật

### 1.4. Chuẩn hóa loại phương tiện

- Không phân biệt chữ hoa/thường
- Chỉ chấp nhận:
  - Car
  - Motorcycle
  - Bicycle

### 1.5. Kiểm tra dữ liệu đầu vào

- Mã xe > 0
- Giờ vào từ 0–23
- Thời lượng đỗ từ 1–23
- Không cho phép đỗ qua đêm

### 1.6. Tính phí đỗ xe

- Xác định giờ cao điểm
- Tính phí 2 giờ đầu
- Tính phí từ giờ thứ 3 trở đi
- Quy đổi từ USD sang VND

### 1.7. Hiển thị thông tin xe

- In tiêu đề bảng
- In chi tiết thông tin xe

---

## 2. Thiết kế lớp `ParkingLot`

### 2.1. Khai báo thuộc tính riêng tư

- `parkID`
- `size`
- `vehicle1`
- `vehicle2`
- `vehicle3`
- `hasVehicle1`
- `hasVehicle2`
- `hasVehicle3`

### 2.2. Quản lý kích thước bãi đỗ

- S: tối đa 1 xe
- M: tối đa 2 xe
- L: tối đa 3 xe

### 2.3. Tính toán sức chứa

- Xác định số chỗ tối đa
- Đếm số xe hiện tại
- Tính số vị trí còn trống

### 2.4. Quản lý thông tin bãi đỗ

- Cập nhật mã bãi
- Cập nhật kích thước bãi
- Kiểm tra kích thước hợp lệ

### 2.5. Thêm xe vào bãi

- Kiểm tra xe hợp lệ
- Kiểm tra trùng mã xe
- Kiểm tra còn chỗ trống
- Tự động đưa vào vị trí phù hợp

### 2.6. Xóa xe khỏi bãi

- Tìm theo `vehicleID`
- Giải phóng vị trí chứa xe

### 2.7. Tìm kiếm xe

- Kiểm tra xe có tồn tại trong bãi hay không

### 2.8. Thống kê theo loại xe

- Đếm số xe theo loại
- Tính tổng phí theo loại

### 2.9. Tính tổng doanh thu bãi

- Cộng phí của tất cả xe trong bãi

### 2.10. Hiển thị thông tin bãi

- Hiển thị tóm tắt
- Hiển thị danh sách xe
- Hiển thị xe theo loại

---

## 3. Thiết kế lớp `SystemInterface`

### 3.1. Quản lý tối đa 3 bãi đỗ

- `parkingLot1`
- `parkingLot2`
- `parkingLot3`

### 3.2. Quản lý trạng thái tồn tại của bãi

- `hasLot1`
- `hasLot2`
- `hasLot3`

### 3.3. Các hàm hỗ trợ truy cập bãi

- Truy cập bãi theo vị trí
- Kiểm tra tồn tại
- Cập nhật trạng thái

### 3.4. Tìm kiếm bãi đỗ

- Tìm theo `parkID`
- Tìm theo `vehicleID`

### 3.5. Tìm vị trí trống

- Xác định nơi lưu bãi mới

### 3.6. Chọn bãi phù hợp để thêm xe

- Ưu tiên bãi còn ít chỗ trống nhất
- Tối ưu hoá việc lấp đầy bãi

### 3.7. Xử lý nhập dữ liệu an toàn

- Đọc số nguyên
- Đọc chuỗi
- Kiểm tra lỗi nhập liệu
- Xử lý EOF

### 3.8. Hiển thị tiền tệ

- Định dạng VND

---

# Các Chức Năng Menu Đã Hoàn Thành

## Menu 1 - Tạo bãi đỗ xe mới

### Chức năng

- Tạo tối đa 3 bãi đỗ
- Kiểm tra trùng mã bãi
- Kiểm tra kích thước hợp lệ

### Ràng buộc

- `parkID > 0`
- Size phải là:
  - S
  - M
  - L

---

## Menu 2 - Thêm xe vào bãi đỗ

### Chức năng

- Nhập thông tin xe
- Kiểm tra dữ liệu hợp lệ
- Tự động tính phí
- Tự động xếp bãi

### Kiểm tra

- Trùng mã xe
- Loại xe hợp lệ
- Không đỗ qua đêm
- Còn chỗ trống

---

## Menu 3 - Xóa bãi đỗ xe

### Chức năng

- Xóa bãi theo `parkID`
- Xóa toàn bộ xe trong bãi

---

## Menu 4 - Lấy xe ra khỏi bãi

### Chức năng

- Tìm xe theo `vehicleID`
- Xóa xe khỏi bãi

---

## Menu 5 - Hiển thị danh sách bãi đỗ

### Thông tin hiển thị

- Mã bãi
- Kích thước
- Số xe hiện có
- Sức chứa tối đa

---

## Menu 6 - Hiển thị xe theo bãi đỗ

### Thông tin hiển thị

- Mã xe
- Loại xe
- Giờ vào
- Thời gian đỗ
- Phí đỗ xe

---

## Menu 7 - Liệt kê xe theo loại

### Hỗ trợ

- Car
- Motorcycle
- Bicycle

### Kết quả

- Danh sách xe phù hợp
- Bãi đỗ tương ứng

---

## Menu 8 - Báo cáo phí đỗ xe

### Báo cáo toàn hệ thống

- Số lượng Car
- Số lượng Motorcycle
- Số lượng Bicycle
- Phí trung bình từng loại

### Báo cáo theo từng bãi

- Tổng doanh thu
- Doanh thu theo loại xe
- Phí trung bình theo loại

### Báo cáo cuối

- Tổng doanh thu hệ thống
- Tổng số xe đang đỗ

---

## Menu 9 - Thoát chương trình

### Chức năng

- Kết thúc chương trình
- Giải phóng luồng xử lý

---

# Các Yêu Cầu Đề Bài Đã Đáp Ứng

- ✅ Sử dụng OOP
- ✅ Tính đóng gói (Encapsulation)
- ✅ Constructor
- ✅ Getter / Setter
- ✅ Quản lý nhiều bãi đỗ
- ✅ Quản lý nhiều loại phương tiện
- ✅ Thêm xe
- ✅ Xóa xe
- ✅ Tìm kiếm xe
- ✅ Hiển thị danh sách
- ✅ Tính phí đỗ xe
- ✅ Thống kê doanh thu
- ✅ Không sử dụng con trỏ
- ✅ Không sử dụng mảng tĩnh
- ✅ Không sử dụng `std::array`
- ✅ Không sử dụng `std::vector`
- ✅ Chỉ dùng các biến đối tượng cố định theo đúng yêu cầu đề bài
