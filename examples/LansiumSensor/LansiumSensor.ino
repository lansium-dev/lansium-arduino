#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <Lansium.h>
#include "DHT.h"

#define DHTTYPE DHT11

ESP8266WiFiMulti WiFiMulti;
Lansium lansium;

DHT dht(12, DHTTYPE);

char clientId[] = "YOUR_DEVICE_ID";
char auth[] = "YOUR_AUTH_TOKEN";

char ssid[] = "SSID";
char pass[] = "Password";

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    dht.begin();

    if (WiFi.getMode() & WIFI_AP)
    {
        WiFi.softAPdisconnect(true);
    }
    WiFiMulti.addAP(ssid, pass);
    while (WiFiMulti.run() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    lansium.begin(clientId, auth);
}

unsigned long readTimestamp = 0;

void loop()
{
    lansium.loop();

    // send to server every 5 seconds
    uint64_t now = millis();
    if (now - readTimestamp > 5000)
    {
        readTimestamp = now;

        float h = dht.readHumidity();
        float t = dht.readTemperature();

        if (isnan(h) || isnan(t))
        {
            Serial.println(F("Failed to read from DHT sensor!"));
            return;
        }

        lansium.send(12, h);
        // You can write wirtual pin. Make sure it match with frontend widget pin
        lansium.send(100, t);
    }
}