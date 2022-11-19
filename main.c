#include <stdio.h>
#include <stdlib.h>
#include "Map.c"
// PNJ BOT
void search(char objet){
    int xSize = 5;
    int ySize = 5;
    int yPlayerPos;
    int xPlayerPos;
    int playerFound = 0;
    int xObjPos;
    int yObjPos;
    int objFound = 0;

    //TODO : Attention taille des tableaux a revoir

    char tab[5][5] = {{'x','x','x','x','x'},
                      {'x',' ',' ',' ','x'},
                      {'x','m','p',' ','x'},
                      {'x',' ',' ',' ','x'},
                      {'x','x','x','x','x'},};

    for (int y = 0 ; y < ySize ; y++){
        for (int x = 0 ; x < xSize ; x++){
            if (tab[y][x] == 'p'){
                yPlayerPos = y;
                xPlayerPos = x;
                playerFound = 1;
                break;
            }
        }
        if (playerFound == 1){
            break;
        }
    }
    int i = 1;
    while(objFound == 0){
        if (tab[yPlayerPos][i] == objet ){

        }
    }
}

void start(){
    Map map = {1, 7, 5, 2, NULL};
    map.map = mapUn(map.id, map.longueur, map.hauteur, map.nbBombes);

    Map maps[] = {map};
    bool selection[] = {false};
    bool selectionEnd = false;
    do{
        int nbMap = strlen(maps);
        for(int i=0 ; i < nbMap ; i++) {
            printf("Map-%d:\n", i+1);
            afficherMap(maps[i]);
            if(selection[i] == true) {
                printf("Selected\n\n");
            } else {
                printf("Not selected\n\n");
            }
        }
        int choice = 0;
        do {
            printf("Veuillez selectionner la ou les carte(s) par leur numeros (Tapez 0 pour finir la selection):\n");
            scanf("%d", &choice);
        }while(choice > nbMap & choice < 0);

        if(choice == 0) {
            int selected = 0;
            for(int i=0 ; i < nbMap ; i++) {
                if(selection[i] == true) {
                    selected++;
                }
            }
            if(selected == 0) {
                printf("Veuillez selectionner au moins une map !\n");
            }
            else {
                break;
            }
        }

        if(selection[choice-1] == true){
            selection[choice-1] = false;
        }
        else if(selection[choice-1] == false){
            selection[choice-1] = true;
        }

        printf("\n");
    }while(selectionEnd == false);


}

int main() {
    int choix = 1;
    while(choix > 0 && choix < 4) {
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
