#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield motorDriver;

/**
 * This method runs if there is a motor fault
 * and prints feedback to the serial.
 */
void stopIfFault(){
  if (motorDriver.getM1Fault()){
    Serial.println("M1 fault");
    while(1);
  }
  if (motorDriver.getM2Fault()){
    Serial.println("M2 fault");
    while(1);
  }
}

/**
 * Setup code which runs once.
 */
void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection established.");
  motorDriver.init();
}

/**
 * This method is for used to move the robot back and forth
 */
void setMotorSpeed(int speed){
  if(speed >= -400 && speed <= 400){
    motorDriver.setM1Speed(speed);
    motorDriver.setM2Speed(speed);

    stopIfFault();
    delay(1);
  }
}

void turnLeft(){
  motorDriver.setM1Speed(100);
  motorDriver.setM2Speed(-100);
  delay(225);
  motorDriver.setM1Speed(0);
  motorDriver.setM2Speed(0);
}

void turnRight(){
  motorDriver.setM1Speed(-100);
  motorDriver.setM2Speed(100);
  delay(225);
  motorDriver.setM1Speed(0);
  motorDriver.setM2Speed(0);
}

/**
 * Main code which runs repeatedly
 */
void loop() {
  if(Serial.available()){
    switch(Serial.parseInt()){
      case 0: // stop
        setMotorSpeed(0);
        break;
      case 1: // move forward
        setMotorSpeed(400);
        break;
      case 2: // move backward
        setMotorSpeed(-400);
        break;
      case 3: // turn left
        turnLeft();
        break;
      case 4: // turn right
        turnRight();
        break;
      default:
        Serial.println("Uups!.. Wrong command entered!");
    }
  }
  delay(1);
}



