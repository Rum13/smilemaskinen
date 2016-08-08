#include <LowPower.h>
#include <Servo.h>

Servo myservo;

int potPin = A1;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int oldVal = 200;

void setup() {
  pinMode(12, OUTPUT);
  myservo.attach(11);
}

void loop() {
  val = analogRead(potPin);

  //val = map(val, 10, 800, 60, 120);
  val = map(val, 200, 700, 50, 120);

  int tempVal=val-oldVal;

  if(abs(tempVal)>=10){
    digitalWrite(12,HIGH);

    myservo.write(val);                  // sets the servo position according to the scaled value
    oldVal=val;
    delay(250);                           // waits for the servo to get there

    digitalWrite(12,LOW);
  }

  LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
}
