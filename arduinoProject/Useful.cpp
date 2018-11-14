#include <Arduino.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

#include "Constants.h"
#include "Useful.h"
#include "Functionality.h"

int calibratedValues[4];                //kalibracne hodnoty pre PR

SoftwareSerial BT(bluetoothTX, bluetoothRX);     //inicializacia objektu bluetoothu
String BluetoothData;                            //pole pre vstup bluetooth dat

void setupUseful(){
    BT.begin(9600);                     //zacne prijmat bluetoothLE data na pasme 9600 baudov
    BT.println("Bluetooth is on");      //posle bluetooth informaciu ze je zapnuty
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
    long duration;                      //casova dlzka za ktoru pride zvuk na echo pin
    int distance;                       //vzdialenost od objektu

    if(i >= 3){                         //ak je ultrasonic vacsi ako 3 ktory neexistuje skonc...
        return MAX_DISTANCE + 1;        //vrat hodnotu ktora neovlyvnuje otacanie kolies
    }

    digitalWrite(trig1Pin+i, LOW);      //vycisti trigger
    delayMicroseconds(2);               //pocka 2 microsekundy
 
    digitalWrite(trig1Pin+i, HIGH);     //zacne posielat signal cez trigPin
    delayMicroseconds(10);              //Pocka 10 mikrosekund
    digitalWrite(trig1Pin+i, LOW);      //vycisti trigger
 
    duration = pulseIn(echo1Pin+i, HIGH); //zisti ako dlho trvalo zvuku dostat sa naspat na echo pin
 
 
    distance = duration*0.034/2;        //vypocita vzdialenost od predmetu ako cas za ktory sa zvuk dostal
                                        // spat na echo vzdialenost dostane vynasobenim casu rychlostou za sekundu
                                        //dostane ale vydialenost tam a naspat takze tuto vydialenost musi vydelit dvoma

    Serial.println(distance);
    return distance;                    //vrati vzdialenost od objektu
}

void btValues(){
  if(BT.available()){                   //Ak je bluetooth dostupny tak zacni s bt
        BluetoothData += BT.readString();
        delay(100);
  }
  
  if(BluetoothData.equals("w")){        // auticko do predu
        goStraight(false);
        Serial.println(BluetoothData);
        BT.println("Going in Straight line");
  }else if (BluetoothData.equals("s")){ //auticko do zadu
        goReverse();
        Serial.println(BluetoothData);
        BT.println("Going in Reverse");
  }else if (BluetoothData.equals("d")){ //auticko do prava
        turnRight(true,1000);
        Serial.println(BluetoothData);
        BT.println("Turning Right");
  }else if (BluetoothData.equals("a")){ // auticko do lava
        turnLeft(true,1000);
        Serial.println(BluetoothData);
        BT.println("Turning Left");
  }else if (BluetoothData.equals("p")){ // auticko stop
        stopCar();
        Serial.println(BluetoothData);
        BT.println("Car is stopped");
  }else if (BluetoothData.equals("l")){ //auto turn on led
        ledLightOn();
        Serial.println(BluetoothData);
        BT.println("Leds are On");
  }else if (BluetoothData.equals("k")) {//turn off led
        ledLightOff();
        Serial.println(BluetoothData);
        BT.println("Leds Are OFF");
  }else if (BluetoothData.equals("h")){ //piezo horn
        horn();
        Serial.println(BluetoothData);
        BT.println("I buzz");
  }

    while(BluetoothData.equals("o")){     //auticko autonom
        goAutonomous();
        BT.println("Self-driving");    
        Serial.println("Self-driving");    
        if(BT.available()){                   //Ak je bluetooth dostupny tak zacni s bt
            Serial.println("Zmena nacitavania pre SD");
            BluetoothData += BT.readString();
            delay(100);
            break;
        }
  }
  while(BluetoothData.equals("j")){     //auticko hlada svetlo
        readPRData();
        BT.println("Read PR data");    
        Serial.println("Read PR data");    
        if(BT.available()){                   //Ak je bluetooth dostupny tak zacni s bt
            Serial.println("Zmena nacitavania pri citani pr");      
            BluetoothData += BT.readString();
            delay(100);
            break;
        }
  }

  BluetoothData=("");

}

void calibrate(){
    int value = 0;                      //hodnota na prechadzanie while
    int values[4] = {0,0,0,0};          //zakladne pomocne hodnoty na citanie
    while(value < 2500){                //vykona 2500krat
        value++;                        //zvysuje hodnotu kazdu 0.001s
        if(value % 200 <= 100){         //esteticky blikaj svetlami
            ledLightOn();               //zapni svetla
        }else{
            ledLightOff();              //vypni svetla
         }
        for(int i = 0; i < 4; i++){     //prechadza vsetkymi styroma PR a hlada nove hodnoty na kalibraciu
            values[i] = analogRead(frontRightPR+i);     //cita pomocne hodnoty
            if(calibratedValues[i] < values[i]){        //ked je hodnota pomocnej vacsia ako kalibracne hodnoty tak zmeni
                calibratedValues[i] = values[i];        //zmeni kalibracne hodnoty
            }
        }
        delay(1);                       //pocka 0.001s
    }
}

void readPRData(){
    int values[4] = {0,0,0,0};                            //hodnoty pre citanie PP,ZP,PL,ZL

    int go = -1;                                          //hodnota rozhodovania ktory PR je najvyssi tam pojde
                                                          //1 - pravy predny
                                                          //2 - pravy zadny
                                                          //3 - lavy predny
                                                          //4 - lavy zadny
                                                          //-1 - error
                                                          //0 - vypnute

    int previous = 0;                                     //Predosla hodnota svetla
    int light = 0;                                        //na kolko PR svieti svetlo

    for(int i = 0; i < 4; i++){                           //nacita vsetky photorezistory
        values[i] = analogRead(frontRightPR+i);           //precitaj hodnoty
        Serial.print("Hodnota PR cislo: ");
        Serial.print(i+1);
        Serial.print(" je ");
        Serial.println(values[i]);

        if(values[i] > calibratedValues[i]){              //ak je hodnota vacsia ako 200 tak svieti nan svetlo
            light++;                                      //pocet PR ktore splnaju podmienky
        }

        if(values[i] > previous){                         //vacsia ako predosla hodnota tak zisti kam je najvyhodnejsie ist
            go = i+1;                                     //zmen na dalsie
            previous = values[i];                         //nastavi predoslu
        }
    }

  if(light == 4){                                         //na vsetky 4 svieti tak zastav
      go = 0;                                             //go nastav na nulu teda auticko zastavi
  }

  if(go < 0) goStraight(false);                           //je nejaky problem
  else if(go == 0) stopCar();                             //na vsetky svieti = stoj
  else if(go <= 2) turnLeft(true, 1000);                  //na lave svieti chod vlavo
  else if(go <= 4) turnRight(true, 1000);                 //na prave svieti chod vpravo

}
