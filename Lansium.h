#ifndef LANSIUM_H
#define LANSIUM_H

#include <WebSocketsClient.h>
#include <SocketIOclient.h>

#define LANSIUM_HOST "api.lansium.com"
#define LANSIUM_PORT 3006

#define SOCKET_RECONNECT_INTERVAL 10000

#define LANSIUM_EVENT_AUTHENTICATE "authenticate"
#define LANSIUM_EVENT_DATA_CHANGE "data_change"
#define LANSIUM_EVENT_STATE_CHANGE "state_change"

class Lansium
{
public:
    Lansium();
    ~Lansium();

    SocketIOclient _socketIO;
    String _auth;

    void begin(String auth);
    void loop();
    void send(String event, int pin, auto data);

    void sendStateChanged(int pin, bool state);
    void sendDataChanged(int pin, String data);
    void sendDataChanged(int pin, int data);
    void sendDataChanged(int pin, float data);
    void sendDataChanged(int pin, double data);
};

#endif /* LANSIUM_H */