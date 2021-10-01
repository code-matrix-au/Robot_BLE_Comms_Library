#include <BLE_TX.h>

BLE_TX::BLE_TX(/* args */)
{
    val={.left_joystick=25,
        .right_joystick=3, 
        .emergency_stop=30,
        .start= 20,
        .stop=50,
        .button=80,
        .connection=40};
    Serial.begin(9600);
    mySerial = new SoftwareSerial(2, 3);
    mySerial->begin(9600);
   
}



void BLE_TX::left_joystick(int x)
{
    val.left_joystick=x;
    transmit_data();

}
void BLE_TX::right_joystick(int x)
{
    val.right_joystick=x;
    transmit_data();
}
void BLE_TX::emergency_stop(byte x)
{
    val.emergency_stop=x;
    transmit_data();
}
void BLE_TX::start(byte x)
{
    val.start=x;
    transmit_data();
}
void BLE_TX::button(byte x)
{
    val.button=x;
    transmit_data();
}
void BLE_TX::stop(byte x)
{
    val.stop=x;
    transmit_data();
}
void BLE_TX::connection()
{

}
void BLE_TX::transmit_data(){
    
mySerial->write((byte*) &val, sizeof(val));


}
