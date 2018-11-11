#include <Arduino.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

SoftwareSerial BT(0, 1);
String BluetoothData;

void setupUseful(){
    BT.begin(9600);
    BT.println("Bluetooth On");
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


void btValues(){
  if(BT.available()){
      BluetoothData += BT.readString();
      delay(100); 
  }  

  if(BluetoothData.equals("w")){ // auticko do predu
      goStraight();
      BluetoothData=("");
  }
  
  else if (BluetoothData.equals("s")){ //auticko do zadu
      goReverse();
      BluetoothData=("");
  }

  else if (BluetoothData.equals("d")){ //auticko do prava
      turnRight(1);
      BluetoothData=("");
  }

  else if (BluetoothData.equals("a")){ // auticko do lava
      turnLeft(1);
      BluetoothData=("");
  }

  else if (BluetoothData.equals("p")){   // auticko stop
      stopCar();
      BluetoothData=("");
  }

  else if (BluetoothData.equals("o")){ //auticko autonom
     goAutonomous();
     BluetoothData=("");
  }

  else if (BluetoothData.equals("l")){ // auto turn on led 
     ledLightOn();
     BluetoothData=("");
  }

  else if (BluetoothData.equals("k")){ //turn off led 
    ledLightOff();
    BluetoothData=("");
  }
  
  else if (BluetoothData.equals("j")){ // piezo horn
    horn();
    BluetoothData=("");
  }
}


void readPRData(){
  //sprav pole v setup kde nacita na zaciatku hodnoty
  //PP,ZP,PL,ZL
  int values[4] = {0,0,0,0};

  //PP ZP PL ZL ERR s 
  //1  2  3  4  -1  0 
  int go = -1;

  int previous = 0; //previous value of light
  int light = 0;    //how many of the pr have light pointing at them

  //nacita vsetky photorezistory
  for(int i = 0; i < 4; i++){
    values[i] = analogRead(frontRightPR+i); //precitaj hodnoty

    //ak je hodnota vacsia ako 200 tak svieti nan svetlo
    if(values[i] > 200){
      light++;
    }

    //zisti kam je najvyhodnejsie ist
    if(values[i] > previous){   //vacsia ako predosla hodnota tak dalsie je viac
      go = i+1;         //zmen na dalsie 
      previous = values[i];   //nastavi predoslu
    }
  }

  //na vsetky 4 svieti tak zastav
  if(light == 4){
      go = 0; 
  }
/*
  if(go < 0) error();       //je nejaky problem
  else if(go == 4) stop();      //na vsetky svieti = stoj
  else if(go < 2) turnRight();  //na prave svieti chod vpravo
  else if(go < 4) turnLeft();   //na lave svieti chod vlavo
*/
}

