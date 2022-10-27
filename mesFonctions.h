typedef struct {
    char* name;
    char* IP;
} user;

int connectToServer(char* IP, int port);

int sendMess(int socket, char* query);

char* readMess (int socket);

int createServer(struct sockaddr_in sa);

int createConnexion(int sockServer, struct sockaddr_in * sa);

int sendStruct(int socket, user* user);

user * readStruct(int socket);

void * thread(void * args);

void client (char* ip, int port);

int main(int argc, char const *argv[]);