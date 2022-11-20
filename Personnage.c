#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Personnage.h"

void deplacementDroite(Personnage perso, Map map) {
    map.map[perso.posX][perso.posY] = ' ';
    ++perso.posX;
    if (perso.posX > map.longueur && map.map[perso.posX][perso.posY] == ' ') {
        perso.posX -= map.longueur;
    }
    map.map[perso.posX][perso.posY] = 'p';
}

void deplacementGauche(Personnage perso, Map map) {
    map.map[perso.posX][perso.posY] = ' ';
    --perso.posX;
    if (perso.posX < 0 && map.map[perso.posX][perso.posY] == ' ') {
        perso.posX += map.longueur;
    }
}

void deplacementBas(Personnage perso, Map map) {
    map.map[perso.posX][perso.posY] = ' ';
    ++perso.posY;
    if (perso.posY > map.hauteur && map.map[perso.posX][perso.posY] == ' ') {
        perso.posY -= map.hauteur;
    }
}

void deplacementHaut(Personnage perso, Map map) {
    map.map[perso.posX][perso.posY] = ' ';
    --perso.posY;
    if (perso.posY < 0 && map.map[perso.posX][perso.posY] == ' ') {
        perso.posY += map.hauteur;
    }
}

void Deplacement(Personnage perso, char c, Map map) {
    if (c == 100 || c == 68) {              //d-D
        deplacementDroite(perso, map);
    } else if (c == 115 || c == 83) {       //s-S
        deplacementBas(perso, map);
    } else if (c == 122 || c == 90) {       //z-Z
        deplacementHaut(perso, map);
    } else if (c == 113 || c == 81) {       //q-Q
        deplacementGauche(perso, map);
    }
}
//Devons-nous remplacer manuellement le char où il y a le perosnnage par ' ''perso.posX = espace et rajouter par exemple a posX perso.symbole? ou bien la fonction deplacement suffit?
