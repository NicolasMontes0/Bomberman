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
    int nbJoueurs;
} typedef Map;

struct Personnage {
    char symbole;
    int id;
    int posX;
    int posY;
    int nbDebombes;
    bool mort;
} typedef Personnage;

void afficherMap(Map map);

char **mapUn(int id, int longueur, int hauteur, int nbBombes);

void ia();

void poseBombe(Personnage perso, Map map);