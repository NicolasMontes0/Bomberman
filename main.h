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

struct Bombe{
    int timer;
    int portee;
    int bPosX;
    int bPosY;
}typedef Bombe;

struct Personnage {
    char symbole;
    int id;
    int posX;
    int posY;
    int nbDebombes;
    Bombe *bombe;
    int portee;
    bool invincibilite;
    bool coeur;
    int pdv;
    bool passeBombe;
    bool bombKick;
} typedef Personnage;

void afficherMap(Map map);

char **mapUn(int id, int longueur, int hauteur, int nbBombes);

void ia();

void poseBombe(Personnage personnage, Map map);

void explosionBombe(Personnage personnage, Map map);

void bombUp(Personnage personnage);

void bombDown(Personnage personnage);