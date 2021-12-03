# Lansium Arduino

Lansium-Arduino là thư viện dùng để kết nối mạch điện tới Lansium IoT Server.

## Tải về

Trang chủ: https://lansium.com

Mobile app: [<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=com.lansium&hl=vi)

## Cài đặt

Thư viện này sử dụng [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) để thiết lập kết nối tới server.

Trước khi cài đặt Lansium Arduino, bạn phải cài đặt 2 thư viện sau:

- https://github.com/bblanchon/ArduinoJson
- https://github.com/Links2004/arduinoWebSockets

Bạn có thể cài đặt **LansiumArduino** trực tiếp từ **Arduino Library Manager** hoặc tải source code về và thêm thủ công.

👉 [Hướng dẫn cách cài đặt thư viện cho Arduino IDE](https://www.arduino.cc/en/guide/libraries)

## Danh sách mạch điện hỗ trợ

Xem danh sách tại: https://github.com/Links2004/arduinoWebSockets#supported-hardware

## Kết nối

- **Bước 1:** Tải và cài đặt Lansium app
- **Bước 2:** Lấy Auth Token
  - Mở Lansium app, chọn tab IoT
  - Thêm nhóm thiết bị
  - Thêm thiết bị
  - Nhấn vào nút xem chi tiết thiết bị (nút ℹ️ nằm ở góc trên bên phải ứng dụng)
  - Nhấn nút sao chép Auth Token
- **Bước 3:** Kiểm tra lại và chắc chắn rằng bạn đã cài thư viện này cùng với 2 thư viện đi kèm
- **Bước 4:** Cập nhật Auth Token
  - Mở Arduino IDE
  - Chọn File -> Examples -> lansium-arduino -> LansiumBasic
  - Thay đổi giá trị `YOUR_DEVICE_TOKEN` thành Auth Token vừa mới sao chép ở bước 2
  - Thay đổi thông tin kết nối wifi (SSID, Password)
- **Bước 5:** Lưu code và upload code lên mạch điện

## Ví dụ

Xem chi tiết tại [Lansium Examples](https://github.com/lansium-dev/lansium-arduino/tree/main/examples)

## Khai báo cơ bản

Khai báo thư viện

```cpp
#include <Lansium.h>

Lansium lansium;
```

Thiết lập kết nối

```cpp
void setup()
{
  ...
  // Mạch điện phải kết nối mạng thành công trước khi chạy dòng này
  lansium.begin(authToken);
}
```

Giữ kết nối liên tục

```cpp
void loop()
{
  lansium.loop();
  ...
}
```

Các hàm gửi sự kiện từ mạch tới máy chủ

```cpp
void sendStateChanged(int pin, bool state);

void sendDataChanged(int pin, String data);
void sendDataChanged(int pin, int data);
void sendDataChanged(int pin, float data);
void sendDataChanged(int pin, double data);
```

Sử dụng hàm `sendStateChanged` cho các widget có trạng thái ON/OFF (đèn, nút nhấn, công tắc,...).

Sử dụng hàm `sendDataChanged` cho các widget thu thập dữ liệu từ cảm biến.

## Lỗi đang có

- Mạch điện không thể kết nối lại sau khi bị mất kết nối.
