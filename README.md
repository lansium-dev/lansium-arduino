# Lansium Arduino
Lansium-Arduino is a library for connect board to Lansium IoT Server using SocketIO.

## Downloads
Homepage: https://lansium.com

Mobile app: [<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=com.lansium&hl=vi)

## Installation
This library uses [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) for initial socket connection.

You must install the following libraries before install Lansium Arduino:
- https://github.com/bblanchon/ArduinoJson
- https://github.com/Links2004/arduinoWebSockets

You can install **LansiumArduino** from the **Arduino Library Manager** or manual download source code.

👉 [How to install a library in Arduino](https://www.arduino.cc/en/guide/libraries)

## Supported boards
See https://github.com/Links2004/arduinoWebSockets#supported-hardware

## Quickstart
- **Step 1:** Download Lansium app
- **Step 2:** Get Auth Token
  - Open Lansium app and change to IoT tab
  - Add device group
  - Add device
  - View device details
  - Copy Auth Token to clipboard
- **Step 3:** Make sure this library was installed in Arduino IDE
- **Step 4:** Update Auth Token in the sketch
  - Open Arduino IDE
  - Select File -> Examples -> lansium-arduino -> LansiumBasic
  - Update Auth Token
  - Change Wifi SSID and Password 
- **Step 5:** Upload code to board

## Examples
See [Lansium Examples](https://github.com/lansium-dev/lansium-arduino/tree/main/examples)

## Basics
Import this library
```cpp
#include <Lansium.h>

Lansium lansium;
```

Initial connection
```cpp
void setup()
{
  ...
  // make sure your board connected to the internet
  lansium.begin(authToken);
}
```

Keep socket connection
```cpp
void loop()
{
  lansium.loop();
  ...
}
```

Send events
```cpp
void sendStateChanged(int pin, bool state);

void sendDataChanged(int pin, String data);
void sendDataChanged(int pin, int data);
void sendDataChanged(int pin, float data);
void sendDataChanged(int pin, double data);
```
Use `sendStateChanged` for ON/OFF widgets (LED, Switch,...).

Use `sendDataChanged` for data collection from sensor.

## Known Issues
- Board cannot reconnect after loss of connection. (We'll fix it soon)
