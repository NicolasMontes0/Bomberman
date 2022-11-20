//
// Created by monte on 20/11/2022.
//

#include <stdbool.h>

#ifndef BOMBERMAN_MAIN_H
#define BOMBERMAN_MAIN_H

#endif //BOMBERMAN_MAIN_H

struct Map {
    int id;
    int longueur;
    int hauteur;
    int nbBombes;
    char** map;
} typedef Map;

struct Personnage {
    char symbole;
    int id;
    int posX;
    int posY;
    int nbDebombes;
} typedef Personnage;

void afficherMap(Map map);

char **mapUn(int id, int longueur, int hauteur, int nbBombes);

bool deplacementDroite(Personnage perso, Map map);

bool deplacementGauche(Personnage perso, Map map);

bool deplacementBas(Personnage perso, Map map);

bool deplacementHaut(Personnage perso, Map map);

void poseBombe(Personnage perso, Map map);