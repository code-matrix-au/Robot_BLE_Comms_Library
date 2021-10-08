#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SerialTransfer.h"
#include "Wire.h"

SoftwareSerial mySerial(2, 3);
SerialTransfer dataPayload;
unsigned long startMillis;
unsigned long currentMillis;
bool link;
struct values
{   
    byte left_joystick;
    byte right_joystick;
    bool emergency_stop;
    bool start_stop;
    bool open_close;
} val;

struct states
{
    byte rpm_l;
    byte rpm_r;
    bool door_state;
    bool moving_status;
    byte feedback_status;
    byte packet_id;
} robot_state;

void BLE_UNO_init()
{
    val = {.left_joystick = 26,
           .right_joystick = 76,
           .emergency_stop = 0,
           .start_stop = 1,
           .open_close = 0        
           };

    mySerial.begin(9600);
    Serial.begin(9600);
    dataPayload.begin(mySerial);

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 3036;
    TCCR1B |= (1 << CS12);
    TIMSK1 |= (1 << TOIE1);
    startMillis = millis();
}



void transmit_data()
{
    TCNT1 = 3036;
    uint16_t packetSize = 0;
    packetSize = dataPayload.txObj(val, packetSize);
    dataPayload.sendData(packetSize);
}
/**
 * Functions to access state/diagnostics
 * data from the robot.
 */

int rpm_l()
{
    return robot_state.rpm_l;
}

int rpm_r()
{
    return robot_state.rpm_r;
}
int door_state()
{
    return robot_state.door_state;
}
int moving_status()
{
    return robot_state.moving_status;
}
int feedback_status()
{
    return robot_state.feedback_status;
}

/**
 * Functions to write data and transmit 
 */
void left_joystick(unsigned int x)
{
    if (val.left_joystick != x)
    {
        val.left_joystick = x;
        transmit_data();
    }
}

void right_joystick(unsigned int x)
{
    if (val.right_joystick != x)
    {
        val.right_joystick = x;
        transmit_data();
    }
}

void emergency_stop(bool x)
{
    if (val.emergency_stop != x)
    {
        val.emergency_stop = x;
        transmit_data();
    }
}

void start_stop(bool x)
{
    if (val.start_stop != x)
    {
        startMillis = currentMillis;
        val.start_stop = x;
        transmit_data();
    }
}
void open_close(bool x)
{
    if (val.open_close != x)
    {
        val.open_close = x;
        transmit_data();
    }
}

bool connection()
{
    return link;
}

/**
 * arduino built in functions 
 */

ISR(TIMER1_OVF_vect)
{
    TCNT1 = 3036;
    //mySerial.write((byte*)&val, sizeof(val));
    transmit_data();
    
}

void mySerialEvent()
{
    if(dataPayload.available())
    {
        uint16_t packetSize = 0;
        packetSize = dataPayload.rxObj(robot_state, packetSize);
        startMillis = currentMillis;
    }
    else{
        currentMillis = millis();
        if(currentMillis - startMillis >= 3000)
        {
            val.start_stop = false;
            robot_state.moving_status= false;
            startMillis = currentMillis;
        }
    }
}