#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SerialTransfer.h"

#define debug 1

SoftwareSerial mySerial(2, 3);
SerialTransfer dataPayload;
unsigned long startMillis;
unsigned long currentMillis;

enum link{Connected = 1, Disconnected = 0};

link link_status = Disconnected;


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
} robot_state;

void BLE_UNO_init()
{
    val = {.left_joystick = 26,
           .right_joystick = 76,
           .emergency_stop = 0,
           .start_stop = 1,
           .open_close = 0};

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

void print_control_data()
{
    Serial.print("control data : ");
    Serial.print(val.left_joystick);
    Serial.print(" | ");
    Serial.print(val.right_joystick);
    Serial.print(" | ");
    Serial.print(val.emergency_stop);
    Serial.print(" | ");
    Serial.print(val.start_stop);
    Serial.print(" | ");
    Serial.println(val.open_close);
}

void print_Robot_State()
{
    Serial.print("Robot State data : ");
    Serial.print(robot_state.rpm_l);
    Serial.print(" | ");
    Serial.print(robot_state.rpm_r);
    Serial.print(" | ");
    Serial.print(robot_state.door_state);
    Serial.print(" | ");
    Serial.print(robot_state.moving_status);
    Serial.print(" | ");
    Serial.println(robot_state.feedback_status);
}

void transmit_data()
{
    TCNT1 = 3036;
    uint16_t packetSize = 0;
    packetSize = dataPayload.txObj(val, packetSize);
    dataPayload.sendData(packetSize);
    if (debug)
    {
        print_control_data();
        print_Robot_State();
    }
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

link connectionStatus(){
    return link_status;
}




/**
 * Functions to write data and transmit 
 */
void sendData(byte left_joystick, byte right_joystick, bool emergency_stop, bool start_stop, bool open_close)
{
    val.left_joystick = left_joystick;
    val.right_joystick = right_joystick;
    val.emergency_stop = emergency_stop;
    val.start_stop = start_stop;
    val.open_close = open_close;
    transmit_data();
}

/**
 * arduino built in functions 
 */

ISR(TIMER1_OVF_vect)
{
    TCNT1 = 3036;
    transmit_data();
}

void mySerialEvent()
{
    if (dataPayload.available())
    {
        uint16_t packetSize = 0;
        packetSize = dataPayload.rxObj(robot_state, packetSize);
        link_status = Connected;
        startMillis = currentMillis;
    }
    else
    {
        currentMillis = millis();
        if (currentMillis - startMillis >= 3000)
        {
            link_status = Disconnected;
            startMillis = currentMillis;
        }
    }
}