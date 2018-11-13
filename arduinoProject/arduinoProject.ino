//pouzite kniznice
#include <Servo.h>
#include <stdbool.h>

//hlavickove subory
#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

void setup() {
    Serial.begin(9600);             //Inicializacia serialoveho terminalu
    setupUseful();                  //BLuetooth inicializacia
    calibrate();                    //Kalibracia hodnot pre hladanie svetla 
    ledLightOn();

    pinMode(motorA1,OUTPUT);
    pinMode(motorA2,OUTPUT);
    pinMode(motorB1,OUTPUT);
    pinMode(motorB2,OUTPUT);
//    pinMode(trig1Pin,OUTPUT);
//    pinMode(trig2Pin,OUTPUT);
//    pinMode(trig3Pin,OUTPUT);
//    pinMode(echo1Pin,INPUT);
//    pinMode(echo2Pin,INPUT);
//    pinMode(echo3Pin,INPUT);
}


void loop() {
  turnRight(true, 1000);
  delay(500);
  turnLeft(true, 1000);
//    btValues();                     //Funckia bluetooth ktora sa stara o cele ovladanie a pracu auticka
  delay(500);                     //menej citani = menej parkinson
}
