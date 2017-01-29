#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
 
//#define SERVER_IP "127.0.0.1"
#define SERVER_IP "192.168.20.101"
#define SERVER_PORT 1010
#define BUFFER 10
 
#define N_AMOSTRAS 1000
 
 
int main(void) {
    struct timeval tempo_inicial, tempo_final; 
    float tms=0, tmus=0, time_total, tempo_aux=0, tempo_medio=0; 
    int cont;
    
    int sockfd;
    int slen;
    struct sockaddr_in address;
    char message[BUFFER] = "str"; 
    // for(int i=0; i<BUFFER; i++){
    //     message[i] = 'a';
    // }   
     
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
     
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(SERVER_PORT);
     
    slen = sizeof(address);
 
    cont = 0;
    printf("novo cliente\n");
    while(cont<N_AMOSTRAS) {
        gettimeofday(&tempo_inicial, NULL); 
        if(sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *) &address, slen) < 0) {
            perror("error sendto");
            exit(-1);
        }
         
        if (recvfrom(sockfd,message, BUFFER, 0, (struct sockaddr *) &address, &slen) < 0) {
            perror("error sendto");
            exit(-1);
        }
         
        gettimeofday(&tempo_final, NULL);
        tms = (tempo_final.tv_sec - tempo_inicial.tv_sec)*1000000;//pega o tempo em milisec
        tmus = (tempo_final.tv_usec - tempo_inicial.tv_usec);//pega o tempo de microsec
        time_total = tms + tmus;
        //imprime tempo
        printf("%f\n", time_total); 
        tempo_aux += time_total;
        cont++;
    }
    tempo_medio = tempo_aux/cont/2;
    //printf("tempo de comunicação = %f\n", tempo_medio);
    close(sockfd);
    exit(0);
}