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
  Serial.begin(9600);
  Serial.setTimeout(50); // limiting the max wait time for serial data
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


/**
 * This method is for turning left
 */
void turnLeft(){
  motorDriver.setM1Speed(100);
  motorDriver.setM2Speed(-100);
  delay(225);
  motorDriver.setM1Speed(0);
  motorDriver.setM2Speed(0);
}


/**
 * This method is for turning right
 */
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
      case 1: // move forward 200
        setMotorSpeed(200);
        break;
      case 2: // move backward 200
        setMotorSpeed(-200);
        break;
      case 3: // move forward 400
        setMotorSpeed(400);
        break;
      case 4: // move backward 400
        setMotorSpeed(-400);
        break;
      case 5: // turn left
        turnLeft();
        break;
      case 6: // turn right
        turnRight();
        break;
      default:
        Serial.println("Uups!.. Wrong command entered!");
    }
  }
  delay(1);
}

