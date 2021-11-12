#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <Lansium.h>
#include "DHT.h"

#define DHTTYPE DHT11

ESP8266WiFiMulti WiFiMulti;
Lansium lansium;

DHT dht(12, DHTTYPE);

String auth = "YOUR_DEVICE_TOKEN";

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    dht.begin();

    if (WiFi.getMode() & WIFI_AP)
    {
        WiFi.softAPdisconnect(true);
    }

    WiFiMulti.addAP("SSID", "Password");
    while (WiFiMulti.run() != WL_CONNECTED)
    {
        delay(500);
    }
    lansium.begin(auth);
}

unsigned long readTimestamp = 0;

void loop()
{
    lansium.loop();

    // send to server every 30 seconds
    uint64_t now = millis();
    if (now - readTimestamp > 30000)
    {
        readTimestamp = now;

        float h = dht.readHumidity();
        float t = dht.readTemperature();

        if (isnan(h) || isnan(t))
        {
            Serial.println(F("Failed to read from DHT sensor!"));
            return;
        }

        lansium.sendDataChanged(12, h);
        // Write wirtual pin. Make sure it match with frontend widget pin
        lansium.sendDataChanged(100, t);
    }
}