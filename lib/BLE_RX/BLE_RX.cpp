#include "Arduino.h"
#include "SerialTransfer.h"

struct values
{
    byte left_joystick;
    byte right_joystick;
    bool emergency_stop;
    bool start_stop;
    bool open_close; 
}val;

void BLE_RX_init(){
     val={.left_joystick=0,
        .right_joystick=0, 
        .emergency_stop=false,
        .start_stop= false,
        .open_close=false};

        Serial.begin(9600);
        //Serial1.begin(9600);
}

if(myTransfer.available())
  {
uint16_t recSize = 0;




  }



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


bool connection()
{
    
}
