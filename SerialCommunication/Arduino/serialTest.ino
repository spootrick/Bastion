/*
  This program sets pin 2 to led pin. Reads serial and
  according to the serial data blinks led for a second for
  given time.
*/

int led = 2;

void setup() {                
  pinMode(led, OUTPUT);  
  Serial.begin(9600);   
}

void loop() {
  if(Serial.available()){
    doSomething(Serial.parseInt());
  }
  delay(500);
}

void doSomething(int n){
  for(int i = 0; i < n; i++){
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}

