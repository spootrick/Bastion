#include "DualVNH5019MotorShield.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// motor shield object as motorDriver
DualVNH5019MotorShield motorDriver;


// adafruit pca9685 servo driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


// definings for servos
#define SERVOMIN  150
#define SERVOMAX  650
#define FREQUENCY 60


// defining servo pins
uint8_t servo1 = 0;
uint8_t servo2 = 1;
uint8_t servo3 = 2;
uint8_t servo4 = 3;
uint8_t servo5 = 4;
uint8_t servo6 = 5;
uint8_t servo7 = 6;
uint8_t servo8 = 7;


// defining start values of servos
int pos_servo_1 = 150;
int pos_servo_2 = 150;
int pos_servo_3 = 150;
int pos_servo_4 = 150;
int pos_servo_5 = 150;
int pos_servo_6 = 150;
int pos_servo_7 = 150;
int pos_servo_8 = 150;


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
 * This method turns servos in positive direction.
 */
void turnServoPositive(uint8_t servo_num, int pos_servo) {
  if(pos_servo >= SERVOMIN && pos_servo <= SERVOMAX){
    for(int i = pos_servo; i < pos_servo + 50; i++){
      pwm.setPWM(servo_num, 0, i);
      delay(2);
    }
    Serial.print("Servo ");
    Serial.print(servo_num);
    Serial.print(" pozitif yonde donuyor.. pos: ");
    Serial.println(pos_servo);
  }else{
    Serial.print("Servo ");
    Serial.print(servo_num);
    Serial.print(" icin verilen deger aralik disinda! girilen deger: ");
    Serial.println(pos_servo);
  }
}


/**
 * This method turns servos in negative direction.
 */
void turnServoNegative(uint8_t servo_num, int pos_servo) {
  if(pos_servo > SERVOMIN && pos_servo < SERVOMAX){
    for(int i = pos_servo; i > pos_servo - 50; i--){
      pwm.setPWM(servo_num, 0, i);
      delay(2);
    }

    Serial.print("Servo ");
    Serial.print(servo_num);
    Serial.print(" negatif yonde donuyor.. pos: ");
    Serial.println(pos_servo);
  }else{
    Serial.print("Servo ");
    Serial.print(servo_num);
    Serial.print(" icin verilen deger aralik disinda! girilen deger: ");
    Serial.println(pos_servo);
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

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
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

      // robotic arm commands

      // SERVO 1
      case 7:
        turnServoPositive(servo1, pos_servo_1);
        pos_servo_1 += 50;
        break;
      case 8:
        pos_servo_1 -= 50;
        turnServoNegative(servo1, pos_servo_1);
        break;

      // SERVO 2
      case 9:
        turnServoPositive(servo2, pos_servo_2);
        pos_servo_2 += 50;
        break;
      case 10:
        pos_servo_2 -= 50;
        turnServoNegative(servo2, pos_servo_2);
        break;

      // SERVO 3
      case 11:
        turnServoPositive(servo3, pos_servo_3);
        pos_servo_3 += 50;
        break;
      case 12:
        pos_servo_3 -= 50;
        turnServoNegative(servo3, pos_servo_3);
        break;

      // SERVO 4
      case 13:
        turnServoPositive(servo4, pos_servo_4);
        pos_servo_4 += 50;
        break;
      case 14:
        pos_servo_4 -= 50;
        turnServoNegative(servo4, pos_servo_4);
        break;

      // SERVO 5
      case 15:
        turnServoPositive(servo5, pos_servo_5);
        pos_servo_5 += 50;
        break;
      case 16:
        pos_servo_5 -= 50;
        turnServoNegative(servo5, pos_servo_5);
        break;

      // SERVO 6
      case 17:
        turnServoPositive(servo6, pos_servo_6);
        pos_servo_6 += 50;
        break;
      case 18:
        pos_servo_6 -= 50;
        turnServoNegative(servo6, pos_servo_6);
        break;

      // SERVO 7
      case 19:
        turnServoPositive(servo7, pos_servo_7);
        pos_servo_7 += 50;
        break;
      case 20:
        pos_servo_7 -= 50;
        turnServoNegative(servo7, pos_servo_7);
        break;

      // SERVO 8
      case 21:
        turnServoPositive(servo8, pos_servo_8);
        pos_servo_8 += 50;
        break;
      case 22:
        pos_servo_8 -= 50;
        turnServoNegative(servo8, pos_servo_8);
        break;
      default:
        Serial.println("Uups!.. Wrong command entered!");
    }
  }
  delay(1);
}
