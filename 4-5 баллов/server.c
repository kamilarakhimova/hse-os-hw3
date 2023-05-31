#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define MAX_CLIENTS 2

int client_sockets[MAX_CLIENTS];

void room_single_add(int client_sex, int room_add, int* single_rooms) {
    if (single_rooms[room_add] == 10) {
        single_rooms[room_add] = client_sex;
        if (client_sex == 1) {
            printf("Клиентка-дама заселилась в одноместный номер %d.\n", room_add + 1);
        } else {
            printf("Клиент-джентльмен заселился в одноместный номер %d.\n", room_add + 1);
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в одноместный номер ");
        } else {
            printf("Клиент-джентльмен не смог заселиться в одноместный номер ");
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
    }
}

void room_double_add(int client_sex, int room_add, int* double_rooms) {
    if (double_rooms[room_add] == 10 || double_rooms[room_add + 15] == 10) {
        if (double_rooms[room_add] != 10) {
            if (double_rooms[room_add] == client_sex) {
                double_rooms[room_add + 15] = client_sex;
                if (client_sex == 1) {
                    printf("Клиентка-дама заселилась второй в двухместный номер %d.\n", room_add + 1);
                } else {
                    printf("Клиент-джентльмен заселился вторым в двухместный номер %d.\n", room_add + 1);
                }
            } else {
                if (client_sex == 1) {
                    printf("Клиентка-дама не смогла заселиться в двухместный номер ");
                } else {
                    printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
                }
                printf("%d, так как одно место в нём уже занято клиентом противоположного пола.\n", room_add + 1);
            }
        } else {
            double_rooms[room_add] = client_sex;
            if (client_sex == 1) {
                printf("Клиентка-дама заселилась первой в двухместный номер %d.\n", room_add + 1);
            } else {
                printf("Клиент-джентльмен заселился первым в двухместный номер %d.\n", room_add + 1);
            }
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в двухместный номер ");
        } else {
            printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("wrong number of arguments in the command line( \n please, add port number");
        exit(1);
    }
    int server_port = atoi(argv[1]);
    int server_sockfd, client_sockfd;
    struct sockaddr_in servaddr, clientaddr;
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("can't create socket");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("can't bind socket");
        exit(1);
    }
    printf("server ip address = %s\n", inet_ntoa(clientaddr.sin_addr));
    if (listen(server_sockfd, MAX_CLIENTS) < 0) {
        perror("can't listen for connections");
        exit(1);
    }
    srand(time(NULL));
    int single_rooms[10];
    for (int i = 0; i < 10; ++i) {
        single_rooms[i] = 10;
    }
    int double_rooms[30];
    for (int i = 0; i < 30; ++i) {
        double_rooms[i] = 10;
    }
    printf("Добро пожаловать на ночную экскурсию в отель.\n");
    printf("Вы задали количество клиентов, ожидающих заселения, равным: %d.\n", MAX_CLIENTS);
    printf("Администратор (сервер) готов заселять клиентов.\n");

    int i = 0;
    for (;;) {
        socklen_t clntlen = sizeof(clientaddr);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &clientaddr, &clntlen);
        if (client_sockfd < 0) {
            perror("can't accept connection");
            exit(1);
        }
        client_sockets[i] = client_sockfd;
        // printf("server is handling client %s\n", inet_ntoa(clientaddr.sin_addr));
        printf("Администратор (сервер) обрабатывает клиента %d.\n", i + 1);
        ++i;
        char message1[256];
        int symbols1 = read(client_sockets[i], message1, sizeof(message1));
        if (symbols1 < 0) {
            perror("can't get message 1");
            exit(1);
        }
        message1[symbols1] = '\0';
        int client_sex = atoi(message1);
        char message2[256];
        int symbols2 = read(client_sockets[i], message2, sizeof(message2));
        if (symbols2 < 0) {
            perror("can't get message2");
            exit(1);
        }
        message2[symbols2] = '\0';
        int room_number = atoi(message2);
        printf("Администратор (сервер) заселяет клиента в комнату %d.\n", room_number + 1);  
        room_single_add(client_sex, room_number, single_rooms);
        if (i == MAX_CLIENTS) {
            break;
        }
    }
  
    printf("А вот и рассвет, экскурсия окончена. Всё, конец!\n");
    for (i = 0; i < MAX_CLIENTS; ++i) {
        close(client_sockets[i]);
    }
    close(server_sockfd);
    return 0;
}
