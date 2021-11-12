#ifndef LANSIUM_IMPLEMENT_H
#define LANSIUM_IMPLEMENT_H

#include <ArduinoJson.h>
#include "Lansium.h"

SocketIOclient *io;
String *authToken;

Lansium::Lansium(){};

Lansium::~Lansium(){};

void listenEvents(uint8_t *payload, size_t length)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload, length);
    String eventName = doc[0];

    if (eventName == LANSIUM_EVENT_STATE_CHANGE)
    {
        int pin = doc[1]["pin"];
        bool state = doc[1]["state"];

        analogWrite(pin, state ? 255 : 0);
    }
}

void sendAuthenticate()
{
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    array.add(LANSIUM_EVENT_AUTHENTICATE);
    JsonObject param = array.createNestedObject();
    param["token"] = *authToken;
    String output;
    serializeJson(doc, output);
    io->sendEVENT(output);
}

void handleSocketIOEvents(socketIOmessageType_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case sIOtype_DISCONNECT:
        Serial.println("[SocketIO] Disconnected");
        break;
    case sIOtype_CONNECT:
        Serial.print("[SocketIO] Connected to url: ");
        Serial.println((char *)payload);
        // join default namespace (no auto join in Socket.IO V3)
        io->send(sIOtype_CONNECT, "/");
        sendAuthenticate();
        break;
    case sIOtype_EVENT:
        Serial.print("[SocketIO] Get event: ");
        Serial.println((char *)payload);
        listenEvents(payload, length);
        break;
    case sIOtype_ACK:
        Serial.print("[SocketIO] Get ack: ");
        Serial.println(length);
        hexdump(payload, length);
        break;
    case sIOtype_ERROR:
        Serial.print("[SocketIO] Get error: ");
        Serial.println(length);
        hexdump(payload, length);
        break;
    case sIOtype_BINARY_EVENT:
        Serial.print("[SocketIO] Get binary: ");
        Serial.println(length);
        hexdump(payload, length);
        break;
    case sIOtype_BINARY_ACK:
        Serial.print("[SocketIO] Get binary ack: ");
        Serial.println(length);
        hexdump(payload, length);
        break;

    default:
        break;
    }
}

void Lansium::begin(String auth)
{
    _socketIO.setReconnectInterval(SOCKET_RECONNECT_INTERVAL);
    _socketIO.beginSSL(LANSIUM_HOST, LANSIUM_PORT, "/socket.io/?EIO=4");
    _socketIO.onEvent(handleSocketIOEvents);

    _auth = auth;
    io = &_socketIO;
    authToken = &_auth;
}

void Lansium::loop()
{
    _socketIO.loop();
}

void Lansium::send(String event, int pin, auto data)
{
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    array.add(event);
    JsonObject param = array.createNestedObject();
    param["pin"] = pin;
    param["data"] = data;
    String output;
    serializeJson(doc, output);
    _socketIO.sendEVENT(output);
}

void Lansium::sendStateChanged(int pin, bool state)
{
    Lansium::send(LANSIUM_EVENT_STATE_CHANGE, pin, state);
}

void Lansium::sendDataChanged(int pin, String data)
{
    Lansium::send(LANSIUM_EVENT_DATA_CHANGE, pin, data);
}

void Lansium::sendDataChanged(int pin, int data)
{
    Lansium::send(LANSIUM_EVENT_DATA_CHANGE, pin, data);
}

void Lansium::sendDataChanged(int pin, float data)
{
    Lansium::send(LANSIUM_EVENT_DATA_CHANGE, pin, data);
}

void Lansium::sendDataChanged(int pin, double data)
{
    Lansium::send(LANSIUM_EVENT_DATA_CHANGE, pin, data);
}

#endif /* LANSIUM_IMPLEMENT_H */