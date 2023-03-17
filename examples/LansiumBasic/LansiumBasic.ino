#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <Lansium.h>

ESP8266WiFiMulti WiFiMulti;
Lansium lansium;

char clientId[] = "YOUR_DEVICE_ID";
char auth[] = "YOUR_AUTH_TOKEN";

char ssid[] = "SSID";
char pass[] = "Password";

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

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

void loop()
{
    lansium.loop();
}