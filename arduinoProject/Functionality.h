#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_

void forSetup();
void goStraight();
void goReverse();
void turnLeft(bool straight);
void turnRight(bool straight);
void doUTurn();
void stopCar();
int giveTurnValue(int leftDistance, int rightDistance);
void horn();
void setupFunc();
void goAutonomous();
void readPRData();

#endif
