#include <Servo.h>
#include <stdbool.h>
#include "Constants.h"
#include "Useful.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(0, 1);
String BluetoothData;

Servo servo;  //servo module object

void setup() {
    //Serial.begin(9600);
    BT.begin(9600);
    BT.println("Bluetooth On");
    Serial.begin(9660);//Begining the serial
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

void stop(){
    motorVals(0,0,0,0);
    servo.write(90);
}

void loop() {
    giveTurnValue(dist(0),dist(1));
    goStraight();


   if(BT.available())
  {
     BluetoothData += BT.readString();
     
     delay(100); 
  }  
  if(BluetoothData.equals("w")) // auticko do predu
  {
    BluetoothData=("");
  } 
   else if (BluetoothData.equals("s")) //auticko do zadu
   {
    BluetoothData=("");
    }
  else if (BluetoothData.equals("d")) //auticko do prava
  {
    BluetoothData=("");
    }
  else if (BluetoothData.equals("a")) // auticko do lava
  {
    BluetoothData=("");
    }
  else if (BluetoothData.equals("p"))   // auticko stop
  {
    BluetoothData=("");
    }
  else if (BluetoothData.equals("o")) //auticko autonom
  {
    BluetoothData=("");
    }
   else if (BluetoothData.equals("l")) // auto turn on led 
   {
    BluetoothData=("");
    }
   else if (BluetoothData.equals("k")) //turn off led 
   {
    BluetoothData=("");
    }
   else if (BluetoothData.equals("j")) // piezo horn
   {
    BluetoothData=("");
    }


    
}
