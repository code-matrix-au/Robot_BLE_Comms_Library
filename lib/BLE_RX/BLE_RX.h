#include "Arduino.h"

class BLE_RX
{
private:
    /* data */

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
    BLE_RX(/* args */);
    int left_joystick();
    int right_joystick();
    byte emergency_stop(byte);
    byte start(byte);
    byte button(byte);
    byte stop(byte);
    byte connection();
    
};



