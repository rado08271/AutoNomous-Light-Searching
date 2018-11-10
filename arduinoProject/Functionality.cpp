#include <Arduino.h>
#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

SoftwareSerial BT(0, 1);
String BluetoothData;
Servo servo;  

void forSetup(){
    BT.begin(9600);
    BT.println("Bluetooth On");
    servo.attach(servoPin);  
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
      turnRight();
      BluetoothData=("");
  }

  else if (BluetoothData.equals("a")){ // auticko do lava
      turnLeft();
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
     turnOnLed();
     BluetoothData=("");
  }

  else if (BluetoothData.equals("k")){ //turn off led 
    turnOffLed();
    BluetoothData=("");
  }
  
  else if (BluetoothData.equals("j")){ // piezo horn
    horn();
    BluetoothData=("");
  }
}
