/**
 * VÍ DỤ 2-1b: QUẢN LÝ PHÂN HỆ NGUỒN (EPS) VỚI THƯ VIỆN PTITCUBE (MAX17048)
 * 
 * Mô tả:
 * Ví dụ này minh họa cách sử dụng lớp PTIT_EPS trong thư viện PTITCube để 
 * giám sát trạng thái năng lượng của vệ tinh:
 * - Đọc điện áp pin (V)
 * - Đọc phần trăm dung lượng pin chính xác theo thuật toán ModelGauge (%)
 * - Đọc tốc độ sạc hoặc xả (%/h)
 * 
 * Lớp PTIT_EPS tự động đóng gói toàn bộ giao tiếp I2C cấp thấp với IC MAX17048.
 */

#include <Arduino.h>
#include <PTITCube.h>

// Khởi tạo đối tượng phân hệ nguồn EPS
PTIT_EPS eps;

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

        Serial.println("[EXAMPLE 2-1b] PHÂN HỆ NGUỒN EPS - THƯ VIỆN PTITCUBE");
    
    // Khởi tạo phân hệ nguồn EPS
    if (eps.init()) {
        Serial.println("[EPS] Khởi tạo thành công! IC MAX17048 đã sẵn sàng.");
    } else {
        Serial.println("[EPS] CẢNH BÁO: Không phát hiện IC MAX17048. Vui lòng kiểm tra kết nối I2C.");
    }
    
    Serial.println("[EXAMPLE] Bắt đầu theo dõi trạng thái nguồn Pin liên tục...\n");
}

void loop() {
    // Cập nhật thông số từ IC đo dung lượng
    eps.update();

    float voltage = eps.getBatteryVoltage();
    float percent = eps.getBatteryPercent();
    float chargeRate = eps.getChargeRate();

    // Hiển thị dữ liệu Telemetry nguồn
    Serial.printf("[Uptime: %lus] Điện áp: %.3f V | Dung lượng: %.1f %% | Tốc độ: %+.2f %%/h\n",
                  millis() / 1000, voltage, percent, chargeRate);

    // Xử lý các kịch bản quản lý năng lượng vệ tinh
    if (voltage < 3.2f && voltage > 1.0f) {
        Serial.println(" ---> [CẢNH BÁO EPS] Pin yếu! Kích hoạt chế độ Safe-Mode / Deep-Sleep.");
    } else if (percent >= 98.0f) {
        Serial.println(" ---> [EPS INFO] Pin đã sạc đầy. Sẵn sàng cho các nhiệm vụ tải cao (Chụp ảnh/Truyền tin).");
    }

    if (chargeRate > 0.5f) {
        Serial.println(" ---> [EPS INFO] Tấm pin Mặt Trời đang sạc cho vệ tinh.");
    } else if (chargeRate < -2.0f) {
        Serial.println(" ---> [EPS INFO] Vệ tinh đang tiêu thụ dòng cao (Xả nhanh).");
    }

    delay(2000);
}
