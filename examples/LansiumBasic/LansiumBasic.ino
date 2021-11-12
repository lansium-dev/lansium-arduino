#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <Lansium.h>

ESP8266WiFiMulti WiFiMulti;
Lansium lansium;

String auth = "YOUR_DEVICE_TOKEN";

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

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

void loop()
{
    lansium.loop();
}