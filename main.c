#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

const char murIndestructible = 'x';
const char murDestructible = 'm';
const char perso = 'p';
const char espace = ' ';

void start() {
    Map map = {1, 7, 5, 1, NULL};
    map.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Map map2 = {2, 7, 5, 2, NULL};
    map2.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Map map3 = {3, 7, 5, 3, NULL};
    map3.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Personnage Joueur1 = {'1', 1, 1, 1, 2};
    Personnage Joueur2 = {'2', 2, map.hauteur - 2, map.longueur - 2, 1};

    Map maps[] = {map, map2, map3};
    size_t nbMap = sizeof(maps) / sizeof(Map);
    bool selection[nbMap];

    for (int i = 0; i < nbMap; i++) {
        selection[i] = false;
    }
    bool selectionEnd = false;
    int selected = 0;
    do {
        for (int i = 0; i < nbMap; i++) {
            printf("Map-%d:\n", i + 1);
            afficherMap(maps[i]);
            if (selection[i] == true) {
                printf("Selected\n\n");
            } else {
                printf("Not selected\n\n");
            }
        }
        int choice = 0;
        printf("Veuillez selectionner la ou les carte(s) par leur numeros (Tapez 0 pour finir la selection):\n");
        scanf("%d", &choice);

        if (choice == 0) {
            selected = 0;
            for (int i = 0; i < nbMap; i++) {
                if (selection[i] == true) {
                    selected++;
                }
            }
            if (selected == 0) {
                printf("Veuillez selectionner au moins une map !\n");
            } else {
                selectionEnd = true;
            }
        }

        if (choice <= nbMap && selection[choice - 1] == true) {
            selection[choice - 1] = false;
        } else if (choice <= nbMap && selection[choice - 1] == false) {
            selection[choice - 1] = true;
        }

        printf("\n");
    } while (selectionEnd == false);

    Map selectedMap[selected];
    int index = 0;
    for (int i = 0; i < nbMap; i++) {
        if (selection[i] == true) {
            selectedMap[index] = maps[i];
            index++;
        }
    }

    int choice = 1;
    int lastMap = -1;
    bool win = true;
    char touche = '0';
    do {
        if (win == true) {
            printf("Veuillez selectionner une action:\n"
                   "0-Revinir au menu principal \n"
                   "Autre-Commencer une map\n");
            scanf("%d", &choice);

            if (choice == 0) {
                break;
            }
            int randomMap = 0;
            do {
                randomMap = rand() % selected;
            } while (randomMap == lastMap && selected != 1);
            Map currentMap = selectedMap[randomMap];
            lastMap = randomMap;

            printf("La map tire au sort est:\n");
            afficherMap(currentMap);
            printf("\nLa partie commence !\n\n");
        }

        scanf("Deplacement 1er joueur : %c", &touche);
        switch (touche) {
            case 'd' :
                if (deplacementDroite(Joueur1, map) == true) {
                    afficherMap(map);
                }
                break;
            case 'q' :
                if (deplacementGauche(Joueur1, map) == true) {
                    afficherMap(map);
                }
                break;
            case 'z' :
                if (deplacementHaut(Joueur1, map) == true) {
                    afficherMap(map);
                }
                break;
            case 's' :
                if (deplacementBas(Joueur1, map) == true) {
                    afficherMap(map);
                }
                break;
            default:;
                printf("%d %d\n", Joueur1.posY, Joueur1.posX);
                printf("%c\n", map.map[1][1]);
                break;
        }
    } while (choice != 0);
}

int main() {
    int choix = 1;
    while (choix > 0 && choix < 4) {
        printf("Veuillez selectionner une action:\n"
               "1-Demarrer \n"
               "2-Demarrer le serveur\n"
               "3-Rejoindre un serveur\n"
               "Autre-Quitter le jeux\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Vous commencez une partie en solo...\n");
                start();
                break;
            case 2:
                printf("Vous ouvrez un serveur...\n");
                break;
            case 3:
                printf("Vous vous connecter au serveur...\n");
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}

void afficherMap(Map map) {
    printf("%d\n%d %d\n", map.nbBombes, map.longueur, map.hauteur);
    for (int i = 0; i < map.hauteur; ++i) {
        for (int j = 0; j < map.longueur; ++j) {
            printf("%c", *(*(map.map + i) + j));
        }
        printf("\n");
    }
}

char **mapUn(int id, int longueur, int hauteur, int nbBombes) {
    char **carte = malloc(sizeof(char *) * longueur);

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

// PNJ BOT
void search(char objet) {
    int xSize = 5;
    int ySize = 5;
    int yPlayerPos;
    int xPlayerPos;
    int playerFound = 0;
    int xObjPos;
    int yObjPos;
    int objFound = 0;

    //TODO : Attention taille des tableaux a revoir

    char tab[5][5] = {{'x', 'x', 'x', 'x', 'x'},
                      {'x', ' ', ' ', ' ', 'x'},
                      {'x', 'm', 'p', ' ', 'x'},
                      {'x', ' ', ' ', ' ', 'x'},
                      {'x', 'x', 'x', 'x', 'x'},};

    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            if (tab[y][x] == 'p') {
                yPlayerPos = y;
                xPlayerPos = x;
                playerFound = 1;
                break;
            }
        }
        if (playerFound == 1) {
            break;
        }
    }
    int i = 1;
    while (objFound == 0) {
        if (tab[yPlayerPos][i] == objet) {

        }
    }
}

bool deplacementDroite(Personnage perso, Map map) {
    if (perso.posX + 1 == ' ') {
        return true;
    } else {
        return false;
    }
}

bool deplacementGauche(Personnage perso, Map map) {
    if (perso.posX - 1 == ' ') {
        return true;
    } else {
        return false;
    }
}

bool deplacementBas(Personnage perso, Map map) {
    if (perso.posY + 1 == ' ') {
        return true;
    } else {
        return false;
    }
}

bool deplacementHaut(Personnage perso, Map map) {
    if (perso.posY - 1 == ' ') {
        return true;
    } else {
        return false;
    }
}

void poseBombe(Personnage perso, Map map) {
    map.map[perso.posY][perso.posX] = 'x';
}