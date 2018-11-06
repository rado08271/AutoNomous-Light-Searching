#include <Arduino.h>
#include <stdbool.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

void motorVals(int a, int b, int c, int d){
    digitalWrite(motorA1,a);
    digitalWrite(motorA2,b);
    digitalWrite(motorB1,c);
    digitalWrite(motorB2,d);
}

void ledVals(int a, int b){
    digitalWrite(ledRight, a);
    digitalWrite(ledLeft, b);
}

void ledLightOff(){
    ledVals(0,0);
}

void ledLightOn(){
    ledVals(1,1);
}

void ledLightOnL(){
    ledVals(0,1);
}

void ledLightOnR(){
    ledVals(1,0);
}

int giveTurnValue(int leftDistance, int rightDistance){
    int angle = 90;
    if(leftDistance > 30 && rightDistance > 30){
        //servo.write(angle);
        return angle;
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;
 
    if(goRight){
        angle += (40 - leftDistance);
    }else{
        angle -= (40 - rightDistance);
    }
    //servo.write(angle);
    
    return angle;
}

int dist(int i){
    long duration;
    int distance;
 
    digitalWrite(trig1Pin+i, LOW);
    delayMicroseconds(2);
 
    digitalWrite(trig1Pin+i, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin+i, LOW);
 
    duration = pulseIn(echo1Pin+i, HIGH);
 
 
    distance = duration*0.034/2;
  
    return distance;
}

int readLine(){
  int IRvalueL = digitalRead(IRsensorL);
  int IRvalueR = digitalRead(IRsensorR);
 
  if(!IRvalueL && IRvalueR) // ked na lavo je cierna a na pravo je biela vracia 1 ma ist do lava
      return 1;
  if(IRvalueL && !IRvalueR ) // ked je na lavo biela a na pravo cierna vracia 2 ma ist do prava
      return -1;
  if(IRvalueL && IRvalueR) // su na bielej ide rovno 
      return 0;
}

void horn(){
  tone(piezoPin,3000,500); //pin, tone, duration
}

