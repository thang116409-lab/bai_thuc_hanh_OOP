# BÀI TẬP THỰC HÀNH OOP HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE - GIAI ĐOẠN 1

**Giảng viên:** Nguyễn Hạnh Phúc - FIT - VMU

**Ngôn ngữ lập trình:** C++ (Chuẩn C++11 trở lên)

---

# Đề bài chung cho tất cả các giai đoạn

Sinh viên sẽ thiết kế và xây dựng một hệ thống quản lý bãi đỗ xe bằng C++ theo nguyên lý OOP.

Hệ thống cho phép:

- Tạo và quản lý nhiều bãi đỗ xe (*Parking Lots*) với các kích thước khác nhau.
- Tạo và quản lý nhiều phương tiện (*Vehicles*) như ô tô, xe máy, xe đạp.
- Thực hiện các thao tác: thêm, xóa, tìm kiếm, hiển thị thông tin.
- Tính toán phí đỗ xe theo quy tắc nghiệp vụ.
- Thống kê và báo cáo dữ liệu.

## Yêu cầu cốt lõi

Xây dựng các lớp đối tượng:

- `ParkingLot`
- `Vehicle`
- `SystemInterface`

và xử lý các thao tác thêm, xóa, hiển thị thông tin một cách có tổ chức, đúng đắn về mặt thiết kế OOP.

---

# 1. MỤC TIÊU & YÊU CẦU KỸ THUẬT

## Chủ đề

- Đóng gói (Encapsulation)
- Thiết kế Lớp (Class)
- Biến đơn và Luồng điều khiển cơ bản

## Mục tiêu

Thiết kế ứng dụng console hướng đối tượng quản lý bãi đỗ xe cho một công ty.

## Hạn chế bắt buộc (Strict Constraints)

### 1. TÍNH ĐÓNG GÓI

Tất cả các thuộc tính (*instance variables*) của lớp phải ở phạm vi `private`.

Tương tác dữ liệu bắt buộc thông qua các phương thức `public`:

- Getters
- Setters
- Constructors

### 2. KHÔNG SỬ DỤNG MẢNG VÀ CON TRỎ

Tuyệt đối **KHÔNG** sử dụng:

- Mảng tĩnh (C-style array)
- Mảng C++ (`std::array`)
- Mảng động/Vector (`std::vector`)
- Con trỏ (`pointers`)
- `new`
- `delete`

### 3. LƯU TRỮ

Quản lý số lượng đối tượng cố định thông qua:

- Các biến đối tượng đơn lẻ
- Các biến cờ trạng thái (`boolean flags`)

---

# 2. CẤU TRÚC VÀ THIẾT KẾ CÁC LỚP (CLASS SPECIFICATIONS)

## 2.1. Lớp `Vehicle` (Đại diện cho một phương tiện đỗ)

### Thuộc tính (`private`)

#### `int vehicleID`

Mã định danh duy nhất của xe.

#### `std::string vehicleType`

Loại xe (Chỉ nhận 3 giá trị):

- `"Car"`
- `"Motorcycle"`
- `"Bicycle"`

Không phân biệt chữ hoa/thường.

#### `int entryTime`

Giờ vào bãi:

- Số nguyên từ `0` đến `23`
- `0 = 12am`
- `23 = 11pm`

#### `int parkingDuration`

Số giờ đỗ dự kiến:

- Số nguyên từ `1` đến `23`
- Đảm bảo trong cùng một ngày

#### `double parkingFee`

Phí đỗ xe được tính toán.

Đơn vị: VNĐ.

#### `bool isOccupied`

Cờ xác định vị trí xe này có đang chứa dữ liệu thực hay không.

Giá trị mặc định:

```cpp
false
```

### Phương thức (`public`)

#### Constructor

- Constructor mặc định
- Constructor có tham số đầy đủ

#### Getters / Setters

Cho tất cả thuộc tính.

#### Hàm tính phí

```cpp
void calculateFee();
```

Hàm tính phí đỗ xe tự động theo quy tắc ở Mục 3.

#### Hiển thị thông tin

```cpp
void display();
```

In thông tin chi tiết của xe ra màn hình.

---

## 2.2. Lớp `ParkingLot` (Đại diện cho một bãi đỗ xe)

### Thuộc tính (`private`)

#### `int parkID`

Mã định danh bãi đỗ xe.

#### `char size`

Kích thước bãi đỗ:

- `'S'` - Small
- `'M'` - Medium
- `'L'` - Large

##### S (Small)

Chứa tối đa:

```text
1 xe
```

Sử dụng:

```cpp
vehicle1
```

##### M (Medium)

Chứa tối đa:

```text
2 xe
```

Sử dụng:

```cpp
vehicle1
vehicle2
```

##### L (Large)

Chứa tối đa:

```text
3 xe
```

Sử dụng:

```cpp
vehicle1
vehicle2
vehicle3
```

#### Các đối tượng xe

```cpp
Vehicle vehicle1;
Vehicle vehicle2;
Vehicle vehicle3;
```

#### Các cờ trạng thái

```cpp
bool hasVehicle1;
bool hasVehicle2;
bool hasVehicle3;
```

