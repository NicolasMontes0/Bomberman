#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

const char murIndestructible = 'x';
const char murDestructible = 'm';
const char persoCar = 'p';
const char espaceCar = ' ';

void start() {
    Map map = {1, 7, 5, 1, NULL, 2};
    map.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Map map2 = {2, 7, 5, 2, NULL, 2};
    map2.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Map map3 = {3, 7, 5, 3, NULL, 2};
    map3.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

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

    int tours = 0;
    int choice = 1;
    int lastMap = -1;
    bool win = true;
    char touche = '0';
    Map currentMap = selectedMap[0];
    Personnage *players = malloc(sizeof(Personnage));
    int currentPlayer = 0;
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
            lastMap = randomMap;
            currentMap = selectedMap[randomMap];
            players = realloc(players, sizeof(Personnage)*currentMap.nbJoueurs);
            int nbJoueurs = 0;
            for (int i = 0; i < currentMap.hauteur; ++i) {
                for (int j = 0; j < currentMap.longueur; ++j) {
                    if(currentMap.map[i][j] == persoCar) {
                        nbJoueurs++;
                        currentMap.map[i][j] = nbJoueurs+'0';
                        Personnage player = {nbJoueurs+'0', nbJoueurs, j, i, currentMap.nbBombes, false};
                        players[nbJoueurs-1] = player;
                    }
                }
            }

            printf("La map tire au sort est:\n");
            afficherMap(currentMap);
            printf("\nLa partie commence !\n\n");
            win = false;
        }
        if (currentPlayer == 0) {
            afficherMap(currentMap);
            printf("Selectionner une action:\n z-Avancer vers le haut\n s-Avancer vers le bas \n q-Avancer vers la gauche \n d-Avancer vers la droite \n");

            while(getchar() != '\n');
            scanf("%c", &touche);
            switch (touche) {
                case 'd' :
                    if (players[currentPlayer].posX == currentMap.longueur-1 && currentMap.map[players[currentPlayer].posY][0] == espaceCar){
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                        players[currentPlayer].posX = 0;
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                    }
                    else {
                        if (currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX+1] == ' ') {
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                            players[currentPlayer].posX++;
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                        }
                    }
                    break;
                case 'q' :
                    if (players[currentPlayer].posX == 0 && currentMap.map[players[currentPlayer].posY][currentMap.longueur-1] == espaceCar){
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                        players[currentPlayer].posX = currentMap.longueur-1;
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                    }
                    else {
                        if (currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX-1] == ' ') {
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                            players[currentPlayer].posX--;
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                        }
                    }
                    break;
                case 'z' :
                    if (players[currentPlayer].posY == 0 && currentMap.map[currentMap.hauteur-1][players[currentPlayer].posX] == espaceCar){
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                        players[currentPlayer].posY = currentMap.hauteur-1;
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                    }
                    else {
                        if (currentMap.map[players[currentPlayer].posY-1][players[currentPlayer].posX] == ' ') {
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                            players[currentPlayer].posY--;
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                        }
                    }
                    break;
                case 's' :
                    if (players[currentPlayer].posY == currentMap.hauteur-1 && currentMap.map[0][players[currentPlayer].posX] == espaceCar){
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                        players[currentPlayer].posY = 0;
                        currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                    }
                    else {
                        if (currentMap.map[players[currentPlayer].posY+1][players[currentPlayer].posX] == ' ') {
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = espaceCar;
                            players[currentPlayer].posY++;
                            currentMap.map[players[currentPlayer].posY][players[currentPlayer].posX] = players[currentPlayer].symbole;
                        }
                    }
                    break;
                case 'e' :

                default:;
                    printf("Mauvaise selection !!!\n");
                    break;
            }
        }
        else {
            ia();
            tours++;
        }
        currentPlayer++;
        if(currentPlayer >= currentMap.nbJoueurs) {
            currentPlayer = 0;
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
            printf("%c", map.map[i][j]);
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

                *(*(carte + i) + j) = persoCar;

                if (*(*(carte + i - 1) + j) != murIndestructible) {
                    *(*(carte + i - 1) + j) = espaceCar;
                }
                if (*(*(carte + i) + j - 1) != murIndestructible) {
                    *(*(carte + i) + j - 1) = espaceCar;
                }
                if (*(*(carte + i + 1) + j) != murIndestructible) {
                    *(*(carte + i + 1) + j) = espaceCar;
                }
                if (*(*(carte + i) + j + 1) != murIndestructible) {
                    *(*(carte + i) + j + 1) = espaceCar;
                }
            } else if (*(*(carte + i) + j) != espaceCar) {
                *(*(carte + i) + j) = murDestructible;
            }
        }
    }
    *(*(carte + 2) + 0) = espaceCar;
    *(*(carte + 2) + longueur-1) = espaceCar;
    *(*(carte + 0) + 1) = espaceCar;
    *(*(carte + hauteur-1) + 1) = espaceCar;
    return carte;
}

// PNJ BOT
void ia() {

}

void poseBombe(Personnage perso, Map map) {
    map.map[perso.posY][perso.posX] = 'x';

}