#include <Arduino.h>
#include <Servo.h>
#include <stdbool.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

Servo servo;  

void setupFunc(){
    servo.attach(servoPin);  
}

void horn(){
    tone(piezoPin,3000,500); //pin, tone, duration
}

void goStraight(){
    motorVals(1,0,1,0);
    if(dist(2) < MAX_DISTANCE){
        horn();
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

void stopCar(){
    motorVals(0,0,0,0);
    servo.write(90);
}

int giveTurnValue(int leftDistance, int rightDistance){
    int angle = 90;
    if(leftDistance > MAX_DISTANCE && rightDistance > MAX_DISTANCE){
        servo.write(angle);
        return angle;
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;
 
    if(goRight){
        angle += (30 - leftDistance);
    }else{
        angle -= (30 - rightDistance);
    }
    servo.write(angle);
    
    return angle;
}

void goAutonomous(){
    giveTurnValue(dist(0),dist(1));
    goStraight();
}
