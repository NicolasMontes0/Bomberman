
#ifndef CASSEPARPAING_MAP_H
#define CASSEPARPAING_MAP_H

#endif //CASSEPARPAING_MAP_H

struct Map {
    int id;
    int longueur;
    int hauteur;
    int nbBombes;
    char** map;
} typedef Map;

void afficherMap(Map map);

char **mapUn(int id, int longueur, int hauteur, int nbBombes);
