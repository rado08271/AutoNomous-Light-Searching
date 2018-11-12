#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_

/**
 * Auticko ide rovno v jednom smere
 * @param auton hovori o tom ci je auto
 * v mode autonomity alebo nieje ak je, tak
 * pozera v akej vzdialenosti je objekt ak je v dostatocnej
 * blizkosti tak sa urobi otocku
 */
void goStraight(bool auton);

/**
 * Auticko ide dozadu v jednom smere
 */
void goReverse();

/**
 * Otcoi servo motor do lava
 * @param straight rozhoduje o tom ci ide auto vpred alebo dozadu pocas tocenia serva
 */
void turnLeft(bool straight);

/**
 * Otcoi servo motor do prava
 * @param straight rozhoduje o tom ci ide auto vpred alebo dozadu pocas tocenia serva
 */
void turnRight(bool straight);

/**
 * ak je pred autom predmet tak sa auticko otoci
 * auticko sa rozhodne do ktorej strany je vyhodnejsie ist
 * ak je vpravo viac miesta ako vlavo tak ide doprava a dozadu
 * inak ide dolava...
 */
void doUTurn();

/**
 * zastav auticko a otoc kolesa vpred
 */
void stopCar();

/**
 * tato funckia zisti aky uhol sa ma nastavit
 * pre kolesa rozhoduje sa podla vzdialenosti
 * @param leftDistance vzdialenost najblizsieho objektu vlavo
 * @param rightDistance vzdialenost najblizsieho objektu vpravu
 * @return vracia uhol ktorym sa maju natocit kolesa
 */
int giveTurnValue(int leftDistance, int rightDistance);

/**
 * Funckia sa stara o zvuk pieza
 */
void horn();

/**
 * Nastavenie pre setup na pripojenie serva
 */
void setupFunc();

/**
 * funkcia ktora sa stara o samostatnu autonomitu auta
 */
void goAutonomous();

#endif
