# Lab2-01b_Battery_Library

**Quản lý Phân hệ Năng lượng (EPS) với Thư viện PTITCube**

Bài thực hành thuộc Phân hệ Năng lượng (EPS - Electrical Power System) trong hệ thống CubeSat-LMS.

## 1. Giới thiệu
Bài thực hành hướng dẫn sử dụng lớp `PTIT_EPS` trong thư viện chuẩn `PTITCube` để theo dõi và quản lý nguồn năng lượng vệ tinh:
- Đọc điện áp cell pin tức thời.
- Đọc dung lượng pin (%) theo thuật toán ModelGauge™ của IC MAX17048.
- Đọc tốc độ sạc / xả pin (%/h) để phát hiện trạng thái sạc từ pin mặt trời hoặc xả năng lượng khi truyền tin/chụp ảnh.
- Tự động cảnh báo và đề xuất chuyển sang chế độ tiết kiệm năng lượng (Safe Mode).

## 2. API Lớp PTIT_EPS
- `bool init()`: Khởi tạo bus I2C và kiểm tra cảm biến MAX17048.
- `void update()`: Cập nhật các chỉ số năng lượng mới nhất.
- `float getBatteryVoltage()`: Lấy điện áp cell pin (V).
- `float getBatteryPercent()`: Lấy phần trăm dung lượng pin (0.0% - 100.0%).
- `float getChargeRate()`: Lấy tốc độ sạc/xả pin (%/h).
- `bool isConnected()`: Kiểm tra trạng thái kết nối IC MAX17048.

## 3. Biên dịch và nạp code
```bash
pio run -t upload
pio device monitor
```
