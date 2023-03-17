#ifndef LANSIUM_H
#define LANSIUM_H

#define LANSIUM_BROKER "api-dev.lansium.com"
#define LANSIUM_PORT 1883

#define LANSIUM_CLIENT_TOPIC_NAME "lansium/devices/"
#define LANSIUM_CLIENT_TOPIC_DATA "/data/"
#define MQTT_KEEP_ALIVE 60

#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
#endif

class Lansium
{
public:
    Lansium();
    ~Lansium();

    void begin(String clientId, String auth);
    void loop();

    void send(int pin, bool data);
    void send(int pin, int data);
    void send(int pin, float data);
    void send(int pin, double data);
    void send(int pin, String data);
};

#endif /* LANSIUM_H */