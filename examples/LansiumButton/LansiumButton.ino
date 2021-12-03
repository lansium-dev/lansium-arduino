#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <Lansium.h>

ESP8266WiFiMulti WiFiMulti;
Lansium lansium;

String auth = "YOUR_DEVICE_TOKEN";

int BUTTON = 12; // D6 on NodeMCU
int LED = 4;     // D2 on NodeMCU

bool prevButtonStatus = false; // true = ON, false = OFF

void handleStateChanged(int pin, bool state)
{
    if (pin == LED)
    {
        prevButtonStatus = state;
    }
}

void setup()
{
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);

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
    lansium.addStateChangedCallback(handleStateChanged);
}

void loop()
{
    lansium.loop();

    int buttonStatus = digitalRead(BUTTON);
    if (buttonStatus != prevButtonStatus)
    {
        prevButtonStatus = buttonStatus;

        digitalWrite(LED, buttonStatus);
        lansium.sendStateChanged(LED, buttonStatus);
    }
}