#include <Servo.h>
#include <stdbool.h>
#include "Constants.h"
#include "Useful.h"

Servo servo;  //servo module object

void setup() {
    Serial.begin(9600);  //Begining the serial
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
    servo.attach(servoPin);
}

 
void goStraight(){
    motorVals(1,0,1,0);
    if(dist(2) < 30){
        doUTurn();
    }
    ledLightOff();
}
 
void goReverse(){
    motorVals(0,1,0,1);
} 

void turnLeft(bool straight){
    for(int i = 90; i > giveTurnValue(dist(0),dist(1)); i--){
        servo.write(i);
        if(straight){
            ledLightOnL();
            goStraight();
        }else goReverse();
        delay(del);
    }
}
 
void turnRight(bool straight){
    for(int i = 90; i < 120; i++){
        servo.write(i);
        if(straight){
            ledLightOnR();
            goStraight();
        }else goReverse();
        delay(del);
    }
}

void doUTurn(){
    goReverse();
    delay(1000);
    for(int i = 90; i > 60; i--) {
        servo.write(i);
        delay(del);
    }
 
    for(int i = 90; i < 130; i++) {
        servo.write(i);
        delay(del);
    }
 
    goStraight();
    delay(1000);
}
void loop() {
    giveTurnValue(dist(0),dist(1));
    goStraight();
  
}
