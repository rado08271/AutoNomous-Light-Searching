//pouzite kniznice
#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

//hlavickove subory
#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

SoftwareSerial BT(bluetoothRX, bluetoothTX);     //inicializacia objektu bluetoothu
String BluetoothData;                            //pole pre vstup bluetooth dat

void setup() {
    BT.begin(9600);                     //zacne prijmat bluetoothLE data na pasme 9600 baudov
    BT.println("Bluetooth is on");      //posle bluetooth informaciu ze je zapnuty

    Serial.begin(9600);             //Inicializacia serialoveho terminalu
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
  if(BT.available()){                   //Ak je bluetooth dostupny tak zacni s bt
      BluetoothData += BT.readString();
      delay(100);
  }

  if(BluetoothData.equals("w")){        // auticko do predu
        goStraight(true);
        BT.println("Going in Straight line");
  }else if (BluetoothData.equals("s")){ //auticko do zadu
        goReverse();
        BT.println("Going in Reverse");
  }else if (BluetoothData.equals("d")){ //auticko do prava
        turnRight(true,1000);
        BT.println("Turning Right");
  }else if (BluetoothData.equals("a")){ // auticko do lava
        turnLeft(true,1000);
        BT.println("Turning Left");
  }else if (BluetoothData.equals("p")){ // auticko stop
        stopCar();
        BT.println("Car is stopped");
  }else if (BluetoothData.equals("o")){ //auticko autonom
        goAutonomous();
        BT.println("Self-driving");
  }else if (BluetoothData.equals("l")){ //auto turn on led
        ledLightOn();
        BT.println("Leds are On");
  }else if (BluetoothData.equals("k")) {//turn off led
        ledLightOff();
        BT.println("Leds Are OFF");
  }else if (BluetoothData.equals("h")){ //piezo horn
        horn();
        BT.println("I buzz");
  }else if (BluetoothData.equals("j")){ //go PR
        readPRData();
        BT.println("Read PR data");
  }
  BluetoothData=("");
}
