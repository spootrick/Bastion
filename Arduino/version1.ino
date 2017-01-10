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
 *  HC-SR04 Ultrasonic Distance Sensor
 *  connection pins
 *  
 */
const int echo = 8;
const int trig = 10;

/*
 * 
 *  6V Reduced DC Motors
 *  connection pins
 * 
 */
const int left_forward = 2;
const int left_backward = 3;
const int right_forward = 4;
const int right_backward = 5;

/*
 * Constants
 */
int timing = 0;
int distance = 0;

void setup() {
  //Setting up pin modes
  // Distance sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Motors
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);

  // Begin serial connection
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  // distance calculations
  timing = pulseIn(echo, HIGH);
  distance = (timing / 2) / 28.5;
  Serial.println(distance);

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

