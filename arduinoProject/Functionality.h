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
 * Otcoi motor do lava
 * @param straight rozhoduje o tom ci ide auto vpred alebo dozadu 
 */
void turnLeft(bool straight);

/**
 * Otcoi motor do prava
 * @param straight rozhoduje o tom ci ide auto vpred alebo dozadu 
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
 * zastav auticko
 */
void stopCar();

/**
 * tato funckia rozhoduje kam ma auticko ist
 * rozhoduje sa podla vzdialenosti of objektu
 * @param leftDistance vzdialenost najblizsieho objektu vlavo
 * @param rightDistance vzdialenost najblizsieho objektu vpravu
 */
void giveTurnValue(int leftDistance, int rightDistance);

/**
 * Funckia sa stara o zvuk pieza
 */
void horn();

/**
 * funkcia ktora sa stara o samostatnu autonomitu auta
 */
void goAutonomous();

#endif
