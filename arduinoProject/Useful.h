#ifndef USEFUL_H_
#define USEFUL_H_

/**
 * Inicializuje bluetooth
 */
void setupUseful();

/**
 * nastavi hodnoty pre motor zapnutim urcitych pinov na hodnotu 100 alebo 0
 * @param a hodnota pre pravy motor dopredu
 * @param b hodnota pre pravy motor dozadu
 * @param c hodnota pre lavy motor dopredu
 * @param d hodnota pre lavy motor dozadu
 */
void motorVals(int a, int b, int c, int d);

/**
 * zapne alebo vypne urcitu ledku
 * @param a hodnota pre pravu ledku
 * @param b hodnota pre lavu ledku
 */
void ledVals(int a, int b);

/**
 * Vypne vsetky ledky
 */
void ledLightOff();

/**
 * zapne vsetky ledky
 */
void ledLightOn();

/**
 * zapne pravu ledku
 */
void ledLightOnL();

/**
 * zapne lavu ledku
 */
void ledLightOnR();

/**
 * zistuje vzdialenost ultaronic senzora od urciteho objektu
 * @param i cislo ultarasonic senzora
 * 0 pre lavy
 * 1 pre pre pravy
 * 2 pre predny senzor
 * pre hodnotu 3 a viac vrati hodnotu vacsiu ako MAX_DISTANCE = vyvarovanie sa problemom
 * @return vzdialenost od objektu
 */
int dist(int i);

/**
 * Pracuje s bluetooth komunikaciou stylom prijmania
 * jednoduchych bytych dat ak data nepozna bluetooth ignoruje
 * a odosle
 */
void btValues();

/**
 * Tato funckia nakalibruje hodnoty svetla podla hodnoty
 * svetla ktore su pre hladanie svetla idealne svetlo zistuje 2.5s
 * hlada najvyssie hodnoty
 */
void calibrate();

/**
 * Cita PR data a pomoou podmienok vyhodnocuje kam za sa otocit
 * ked su svieti svetlo napravo ide napravo
 * ked svieti svetlo vlavo ide vlavo
 * ked sviet svetlo na vsetky 4 zastavi sa
 */
void readPRData();


#endif
