#define ldrPin A0
#define fetPin 10
#define servoPin 11
#define ldrPower 12
#define loMapFrom 150
#define hiMapFrom 470
#define loMapTo 160
#define hiMapTo 50
#define moveThreshold 5
#define servoDelay 250
#define avgCounter 10

#include <LowPower.h>
#include <Servo.h>

Servo myservo;


unsigned long lightVal;    // variable to read the value from the analog pin
int oldVal = 200;

void setup() {
    //Serial.begin(9600);
    pinMode(ldrPin, INPUT);
    pinMode(fetPin, OUTPUT);
    myservo.attach(servoPin);
    pinMode(ldrPower, OUTPUT);
}

void loop() {
    // turns on the power to the ldr so we can sense the light-levels
    digitalWrite(ldrPower, HIGH);
    // reads the value from the ldr avgCounter-times and calculates the average
    lightVal = 0;
    for(int i = 0; i < avgCounter; i++){
        lightVal += (unsigned long) analogRead(ldrPin);
    }
    // turns off the power to the ldr since we are done sensing light-levels.
    digitalWrite(ldrPower, LOW);

    lightVal = lightVal / (unsigned long) avgCounter;
    
    //Serial.println(lightVal);

    // constrains the light value to be inside the range we're mapping from
    lightVal = constrain(lightVal, loMapFrom, hiMapFrom);
    // scales the value from the ldr to a value for the servo
    int servoVal = map(lightVal, loMapFrom, hiMapFrom, loMapTo, hiMapTo);
    
    //Serial.println(servoVal);

    if(abs(oldVal - servoVal) >= moveThreshold){
        // turning on the power to the servo by turning on the transistor
        digitalWrite(fetPin, HIGH);

        // sets the servo position according to the scaled value
        myservo.write(servoVal);


        // waits for the servo to get there
        delay(servoDelay);
        // turns off the power to the servo by turning the transistor off
        digitalWrite(fetPin, LOW);

        // saves the new servo value
        oldVal = servoVal;
    }

    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}
