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
 * This method 
 */
void stopMove(){
  motorDriver.setM1Speed(0);
  motorDriver.setM2Speed(0);
}

/**
 * This method is for used to move the robot back and forth
 */
void makeMove(int speed){
  if(speed >= -400 && speed <= 400){
    motorDriver.setM1Speed(speed);
    motorDriver.setM2Speed(speed);

    stopIfFault();
    delay(2);
  }
}

/**
 * Main code which runs repeatedly
 */
void loop() {
  if(Serial.available()){
    switch(Serial.parseInt()){
      case 0:
        stopMove();
        break;
      case 1:
        makeMove(200);
        break;
      case 2:
        makeMove(-200);
        break;
      default:
        Serial.println("Uups!.. Wrong command entered!");
    }
  }
  delay(100);
}



