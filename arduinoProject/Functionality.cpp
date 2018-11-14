#include <Arduino.h>
#include <Servo.h>
#include <stdbool.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

void horn(){
    tone(piezoPin,3000,500);            //nastavi frekvenciu ktorou bude zvonit na nejaky cas
}

void goStraight(bool auton){
    Serial.println("Going straight");
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

void turnRight(bool straight, int timeDel){
    stopCar();
    Serial.println("Going Right");
    ledLightOnR();
    if(straight) motorVals(1,0,0,0);   //chod vpred a otacaj kolesa
    else motorVals(0,0,1,0);           //chod vzad a otacaj kolesa
    delay(timeDel);
    ledLightOff();
}

void turnLeft(bool straight, int timeDel){
    Serial.println("Going Left");
    ledLightOnL();
    if(straight) motorVals(0,0,1,0);   //chod vpred a otacaj kolesa
    else motorVals(1,0,0,0);           //chod vzad a otacaj kolesa
    delay(timeDel);
    ledLightOff();
}

void doUTurn(){
    Serial.println("Doing U-Turn");
    bool goRight = dist(0) > dist(1) ? true : false;                    //rozhoduje do ktorej strany ma auticko ist

    goRight ? turnLeft(true, 1000) : turnRight(true, 1000);                         //rozhoduje sa vpravo alebo vlavo a dozadu
    goRight ? turnRight(false, 1000) : turnRight(false, 1000);                      //ak siel vpravo doazdu musi ist dopredu vlavo a naopek

    delay(1000);
}

void stopCar(){
    motorVals(0,0,0,0);                 //zastavi auticko
}

void giveTurnValue(int leftDistance, int rightDistance){
    if(leftDistance > MAX_DISTANCE && rightDistance > MAX_DISTANCE){    //ak su objekty v dostatocnej vzdialenosti chod rovno
        goStraight(true);
        return;
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;       //ak je objekt vpravo blizsie ako objekt vlavo tak rozhoduj pre pravu stranu

    int value = 1600;
    if(goRight){                        //  ak je vyhodnejsie ist vpravo tak zisti vzdialenost doprava
        value -= leftDistance * 50;     // Zisti ako dlho sa bude otacat vpravo
        turnRight(true, value);
    }else{                              //ak je vyhodnejsie ist vlavo tak zisti vzdialenost dolava
        value -= rightDistance * 50;    //zisti ako dlho sa otacat vlavo
        turnLeft(true, value);
    }
}

void goAutonomous(){
    giveTurnValue(dist(0),dist(1));    //zisti hodnotu do ktorej otocit kolesa
    goStraight(true);                  //chod rovno a zistuj ci je nieco vpredu
}

