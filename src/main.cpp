#include <Arduino.h>
#include <BLE_TX.h>

BLE_TX my;



void setup() {
 
  
  // put your setup code here, to run once:
}

void loop() {
my.left_joystick(110);
delay(100);
  // put your main code here, to run repeatedly:
}