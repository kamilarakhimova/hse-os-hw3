#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define MAX_CLIENTS 2
#define MAX_OBSERVERS 2

int client_sockets[MAX_CLIENTS];
int observer_sockets[MAX_OBSERVERS];
char observer_message[256];
int observer_symbols;
int server_port;
int server_sockfd, client_sockfd;
struct sockaddr_in servaddr, clientaddr;
socklen_t clntlen;

void send_observer(char* message) {
    for (int i = 0; i < MAX_OBSERVERS; ++i) {
        int flag = 1;
        while (flag) {
    	    if (write(observer_sockets[i], message, strlen(message)) < 0) {
                printf("Ой, наблюдатель %d покинул нас( Ну ничего, посидим, подождём его...\n", i + 1);
                clntlen = sizeof(clientaddr);
		client_sockfd = accept(server_sockfd, (struct sockaddr*) &clientaddr, &clntlen);
                printf("Порядок, наблюдатель %d вернулся в строй.\n", i + 1);
		if (client_sockfd < 0) {
                    perror("can't send messsage to observer");
                    exit(1);
		}
		observer_sockets[i] = client_sockfd;
    	    } else {
		flag = 0;
	    }
        }
    }
}

void room_single_add(int client_sex, int room_add, int* single_rooms) {
    if (single_rooms[room_add] == 10) {
        single_rooms[room_add] = client_sex;
        if (client_sex == 1) {
            printf("Клиентка-дама заселилась в одноместный номер %d.\n", room_add + 1);
            sprintf(observer_message, "Клиентка-дама заселилась в одноместный номер %d.\n", room_add + 1);
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен заселился в одноместный номер %d.\n", room_add + 1);
            sprintf(observer_message, "Клиент-джентльмен заселился в одноместный номер %d.\n", room_add + 1);
            send_observer(observer_message);
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в одноместный номер ");
            sprintf(observer_message, "Клиентка-дама не смогла заселиться в одноместный номер ");
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен не смог заселиться в одноместный номер ");
            sprintf(observer_message, "Клиент-джентльмен не смог заселиться в одноместный номер ");
            send_observer(observer_message);
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
        sprintf(observer_message, "%d, так как он уже занят.\n", room_add + 1);
        send_observer(observer_message);
    }
}

void room_double_add(int client_sex, int room_add, int* double_rooms) {
    if (double_rooms[room_add] == 10 || double_rooms[room_add + 15] == 10) {
        if (double_rooms[room_add] != 10) {
            if (double_rooms[room_add] == client_sex) {
                double_rooms[room_add + 15] = client_sex;
                if (client_sex == 1) {
                    printf("Клиентка-дама заселилась второй в двухместный номер %d.\n", room_add + 1);
                    sprintf(observer_message, "Клиентка-дама заселилась второй в двухместный номер %d.\n", room_add + 1);
                    send_observer(observer_message);
                } else {
                    printf("Клиент-джентльмен заселился вторым в двухместный номер %d.\n", room_add + 1);
                    sprintf(observer_message, "Клиент-джентльмен заселился вторым в двухместный номер %d.\n", room_add + 1);
                    send_observer(observer_message);
                }
            } else {
                if (client_sex == 1) {
                    printf("Клиентка-дама не смогла заселиться в двухместный номер ");
                    sprintf(observer_message, "Клиентка-дама не смогла заселиться в двухместный номер ");
                    send_observer(observer_message);
                } else {
                    printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
                    sprintf(observer_message, "Клиент-джентльмен не смог заселиться в двухместный номер ");
                    send_observer(observer_message);
                }
                printf("%d, так как одно место в нём уже занято клиентом противоположного пола.\n", room_add + 1);
                sprintf(observer_message, "%d, так как одно место в нём уже занято клиентом противоположного пола.\n", room_add + 1);
                send_observer(observer_message);
            }
        } else {
            double_rooms[room_add] = client_sex;
            if (client_sex == 1) {
                printf("Клиентка-дама заселилась первой в двухместный номер %d.\n", room_add + 1);
                sprintf(observer_message, "Клиентка-дама заселилась первой в двухместный номер %d.\n", room_add + 1);
                send_observer(observer_message);
            } else {
                printf("Клиент-джентльмен заселился первым в двухместный номер %d.\n", room_add + 1);
                sprintf(observer_message, "Клиент-джентльмен заселился первым в двухместный номер %d.\n", room_add + 1);
                send_observer(observer_message);
            }
        }
    } else {
        if (client_sex == 1) {
            printf("Клиентка-дама не смогла заселиться в двухместный номер ");
            sprintf(observer_message, "Клиентка-дама не смогла заселиться в двухместный номер ");
            send_observer(observer_message);
        } else {
            printf("Клиент-джентльмен не смог заселиться в двухместный номер ");
            sprintf(observer_message, "Клиент-джентльмен не смог заселиться в двухместный номер ");
            send_observer(observer_message);
        }
        printf("%d, так как он уже занят.\n", room_add + 1);
        sprintf(observer_message, "%d, так как он уже занят.\n", room_add + 1);
        send_observer(observer_message);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("wrong number of arguments in the command line( \n please, add port number");
        exit(1);
    }
    struct sigaction new_actn, old_actn;
    new_actn.sa_handler = SIG_IGN;
    sigemptyset(&new_actn.sa_mask);
    new_actn.sa_flags = 0;
    sigaction(SIGPIPE, &new_actn, &old_actn);
    // источник: https://stackoverflow.com/questions/1795193/check-connection-open-or-closed-in-c-in-linux
    server_port = atoi(argv[1]);
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
    if (listen(server_sockfd, MAX_CLIENTS + MAX_OBSERVERS) < 0) {
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
    printf("Вы задали количество наблюдателей равным: %d.\n", MAX_OBSERVERS);
    printf("Администратор (сервер) готов заселять клиентов.\n");

    int i = 0; // clients
    int j = 0; // observers
    for (;;) {
        clntlen = sizeof(clientaddr);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &clientaddr, &clntlen);
        if (client_sockfd < 0) {
            perror("can't accept connection");
            exit(1);
        }
        char message1[256];
        int symbols = read(client_sockfd, message1, sizeof(message1));
        if (symbols < 0) {
            perror("can't get message");
            exit(1);
        }
        message1[symbols] = '\0';
        char f = message1[0];
        if (f == 'o') {
            // observer connection
            observer_sockets[j] = client_sockfd;
            printf("К администратору (серверу) подключился наблюдатель %d.\n", j + 1);
            sprintf(observer_message, "К администратору (серверу) подключился наблюдатель %d.\n", j + 1);
            send_observer(observer_message);
            ++j;
            if (j == MAX_OBSERVERS) {
        	break;
	    }
        }
    
    }
    for (;;) {
        clntlen = sizeof(clientaddr);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &clientaddr, &clntlen);
        if (client_sockfd < 0) {
            perror("can't accept connection");
            exit(1);
        }

        char message1[256];
        int symbols = read(client_sockfd, message1, sizeof(message1));
        if (symbols < 0) {
            perror("can't get message");
            exit(1);
        }
        message1[symbols] = '\0';
        char f = message1[0];
        if (f == 'c') {
            // client connection
            client_sockets[i] = client_sockfd;
            printf("Администратор (сервер) обрабатывает клиента %d.\n", i + 1);
            sprintf(observer_message, "Администратор (сервер) обрабатывает клиента %d.\n", i + 1);
            send_observer(observer_message);
            int client_sex = message1[1] - '0';
            int place_number = message1[2] - '0';
            int room_number_first = message1[3] - '0';
            int room_number_second = message1[4] - '0';
            int room_number = room_number_first * 10 + room_number_second;
            printf("Администратор (сервер) заселяет клиента в комнату %d.\n", room_number + 1);
            sprintf(observer_message, "Администратор (сервер) заселяет клиента в комнату %d.\n", room_number + 1);
            send_observer(observer_message);
            if (place_number == 1) {
                room_single_add(client_sex, room_number, single_rooms);
            } else {
                room_double_add(client_sex, room_number, double_rooms);
            }
            ++i;
        } else {
            printf("Ищем покинувшего нас наблюдателя\n");
            char message[256];
            sprintf(message, "Ищем покинувшего нас наблюдателя\n");
            for (int k = 0; k < MAX_OBSERVERS; ++k) {
            	int flag = 1;
            	while (flag) {
    	    	    if (write(observer_sockets[k], message, strlen(message)) < 0) {
                    	printf("Ой, наблюдатель %d покинул нас( Ну ничего, посидим, подождём его...\n", k + 1);
                    	clntlen = sizeof(clientaddr);
		    	client_sockfd = accept(server_sockfd, (struct sockaddr*) &clientaddr, &clntlen);
                    	printf("Порядок, наблюдатель %d вернулся в строй.\n", k + 1);
		    	if (client_sockfd < 0) {
                            perror("can't send message to observer");
                            exit(1);
		    	}
		    	observer_sockets[k] = client_sockfd;
    	            } else {
		    	flag = 0;
	            }
            	}
            }
        }
        if (i == MAX_CLIENTS) {
            break;
        }
    }
    sleep(2);
    printf("А вот и рассвет, экскурсия окончена. Всё, конец!\n");
    sprintf(observer_message, "А вот и рассвет, экскурсия окончена. Всё, конец!\n");
    send_observer(observer_message);
    for (i = 0; i < MAX_CLIENTS; ++i) {
        close(client_sockets[i]);
    }
    for (i = 0; i < MAX_OBSERVERS; ++i) {
        close(observer_sockets[i]);
    }
    close(server_sockfd);
    return 0;
}
