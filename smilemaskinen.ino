#define potPin A1
#define servoPin 11
#define transistorPin 12
#define loMapFrom 200
#define hiMapFrom 700
#define loMapTo 50
#define hiMapTo 120

#include <LowPower.h>
#include <Servo.h>

Servo myservo;


int potVal;    // variable to read the value from the analog pin
int oldVal = 200;

void setup() {
  pinMode(transistorPin, OUTPUT);
  myservo.attach(servoPin);
}

void loop() {
  potVal = analogRead(potPin);
  int servoVal = map(potVal, loMapFrom, hiMapFrom, loMapTo, hiMapTo);

  if(abs(oldVal - servoVal)>=10){
    digitalWrite(transistorPin, HIGH);
    myservo.write(servoVal);                  // sets the servo position according to the scaled value
    
    oldVal = servoVal;
    
    delay(250);                           // waits for the servo to get there
    digitalWrite(12,LOW);
  }

  LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
}
