#include <stdio.h>
#include <stdlib.h>
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
                      {'x',NULL,NULL,NULL,'x'},
                      {'x','m','p',NULL,'x'},
                      {'x',NULL,NULL,NULL,'x'},
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
}
int main() {
    int choix = 0;
    printf("Veuillez choisir entre les different choix\n"
           "1-Demarrer \n"
           "2-Demarrer le serveur\n"
           "3-Rejoindre un serveur\n"
           "4-Quitter le jeux\n");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("vous commencez une partie en solo\n");
                search('m');
                break;
        case 2:
                break;
        case 3:
                break;
        case 4:
            exit(EXIT_FAILURE);
                break;
    }
}
