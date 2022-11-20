#include "Map.h"

/*#ifndef BOMBERMAN_PERSONNAGE_H
#define BOMBERMAN_PERSONNAGE_H*/

struct Personnage {
    int posX;
    int posY;
    int nbDebombes;
   // bool enVie;
} typedef Personnage;

void deplacementDroite(Personnage perso, Map map);

void deplacementGauche(Personnage perso, Map map);

void deplacementBas(Personnage perso, Map map);

void deplacementHaut(Personnage perso, Map map);

void Deplacement(Personnage perso, char c, Map map);

//#endif //BOMBERMAN_PERSONNAGE_H


