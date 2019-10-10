#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256
#define MONKEY_DIGIT_SIZE 10

void commun(int);
void DieWithError(char *);
void my_scanf();
int prepare_server_socket(int);

int main()
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port");

    int sock = pthread_client_socket(argv[1], atoi[2]);
}