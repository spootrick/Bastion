/*    
  ____            _   _             
 |  _ \          | | (_)            
 | |_) | __ _ ___| |_ _  ___  _ __  
 |  _ < / _` / __| __| |/ _ \| '_ \ 
 | |_) | (_| \__ \ |_| | (_) | | | |
 |____/ \__,_|___/\__|_|\___/|_| |_|
           The Sentinel
    www.bastionthesentinel.com
 
 */

/*
 * Bluetooth state variables
 */
int state = 0;
int flag = 0;

/* 
 *  HC-SR04 Ultrasonic Distance Sensor
 *  connection pins
 *  
 */
const int echo = 7;
const int trig = 8;

/*
 * 
 *  6V Reduced DC Motors
 *  connection pins
 * 
 */
const int left_forward = 3;
const int left_backward = 2;
const int right_forward = 4;
const int right_backward = 5;

/*
 *  Test led pin
 */
int ledPin = 13;

/*
 * Constants
 */
long duration = 0;
long distance = 0;
int motorDelay = 500;

void setup() {
  //Setting up pin modes
  // Distance sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  // led
  pinMode(ledPin, LOW);

  // Motors
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);

  // Begin serial connection
  Serial.begin(9600);
}

void loop() {
  // Reading serial connection
  if(Serial.available() > 0) {
    state = Serial.read();
    flag = 0;
  }

  if(state == '0') {                                  // HELP STATE
    if (flag == 0) {
      Serial.println("  ###  HELP  ###  ");
      Serial.println("Type 0 for help");
      Serial.println("Type 1 for go forward");
      Serial.println("Type 2 for go backward");
      Serial.println("Type 3 for go left");
      Serial.println("Type 4 for go right");
      Serial.println("Type 5 for automatic mode");
      Serial.println(" === Test options === ");
      Serial.println("Type 8 for led off");
      Serial.println("Type 9 for led on");
      flag = 1;
    }
  } else if (state == '1') {                          // GO FORWARD
    if(flag == 0){
      goForward();
      delay(motorDelay);
      stopIt();
      flag = 1;
    }
  } else if (state == '2') {                          // GO BACKWARD
    if(flag == 0){
      goBackward();
      delay(motorDelay);
      stopIt();
      flag = 1;
    }
  } else if (state == '3') {                          // GO LEFT
    if(flag == 0){
      goLeft();
      delay(motorDelay);
      stopIt();
      flag = 1;
    }
  } else if (state == '4') {                          // GO RIGHT
    if(flag == 0){
      goRight();
      delay(motorDelay);
      stopIt();
      flag = 1;
    }
  } else if (state == '5') {                          // AUTOMATIC MODE
    if(flag == 0){
      digitalWrite(trig, LOW);           // ultrasound is off
      delayMicroseconds(2); 
      digitalWrite(trig, HIGH);          // send ping 
      delayMicroseconds(10);             // ping remains for 10ms
      digitalWrite(trig, LOW);           // stop ping
      
      duration = pulseIn(echo, HIGH);    // listen for the ping
      distance = (duration / 2) / 29.1;  // convert to cm
      //Serial.println(distance);
    
      // Distance conditions
      if(distance < 30) {
        // if there is an obstacle 
        goBackward();
        delay(250);
        goLeft();
        delay(50);
      } else {
        // if there is no obstacle
        goForward();
      } 
      // flag = 1;  // commented out for ideal performance
    }
  } else if (state == '8') {                         // TEST LED OFF
    digitalWrite(ledPin, LOW);
    if(flag == 0) {
      Serial.println("LED: off");
      
    }
  } else if (state == '9') {                         // TEST LED ON
    digitalWrite(ledPin, HIGH);
    if(flag == 0){
      Serial.println("LED: on");
      flag = 1;
    }
  } else {
    // stop moving
    stopIt();
  }
}

/**
 * This method applies HIGH voltages to forward pins
 * for right and left motor
 * 
 * Performs straight movement
 */
void goForward(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

/**
 * This method applies HIGH voltages to left backward
 * and right forward
 * 
 * Performs left turn
 */
void goLeft(){
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

/**
 * This method applies HIGH voltages to right backward
 * and left forward
 * 
 * Performs left turn
 */
void goRight(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}

/**
 * This method applies HIGH voltages to backward pins
 * for right and left motor
 * 
 * Performs backward movement
 */
void goBackward(){
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}

/**
 * This method applies LOW voltages to both motor 
 * to stop device
 */
void stopIt(){
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW); 
}

