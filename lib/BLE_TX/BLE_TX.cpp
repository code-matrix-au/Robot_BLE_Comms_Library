//#include "BLE_TX.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SerialTransfer.h"
#include "Wire.h"

SoftwareSerial mySerial(2, 3);
SerialTransfer dataPayload;
enum state{Working = 1, Failed = 0};
struct values
{
    byte left_joystick;
    byte right_joystick;
    bool emergency_stop;
    bool start_stop;
    bool open_close; 
}val;

bool link;
char arr[] = "hello";


void BLE_TX_init()
{
     val={.left_joystick=112,
        .right_joystick=76, 
        .emergency_stop=0,
        .start_stop= 1,
        .open_close=0};
           
    mySerial.begin(9600);
    Serial.begin(9600);
    dataPayload.begin(mySerial);

    TCCR1A =0;
    TCCR1B =0;
    TCNT1 = 3036;
    TCCR1B |=(1<<CS12); 
    TIMSK1 |= (1<<TOIE1);
}

void transmit_data(){
    TCNT1 =3036;
    uint16_t packetSize = 0;
    packetSize = dataPayload.txObj(val, packetSize);
    packetSize = dataPayload.txObj(arr, packetSize);
    dataPayload.sendData(packetSize);
}

void left_joystick(int x)
{
    constrain(x,0,255);
    if (val.left_joystick != x){
        val.left_joystick=x;
        transmit_data();
    }
}
void right_joystick(int x)
{
    constrain(x,0,255);
    if(val.right_joystick != x){
        val.right_joystick=x;
        transmit_data();
    }
}
void emergency_stop(bool x)
{   
    if(val.emergency_stop != x){
        val.emergency_stop=x;
        transmit_data();
    }
}
void start_stop(bool x)
{
    if(val.start_stop != x){
        val.start_stop=x;
        transmit_data();
    }
}

bool connection()
{
    return link;
}

ISR(TIMER1_OVF_vect){
    TCNT1 =3036;
    transmit_data();
}
void serialEvent(){


    
}