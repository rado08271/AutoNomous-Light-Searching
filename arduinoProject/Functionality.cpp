#include <Arduino.h>
#include <Servo.h>
#include <stdbool.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

Servo servo;                            //objekt serva

void setupFunc(){
    servo.attach(servoPin);             //pripoji servo na servoPin
}

void horn(){
    tone(piezoPin,3000,500);            //nastavi frekvenciu ktorou bude zvonit na nejaky cas
}

void goStraight(bool auton){
    motorVals(1,0,1,0);                 //hodnoty pravy dopredu ano, lavy depredu ano
    if(auton){                          //mod autonomity
        if(dist(2) < MAX_DISTANCE){     //ak je objekt vo vzdialenosti menej ako MAX_DISTANCE tak zatrub a otoc
            horn();                     //zatrub
            doUTurn();                  //otoc sa
        }
    }
}

void goReverse(){
    motorVals(0,1,0,1);                 //hodnoty pravy zadny ano, lavy zadny ano
} 

void turnRight(bool straight){
    for(int i = 90; i < 120; i++) {     //postupne otaca servo dolava
        if(straight){                   //ked ma ist dopredu tak ide dopredu
            if(i%10>5){                 //zapne blinker
                ledLightOnL();
            }else{
                ledLightOff();
            }
            goStraight(false);          //chod rovno bez zistovania objektov vpredu
        }else goReverse();              //ked ma ist dozadu ide dozadu
        servo.write(i);                 //zapis na servo
        delay(del);                     //pockaj nejaky cas
    }
    servo.write(90);
}

void turnLeft(bool straight){
    for(int i = 90; i > 60; i--) {      //postupne otaca servo doprava
        if(straight) {                  //ked ma ist dopredu tak ide dopredu
            if (i % 10 > 5) {           //zapne blinker
                ledLightOnR();
            } else {
                ledLightOff();
            }
            goStraight(false);          //chod rovno bez zistovania objektov vpredu
        }else goReverse();              //ked ma ist dozadu ide dozadu

        servo.write(i);                 //zapis na servo
        delay(del);                     //pockaj nejaky cas
    }
    servo.write(90);
}

void doUTurn(){
    bool goRight = dist(0) > dist(1) ? true : false; //rozhoduje do ktorej strany ma auticko ist

    goRight ? turnLeft(true) : turnRight(true);   //rozhoduje sa vpravo alebo vlavo a dozadu
    goRight ? turnRight(false) : turnRight(false);//ak siel vpravo doazdu musi ist dopredu vlavo a naopek

    delay(1000);
}

void stopCar(){
    motorVals(0,0,0,0);                 //zastavi auticko
    servo.write(90);                    //otoci kolesa dopradu
}

int giveTurnValue(int leftDistance, int rightDistance){
    int angle = 90;                     //nastavi zakladny uhol na 90
    if(leftDistance > MAX_DISTANCE && rightDistance > MAX_DISTANCE){    //ak su objekty v dostatocnej vzdialenosti chod rovno
        servo.write(angle);             //ide rovno
        return angle;                   //vracia uhol
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;       //ak je objekt vpravo blizsie ako objekt vlavo tak rozhoduj pre pravu stranu

    if(goRight){                       //ak je vyhodnejsie ist vpravo tak zisti o aky uhol ma nastavit vzdialenost doprava
        angle += (30 - leftDistance);  
    }else{                             //ak je vyhodnejsie ist vlavo tak zistuj o aky uhol ma nastavit vzdialenost dolava
        angle -= (30 - rightDistance);
    }
    servo.write(angle);                //zapise uhol na servo
    
    return angle;                      //vracia uhol
}

void goAutonomous(){
    giveTurnValue(dist(0),dist(1));    //zisti hodnotu do ktorej otocit kolesa
    goStraight(true);                  //chod rovno a zistuj ci je nieco vpredu
}

