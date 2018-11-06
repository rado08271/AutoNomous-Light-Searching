#include <Servo.h>
#include <stdbool.h>
 
#define motorA1 9   //IN1 for H-bridge
#define motorA2 10  //IN2 for H-bridge
#define motorB1 11  //IN3 for H-bridge
#define motorB2 12  //IN4 for H-beidge
#define servoPin A0 //Servo Pin OUTPUT
#define trig1Pin 2  
#define trig2Pin 3
#define trig3Pin 4
#define echo1Pin 5
#define echo2Pin 6
#define echo3Pin 7
#define ledRight 
#define ledLeft 
#define IRsensorL
#define IRsensorR 


const int del = 5; //Delay for turning wheels
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


int followLine()
{
  int IRvalueL = digitalRead(IRsensorL);
  int IRvalueR digitalRead(IRsensorR);
 
  if(!IRvalueL && IRvalueR) // ked na lavo je cierna a na pravo je biela vracia 1 ma ist do lava
      return 1;
  if(IRvalueL && !IRvalueR ) // ked je na lavo biela a na pravo cierna vracia 2 ma ist do prava
      return -1;
  if(IRvalueL && IRvalueR) // su na bielej ide rovno 
      return 0;
}
   


int giveTurnValue(int leftDistance, int rightDistance){
    int angle = 90;
    if(leftDistance > 30 && rightDistance > 30){
        servo.write(angle);
        return angle;
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;
 
    if(goRight){
        angle += (40 - leftDistance);
    }else{
        angle -= (40 - rightDistance);
    }
    servo.write(angle);
    delay(200);
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" ld ");
    Serial.print(leftDistance);
    Serial.print(" rd ");
    Serial.println(rightDistance);
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
 
//    Serial.print(i+1);
//    Serial.print(". has value of: ");
//    Serial.println(distance);
 
    return distance;
}
 
void turnLeft(bool straight){
 
    for(int i = 90; i > giveTurnValue(dist(0),dist(1)); i--){
        servo.write(i);
        if(straight)
            ledLightOnL();
            goStraight();
        else
            goReverse();
        delay(del);
    }
}
 
void turnRight(bool straight){
    for(int i = 90; i < 120; i++){
        servo.write(i);
        if(straight)
            ledLightOnR();
            goStraight();
        else
            goReverse();
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
 
void loop() {
    giveTurnValue(dist(0),dist(1));
    goStraight();
  
}
