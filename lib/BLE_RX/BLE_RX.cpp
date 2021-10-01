# include "BLE_RX.h"


BLE_RX::BLE_RX(/* args */)
{
    val={.left_joystick=0,
        .right_joystick=0, 
        .emergency_stop=0,
        .start= 0,
        .stop=0,
        .button=0,
        .connection=0};
}
int BLE_RX::left_joystick()
{
    return val.left_joystick;
}
int BLE_RX::right_joystick()
{
    return val.right_joystick;
}
byte BLE_RX::emergency_stop(byte x)
{
    return val.emergency_stop;
}
byte BLE_RX::start(byte x)
{
   return val.start;
}
byte BLE_RX::button(byte x)
{
   return val.button;
}
byte BLE_RX::stop(byte x)
{
   return val.stop;
}
byte BLE_RX::connection()
{
    return val.connection;
}
void BLE_RX::transmit_data(){
    

}