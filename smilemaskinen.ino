#define ldrPin A1
#define servoPin 11
#define transistorPin 12
#define loMapFrom 200
#define hiMapFrom 700
#define loMapTo 50
#define hiMapTo 120
#define moveThreshold 10
#define servoDelay 250
#define avgCounter 5

#include <LowPower.h>
#include <Servo.h>

Servo myservo;


unsigned long lightVal;    // variable to read the value from the analog pin
int oldVal = 200;

void setup() {
    pinMode(ldrPin, INPUT);
    pinMode(transistorPin, OUTPUT);
    myservo.attach(servoPin);
}

void loop() {
    // reads the value from the ldr avgCounter-times and calculates the average
    for(int i = 0; i < avgCounter; i++){
        lightVal += (unsigned long) analogRead(ldrPin);
    }
    lightVal = lightVal / avgCounter;

    // constrains the light value to be inside the range we're mapping from
    lightVal = constrain(lightVal, loMapFrom, hiMapFrom);
    // scales the value from the ldr to a value for the servo
    int servoVal = map(lightVal, loMapFrom, hiMapFrom, loMapTo, hiMapTo);

    if(abs(oldVal - servoVal) >= moveThreshold){
        // turning on the power to the servo by turning on the transistor
        digitalWrite(transistorPin, HIGH);

        // sets the servo position according to the scaled value
        myservo.write(servoVal);


        // waits for the servo to get there
        delay(servoDelay);
        // turns off the power to the servo by turning the transistor off
        digitalWrite(transistorPin, LOW);

        // saves the new servo value
        oldVal = servoVal;
    }

    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
}
