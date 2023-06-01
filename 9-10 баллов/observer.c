#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int sockfd;

void sigfunc(int sig) {
    if (sig != SIGINT && sig != SIGTERM) {
        return;
    }
    printf("\nПожарная эвакуация!! Всё, всё, пока!\n");
    exit (10);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("wrong number of arguments in the command line( \n please, add IP address and port");
        exit(-1);
    }
    signal(SIGINT, sigfunc);
    signal(SIGTERM, sigfunc);
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("can't create socket");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    if (inet_aton(server_ip, &servaddr.sin_addr) == 0) {
        printf("invalid IP-address");
        close(sockfd);
        exit(1);
    }
    servaddr.sin_addr.s_addr = inet_addr(server_ip);
    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("can't connect to server");
        close(sockfd);
        exit(1);
    }
    char* message1 = "o";
    if (write(sockfd, message1, strlen(message1)) < 0) {
        perror("can't send message 1 to server");
        exit(1);
    }
    printf("Успешно установлено подключение наблюдателя к серверу.\n");
    for (;;) {
        char message2[256];
        int symbols = read(sockfd, message2, sizeof(message2));
        if (symbols < 0) {
            perror("can't get message from server");
            exit(1);
        }
        message2[symbols] = '\0';
        printf("%s", message2);
        if ((strcmp(message2, "А вот и рассвет, экскурсия окончена. Всё, конец!\n") == 0)) {
            break;
        }
    }
    close(sockfd);
    return 0;
}
