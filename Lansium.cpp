#ifndef LANSIUM_IMPLEMENT_H
#define LANSIUM_IMPLEMENT_H

#include <ArduinoJson.h>
#include "Lansium.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

Lansium::Lansium(){};
Lansium::~Lansium(){};

String topic = "";
String topic_status = "";
String lwt_message = "0";

void onMqttMessage(int messageSize) {
    int pinIndex = mqttClient.messageTopic().indexOf("data/");
    if (pinIndex > -1) {
        int pin = mqttClient.messageTopic().substring(pinIndex + 5).toInt();
        String data = "";
        while (mqttClient.available()) {
            data += (char)mqttClient.read();
        }
        analogWrite(pin, data.toInt());
    }
}

void Lansium::begin(String clientId, String auth)
{
    topic = LANSIUM_CLIENT_TOPIC_NAME + clientId + LANSIUM_CLIENT_TOPIC_DATA;
    topic_status = LANSIUM_CLIENT_TOPIC_NAME + clientId + LANSIUM_CLIENT_TOPIC_STATUS;

    // Set the last will and testament (LWT) message
    mqttClient.beginWill(topic_status + "connected", lwt_message.length(), true, 1);
    mqttClient.print(lwt_message);
    mqttClient.endWill();

    mqttClient.setId(clientId);
    mqttClient.setUsernamePassword(auth, auth);

    while (!mqttClient.connect(LANSIUM_BROKER, LANSIUM_PORT))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
        delay(500);
    }

    mqttClient.onMessage(onMqttMessage);
    mqttClient.subscribe(topic + "#");

    mqttClient.beginMessage(topic_status + "connected");
    mqttClient.print(1);
    mqttClient.endMessage();
}

void Lansium::loop()
{
    mqttClient.poll();
}

void Lansium::send(int pin, bool data)
{
    mqttClient.beginMessage(topic + pin);
    mqttClient.print(data);
    mqttClient.endMessage();
}

void Lansium::send(int pin, int data)
{
    mqttClient.beginMessage(topic + pin);
    mqttClient.print(data);
    mqttClient.endMessage();
}

void Lansium::send(int pin, float data)
{
    mqttClient.beginMessage(topic + pin);
    mqttClient.print(data);
    mqttClient.endMessage();
}

void Lansium::send(int pin, double data)
{
    mqttClient.beginMessage(topic + pin);
    mqttClient.print(data);
    mqttClient.endMessage();
}

void Lansium::send(int pin, String data)
{
    mqttClient.beginMessage(topic + pin);
    mqttClient.print(data);
    mqttClient.endMessage();
}

#endif /* LANSIUM_IMPLEMENT_H */