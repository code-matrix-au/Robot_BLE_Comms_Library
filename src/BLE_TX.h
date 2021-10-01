#include "Arduino.h"
#include <SoftwareSerial.h>


class BLE_TX
{
private:

SoftwareSerial *mySerial;
void transmit_data();

struct values
{
    int left_joystick;
    int right_joystick;
    byte emergency_stop;
    byte start;
    byte stop;
    byte button;
    byte connection;
}val;


public:
    BLE_TX(/* args */);
    void left_joystick(int);
    void right_joystick(int);
    void emergency_stop(byte);
    void start(byte);
    void button(byte);
    void stop(byte);
    void connection();




};

