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

//fixme add delay?
void turnRight(bool straight){
    if(straight) motorVals(1,0,0,0);   //chod vpred a otacaj kolesa
    else motorVals(0,1,0,0);           //chod vzad a otacaj kolesa
}

//fixme add delay?
void turnLeft(bool straight){
    if(straight) motorVals(0,0,1,0);   //chod vpred a otacaj kolesa
    else motorVals(0,0,0,1);           //chod vzad a otacaj kolesa
}

void doUTurn(){
    bool goRight = dist(0) > dist(1) ? true : false;                    //rozhoduje do ktorej strany ma auticko ist

    goRight ? turnLeft(true) : turnRight(true);                         //rozhoduje sa vpravo alebo vlavo a dozadu
    goRight ? turnRight(false) : turnRight(false);                      //ak siel vpravo doazdu musi ist dopredu vlavo a naopek

    delay(1000);
}

void stopCar(){
    motorVals(0,0,0,0);                 //zastavi auticko
}

void giveTurnValue(int leftDistance, int rightDistance){
    if(leftDistance > MAX_DISTANCE && rightDistance > MAX_DISTANCE){    //ak su objekty v dostatocnej vzdialenosti chod rovno
        goStraight(true);
    }
    bool goRight = (leftDistance < rightDistance) ? true : false;       //ak je objekt vpravo blizsie ako objekt vlavo tak rozhoduj pre pravu stranu

    if(goRight){                       //ak je vyhodnejsie ist vpravo tak zisti vzdialenost doprava
        turnRight(true);
    }else{                             //ak je vyhodnejsie ist vlavo tak zisti vzdialenost dolava
        turnLeft(true);
    }

    //fixme nejak pracuj s hodnotami ktore dostane a s casom? 700 pri vzd 20 1500 pri vzd < 4
    //20*50 == 1000
    //2*50 === 100
    //1600-1000=600
    //1600-100=1500
}

void goAutonomous(){
    giveTurnValue(dist(0),dist(1));    //zisti hodnotu do ktorej otocit kolesa
    goStraight(true);                  //chod rovno a zistuj ci je nieco vpredu
}

