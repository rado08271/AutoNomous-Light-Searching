#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"


void setup() {
    Serial.begin(9600);  //Begining the serial
    setupUseful();
    setupFunc();
    calibrate();

    pinMode(motorA1,OUTPUT);
    pinMode(motorA2,OUTPUT);
    pinMode(motorB1,OUTPUT);
    pinMode(motorB2,OUTPUT);
    pinMode(trig1Pin,OUTPUT);
    pinMode(trig2Pin,OUTPUT);
    pinMode(trig3Pin,OUTPUT);
    pinMode(echo1Pin,INPUT);
    pinMode(echo2Pin,INPUT);
    pinMode(echo3Pin,INPUT);
}


void loop() {
    giveTurnValue(dist(0),dist(1));
    goStraight();
}