Dùng để kiểm tra trạng thái ô trống.

### Phương thức (`public`)

#### Constructor

- Constructor mặc định
- Constructor khởi tạo theo:

```cpp
parkID
size
```

#### Thêm xe

```cpp
bool addVehicle(const Vehicle& v);
```

Thêm xe vào ô trống phù hợp theo sức chứa của `size`.

#### Xóa xe

```cpp
bool removeVehicle(int vID);
```

Xóa xe khỏi bãi theo mã `vehicleID`.

#### Hiển thị thông tin bãi

```cpp
void displayLotInfo();
```

Hiển thị:

- ID bãi
- Kích thước
- Danh sách các xe hiện có

---

## 2.3. Lớp `SystemInterface` (Giao diện và điều hành hệ thống)

### Thuộc tính (`private`)

```cpp
ParkingLot parkingLot1;
ParkingLot parkingLot2;
ParkingLot parkingLot3;
```

Quản lý tối đa 3 bãi đỗ xe đơn lẻ.

#### Các cờ trạng thái

```cpp
bool hasLot1;
bool hasLot2;
bool hasLot3;
```

Theo dõi sự tồn tại của các bãi đỗ.

### Phương thức (`public`)

#### Menu điều khiển hệ thống

```cpp
void runMenu();
```

Yêu cầu:

- Là lớp duy nhất chứa hàm `main()`.
- Là lớp duy nhất xử lý nhập/xuất Console:
  - `std::cin`
  - `std::cout`

Chức năng:

- Hiển thị menu
- Điều phối toàn bộ chức năng chương trình

---

# 3. QUY TẮC TÍNH PHÍ ĐỖ XE (PARKING FEE RULES)

## 1. Biểu phí cơ bản theo giờ

| Loại xe | Chi phí |
|----------|----------|
| Car | 6.00 / giờ |
| Motorcycle | 4.00 / giờ |
| Bicycle | 2.00 / giờ |

---

## 2. Khung giờ cao điểm (Peak Hours)

### Buổi sáng

Từ:

```text
06:00 đến trước 10:00
```

Các khung giờ:

```text
6, 7, 8, 9
```

### Buổi chiều/tối

Từ:

```text
15:00 đến trước 19:00
```

Các khung giờ:

```text
15, 16, 17, 18
```

---

## 3. Công thức tính phí

### Trong 2 giờ đầu tiên

#### Nếu vào giờ cao điểm

Áp dụng mức tăng:

```text
+30%
```

so với đơn giá chuẩn.

#### Nếu vào giờ thấp điểm

Áp dụng mức giảm:

```text
-5%
```

so với đơn giá chuẩn.

### Từ giờ thứ 3 trở đi

Áp dụng cho tất cả các giờ từ giờ thứ 3.

Giảm giá:

```text
-10%
```

trên đơn giá theo giờ, bất kể vào giờ cao điểm hay thấp điểm.

---

# 4. YÊU CẦU CHỨC NĂNG MENU (MAIN MENU REQUIREMENTS)

Chương trình hiển thị menu lặp lại liên tục cho đến khi người dùng chọn thoát.

---

## 1. Tạo Bãi đỗ xe mới

Nhập:

- `parkID`
- `size` (`'S'`, `'M'`, `'L'`)

Yêu cầu:

- Tối đa 3 bãi.
- Kiểm tra trùng lặp ID.
- Kiểm tra vượt quá sức chứa hệ thống.

---

## 2. Thêm xe vào bãi đỗ

Nhập:

- `vehicleID`
- `vehicleType`
- `entryTime`
- `parkingDuration`

Yêu cầu:

- Tự động xếp vào bãi đỗ còn chỗ thích hợp dựa trên `size`.
- Tự động tính `parkingFee`.

---

## 3. Xóa một Bãi đỗ xe

Nhập:

```text
parkID
```

Để xóa bãi đỗ ra khỏi hệ thống.

---

## 4. Lấy xe ra khỏi bãi đỗ

Nhập:

```text
vehicleID
```

Để lấy xe ra khỏi bãi.

---

## 5. Hiển thị danh sách tất cả các Bãi đỗ xe

Liệt kê thông tin tổng quan:

- ID bãi
- Kích thước
- Số lượng xe hiện có

---

## 6. Hiển thị danh sách xe theo bãi cụ thể

Nhập:

```text
parkID
```

In ra thông tin chi tiết từng xe trong bãi đó.

---

## 7. Liệt kê xe theo loại phương tiện

Nhập loại xe:

- `Car`
- `Motorcycle`
- `Bicycle`

In danh sách:

- Các xe khớp loại
- Bãi đỗ tương ứng

---

## 8. Xem báo cáo tóm tắt phí đỗ xe trung bình

Tính và hiển thị:

### Trên toàn hệ thống

Phí đỗ xe trung bình cho từng loại:

- Car
- Motorcycle
- Bicycle

### Theo từng bãi đỗ

Phân tích chi tiết:

- Tổng phí
- Phí trung bình
- Thống kê theo loại xe

---

## 9. Thoát chương trình

Kết thúc ứng dụng.

---

