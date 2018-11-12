#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define motorA1 9           //IN1 pre H-bridge
#define motorA2 10          //IN2 pre H-bridge
#define motorB1 11          //IN3 pre H-bridge
#define motorB2 12          //IN4 pre H-beidge
#define servoPin A0         //Servo Pin OUTPUT
#define trig1Pin 2          //triger Pin ultrasonic
#define trig2Pin 3          //triger Pin ultrasonic
#define trig3Pin 4          //triger Pin ultrasonic
#define echo1Pin 5          //echo Pin ultrasonic
#define echo2Pin 6          //echo Pin ultrasonic
#define echo3Pin 7          //echo Pin ultrasonic
#define ledRight 0          //lava ledka
#define ledLeft 0           //prava ledka
#define piezoPin 0          //piezo pin
#define bluetoothTX 0       //bluetooth tx pin
#define bluetoothRX 0       //bluetooth rx pin
#define frontRightPR A1     //pravy predny photoresistor
#define backRightPR A2      //pravy zadny photoresistor
#define frontLeftPR A3      //lavy predny photoresistor
#define backLeftPR A4       //lavy zadny photoresistor

const int del = 5;          //casova dlzka pre tocenie kolies
const int MAX_DISTANCE = 20;//maximalna vzdialenost

#endif
