
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char murIndestructible = 'x';
const char murDestructible = 'm';
const char perso = 'p';
const char espace = ' ';

void afficherMap(Map map) {
    printf("%d\n%d %d\n", map.nbBombes,map.longueur,map.hauteur);
    for (int i = 0; i < map.hauteur; ++i) {
        for (int j = 0; j < map.longueur; ++j) {
            printf("%c", *(*(map.map + i) + j));
        }
        printf("\n");
    }
}

char **mapUn(int id, int longueur, int hauteur, int nbBombes) {
    char** carte = malloc(sizeof(char*) * longueur);

    for (int a = 0; a < longueur; ++a) {
        carte[a] = malloc(sizeof(char) * hauteur);
    }

    for (int i = 0; i < hauteur; ++i) {//hauteur / ligne

        for (int j = 0; j < longueur; ++j) {//longueur / colonne


            if (i == 0 || i == hauteur - 1 || j == 0 ||
                j == longueur -
                     1) {                                                                               //Bordure Indestructible

                *(*(carte + i) + j) = murIndestructible;
            } else if ((i == 1 && j == 1) ||
                       (i == hauteur - 2 && j == longueur - 2)) {

                *(*(carte + i) + j) = perso;

                if (*(*(carte + i - 1) + j) != murIndestructible) {
                    *(*(carte + i - 1) + j) = espace;
                }
                if (*(*(carte + i) + j - 1) != murIndestructible) {
                    *(*(carte + i) + j - 1) = espace;
                }
                if (*(*(carte + i + 1) + j) != murIndestructible) {
                    *(*(carte + i + 1) + j) = espace;
                }
                if (*(*(carte + i) + j + 1) != murIndestructible) {
                    *(*(carte + i) + j + 1) = espace;
                }
            } else if (*(*(carte + i) + j) != espace) {
                *(*(carte + i) + j) = murDestructible;
            }
        }
    }
    return carte;
}
