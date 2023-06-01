#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("wrong number of arguments in the command line( \n please, add IP address and port");
        exit(-1);
    }
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);
    int sockfd;
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
    printf("Клиент подошёл к администратору (серверу) оформляться на заселение!\n");
    srand(time(NULL));
    sleep(2);
    int client_sex = rand() % 2;
    if (client_sex == 1) {
        printf("Пол клиента: женский.\n");
    } else {
        printf("Пол клиента: мужской.\n");
    }
    char message1[6];
    message1[0] = 'c';
    message1[1] = (client_sex + '0');

    int place_num = rand() % 2;
    int room_add;
    if (place_num == 1) {
        printf("Клиент хочет заселиться в одноместный номер.\n");
        room_add = rand() % 10;
    } else {
        printf("Клиент хочет заселиться в двухместный номер.\n");
        room_add = rand() % 15;
    }
    message1[2] = place_num + '0';
    message1[3] = (room_add / 10) + '0';
    message1[4] = (room_add % 10) + '0';
    if (write(sockfd, message1, strlen(message1)) < 0) {
        perror("can't send message 1");
        exit(1);
    }
    printf("Клиент отошёл от стойки регистрации.\n");
    close(sockfd);
    return 0;
}
