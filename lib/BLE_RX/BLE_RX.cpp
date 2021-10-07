#include "Arduino.h"
#include "SerialTransfer.h"
#include "Wire.h"

SerialTransfer dataPayload;

unsigned long startMillis;
unsigned long currentMillis;

struct values
{
    byte left_joystick;
    byte right_joystick;
    bool emergency_stop;
    bool start_stop;
    bool open_close;
} val;

struct state
{
    byte rpm_l;
    byte rpm_r;
    bool door_state;
    bool moving_status;
    byte feedback_status;
} robot_state;

void BLE_RX_init()
{
    val = {.left_joystick = 0,
           .right_joystick = 0,
           .emergency_stop = false,
           .start_stop = false,
           .open_close = false};
    Serial.begin(9600);
    Serial1.begin(9600);
    dataPayload.begin(Serial1);
    startMillis = millis();
}

// transmit data
void transmit_data()
{
    uint16_t packetSize = 0;
    packetSize = dataPayload.txObj(robot_state, packetSize);
    dataPayload.sendData(packetSize);
}


// read serial data if its available
void serialEvent1()
{
    if(dataPayload.available())
    {
        uint16_t packetSize = 0;
        packetSize = dataPayload.rxObj(val, packetSize);
        transmit_data(); 
        startMillis = currentMillis;
    }
    
}

void connection_timeout(){
    currentMillis = millis();
    if(currentMillis - startMillis >= 3000)
    {
        val.start_stop = false;
        robot_state.moving_status= false;
        transmit_data(); 
        startMillis = currentMillis;
    }
}



/**
 * The functions to access data sent 
 * from the host controler.
 */

int left_joystick()
{
    return val.left_joystick;
}
int right_joystick()
{
    return val.right_joystick;
}
bool emergency_stop()
{
    return val.emergency_stop;
}
bool start_stop()
{
    return val.start_stop;
}
bool open_close()
{
    return val.open_close;
}
bool connection()
{
    return false;
}

/**
 * Below are the functions that are 
 * used to send robot state/diagnostics 
 * data back to the host controller.
 */

void rpm_l(byte x)
{
    if (robot_state.rpm_l != x)
    {
        robot_state.rpm_l = x;
    }
}
void rpm_r(byte x)
{
    if (robot_state.rpm_r != x)
    {
        robot_state.rpm_r = x;
    }
}
void door_state(bool x)
{
    if (robot_state.door_state != x)
    {
        robot_state.door_state = x;
    }
}
void moving_status(bool x)
{
    if (robot_state.moving_status != x)
    {
        robot_state.moving_status = x;
    }
}

void feedback_status(bool x)
{
    if (robot_state.feedback_status != x)
    {
        robot_state.feedback_status = x;
    }
}
