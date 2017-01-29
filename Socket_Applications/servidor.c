#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 
//#define SERVER_IP "192.168.7.2"
#define SERVER_PORT 1010
#define BUFFER 10
 
 
int main(void) {
    int server_sockfd, client_sockfd;
    int recv;
 
     
    size_t server_len;
    socklen_t client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
     
    char message[BUFFER];

    if((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf(" Houve erro na ebertura do socket ");
        exit(-1);
    }
     
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);
     
    server_len = sizeof(server_address);
     
    if(bind(server_sockfd, (struct sockaddr *) &server_address, server_len) < 0) {
        perror("error bind");
        exit(-1);
    }
     
    client_len = sizeof(client_address);
    printf("servidor novo escutando...\n");
    while(1) {
        if(recv = recvfrom(server_sockfd, message, BUFFER, 0, (struct sockaddr *) &server_address, &client_len) < 0 ) {
            perror("error recvfrom");
            exit(-1);
        }
 
        //printf("server recebeu: %s \n", message);
        if (sendto(server_sockfd, message, recv, 0, (struct sockaddr*) &server_address, client_len) < 0) {
            perror("error sendto");
            exit(-1);
        }
        //printf("server mandou: %s \n\n", message);
        
    }
}