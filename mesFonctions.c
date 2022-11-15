#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <winsock2.h> // librairie requise pour les sockets sous windows
#include <fcntl.h>
#include "mesFonctions.h"

int connectToServer(char* IP, int port) {
    //Déclaration de la structure et initialisation de la structure
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port); //htons() convertit son paramètre en binaire. h -> host; to; n -> network; s -> short
    sa.sin_addr.s_addr = (long)inet_addr(IP);

    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if( sd == -1) {
        perror("erreur de création de socket !");
        return -1;
    }

    int err = connect(sd, (struct sockaddr *)&sa, sizeof(sa));
    if(err == -1) {
        perror("erreur de connexion !");
        return -1;
    }

    return sd;
}

int sendMess(int socket, char* query) {
    int nbOctet = send(socket, query, strlen(query)+1, 0);
    return nbOctet;
}

char* readMess (int socket) {
    int index = 0;
    char c = 1;
    char * message = (char *)malloc(sizeof(char));
    while(c != '\0'){
        int nbOctet = recv(socket, &c, 1, 0);
        *(message + index) = c;
        message = realloc(message, sizeof(char)*(index+1));
        index++;
    }
    *(message + index) = '\0';
    return message;
}

int createServer(struct sockaddr_in sa) {
    int socketServeur = -1;

    socketServeur = socket(PF_INET, SOCK_STREAM, 0);

    if(socketServeur == -1) {
        perror("erreur de creation de socket");
        return -1;
    }

    int errBind = bind(socketServeur, (struct sockaddr *)&sa, sizeof(sa));

    if(errBind == -1) {
        perror("erreur de bind");
        return -1;
    }

    int errListen = listen(socketServeur, SOMAXCONN);

    if(errListen == -1)  {
        perror("erreur de file d'attente");
        return -1;
    }

    return socketServeur;
}

int createConnexion(int socketServer, struct sockaddr_in *sa) {
    int sockConn = -1;

    int size_sa = sizeof(sa);

    sockConn = accept(socketServer, (struct sockaddr*)&sa, &size_sa);

    if(sockConn == -1)  {
        perror("erreur de connexion du client");
        return -1;
    }

    return sockConn;
}

int sendStruct(int socket, user* usr){
    int nbOctName = sendMess(socket, usr->name);
    int nbOctIp = sendMess(socket, usr->IP);
    return (nbOctName + nbOctIp);
}

user * readStruct(int socket){
    user* usr= (user*)malloc(sizeof(user));
    usr->name =(char *) malloc(sizeof(char));
    usr->IP =(char *) malloc(sizeof(char));
    usr->name = readMess(socket);
    usr->IP = readMess(socket);
    return usr;
}

void * thread(void * args) {
    int * socketClient = (int *) args;
    char * message = readMess(*socketClient);

    printf("Message du client : %s\n", message);
    sendMess(*socketClient, message);

    close(*socketClient);
    pthread_exit(EXIT_SUCCESS);

}

void client (char* ip, int port) {
    int socketDuMain = connectToServer(ip, port);

    printf("L'identifiant de la socket = %d\n", socketDuMain);
    sendMess(socketDuMain, "Salut, c Nico !");
    printf("Reponse : %s\n\n", readMess(socketDuMain));
}

int server(int argc, char const *argv[]) {
    char * ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = (long)inet_addr(ip);

    int sockServer = createServer(sa);

    pthread_t tid;
    while(1){
        int sockClient = createConnexion(sockServer, &sa);

        if (sockClient == -1){
            perror("Connexion refusée");
            exit(EXIT_FAILURE);
        }
        pthread_create(&tid, NULL, thread, &sockClient);
        pthread_join(tid, NULL);
    }
}