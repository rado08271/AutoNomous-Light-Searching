//pouzite kniznice
#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>


//hlavickove subory
#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

void setup() {
    
    setupUseful();
    
    Serial.begin(9600);               //Inicializacia serialoveho terminalu
    calibrate();                      //Kalibracia hodnot pre hladanie svetla 
    ledLightOn();

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

    pinMode(ledRight,OUTPUT);
    pinMode(ledLeft,OUTPUT);
    pinMode(piezoPin,OUTPUT);

    pinMode(frontRightPR,INPUT);
    pinMode(backRightPR,INPUT);
    pinMode(frontLeftPR,INPUT);
    pinMode(backLeftPR,INPUT);

}


void loop() {
  btValues();
}
