#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include "BlackCore.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


using namespace std;
using namespace BlackLib;

//variaveis globais
#define matrix_left_pot 6
#define matrix_center_pot 4
#define matrix_right_pot 2


BlackGPIO 	led_left_matrix_left(GPIO_67, output);
BlackGPIO 	led_right_matrix_left(GPIO_68, output);

BlackGPIO 	led_left_matrix_right(GPIO_44, output);
BlackGPIO 	led_right_matrix_right(GPIO_26, output);

BlackGPIO 	led_left_matrix_center(GPIO_69, output);
BlackGPIO 	led_top_matrix_center(GPIO_65, output);
BlackGPIO 	led_right_matrix_center(GPIO_66, output);
BlackGPIO 	led_bottom_matrix_center(GPIO_45, output);


//biblioteca do Thiago
ADC 	potenciometro_left(matrix_left_pot);		
ADC 	potenciometro_center(matrix_center_pot);		
ADC 	potenciometro_right(matrix_right_pot);		


int sleep_left=1, sleep_center=1, sleep_right=1;
int res;
pthread_mutex_t work_mutex_left, work_mutex_right; /* proteção para: work_area e time_to_exit */
//funcao q atualiza os valores do potenciomentro





char** str_split(char *src_str, const char deliminator, size_t &num_sub_str){
  //replace deliminator's with zeros and count how many
  //sub strings with length >= 1 exist
  num_sub_str = 0;
  char *src_str_tmp = src_str;
  bool found_delim = true;
  while(*src_str_tmp){
    if(*src_str_tmp == deliminator){
      *src_str_tmp = 0;
      found_delim = true;
    }
    else if(found_delim){ //found first character of a new string
      num_sub_str++;
      found_delim = false;
      //sub_str_vec.push_back(src_str_tmp); //for c++
    }
    src_str_tmp++;
  }
  printf("Start - found %d sub strings\n", num_sub_str);
  if(num_sub_str <= 0){
    printf("str_split() - no substrings were found\n");
    return(0);
  }

  //if you want to use a c++ vector and push onto it, the rest of this function
  //can be omitted (obviously modifying input parameters to take a vector, etc)

  char **sub_strings = (char **)malloc( (sizeof(char*) * num_sub_str) + 1);
  const char *src_str_terminator = src_str_tmp;
  src_str_tmp = src_str;
  bool found_null = true;
  size_t idx = 0;
  while(src_str_tmp < src_str_terminator){
    if(!*src_str_tmp) //found a NULL
      found_null = true;
    else if(found_null){
      sub_strings[idx++] = src_str_tmp;
      //printf("sub_string_%d: [%s]\n", idx-1, sub_strings[idx-1]);
      found_null = false;
    }
    src_str_tmp++;
  }
  sub_strings[num_sub_str] = NULL;

  return(sub_strings);
}


void error(const char *msg)
{
    perror(msg);
    exit(1);
}



// void * update (void *arg){
// 	while(true){
// 		sleep_left = (int) potenciometro_left.getPercentValue();
// 		sleep_center = (int) potenciometro_center.getPercentValue();
// 		sleep_right = (int) potenciometro_right.getPercentValue();
// 		cout<<"Sleep left: "<<sleep_left<<"    ";
// 		cout<<"Sleep center: "<<sleep_center<<"		";
//         cout<<"Sleep right: "<<sleep_right<<endl;
//         sleep(1);
// 	}
// }


void * control_left_funcion (void *arg){
	while(true){
		led_left_matrix_left.setValue(high);
		led_right_matrix_left.setValue(low);
		usleep(sleep_left*20000);

		//regiao critica
		pthread_mutex_lock(&work_mutex_left); // Entrando na região crítica
		led_left_matrix_left.setValue(low);
		led_right_matrix_left.setValue(high);
		usleep(sleep_left*20000);
		pthread_mutex_unlock(&work_mutex_left); // saindo de região critica

	}
}

void * control_right_funcion (void *arg){
	while(true){
		//regiao critica
		pthread_mutex_lock(&work_mutex_right); // Entrando na região crítica
		led_left_matrix_right.setValue(high);
		led_right_matrix_right.setValue(low);
		usleep(sleep_right*20000);
		pthread_mutex_unlock(&work_mutex_right); // saindo de região critica


		led_left_matrix_right.setValue(low);
		led_right_matrix_right.setValue(high);
		usleep(sleep_right*20000);

	}
}



void * control_center_funcion (void *arg){
	while(true){

	//regiao critica
	 pthread_mutex_lock(&work_mutex_left);// Entrando na região crítica
	 led_left_matrix_center.setValue(high);
	 led_top_matrix_center.setValue(low);
	 led_right_matrix_center.setValue(low);
	 led_bottom_matrix_center.setValue(low);
	 usleep(sleep_center*20000);
	 pthread_mutex_unlock(&work_mutex_left); // saindo de região critica

	 led_left_matrix_center.setValue(low);
	 led_top_matrix_center.setValue(high);
	 led_right_matrix_center.setValue(low);
	 led_bottom_matrix_center.setValue(low);
	 usleep(sleep_center*20000);

	 //regiao critica
	 pthread_mutex_lock(&work_mutex_right);// Entrando na região crítica
	 led_left_matrix_center.setValue(low);
	 led_top_matrix_center.setValue(low);
	 led_right_matrix_center.setValue(high);
	 led_bottom_matrix_center.setValue(low);
	 usleep(sleep_center*20000);
	 pthread_mutex_unlock(&work_mutex_right); // saindo de região critica

	 led_left_matrix_center.setValue(low);
	 led_top_matrix_center.setValue(low);
	 led_right_matrix_center.setValue(low);
	 led_bottom_matrix_center.setValue(high);
	 usleep(sleep_center*20000);
	}
}
















int main(int argc, char * argv[]){
    void *thread_result;
	pthread_t update_thread, left_thread, center_thread, right_thread;

    res = pthread_mutex_init(&work_mutex_left, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&work_mutex_right, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }


    // Criar thread
    res = pthread_create(&left_thread, NULL, control_left_funcion, (void *) 0);
    if (res != 0) {
        perror("Criação da Thread left");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&center_thread, NULL, control_center_funcion, (void *) 0);
    if (res != 0) {
        perror("Criação da Thread center");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&right_thread, NULL, control_right_funcion, (void *) 0);
    if (res != 0) {
        perror("Criação da Thread right");
        exit(EXIT_FAILURE);
    }

    // res = pthread_create(&update_thread, NULL, update, (void *) 0);
    // if(res != 0){
    // 	cerr << "Erro na criação da upadte";
    // }

   //////========================novo codigo===================





     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);

     bool flag = false;
     while(1){

            clilen = sizeof(cli_addr);
            printf("Servidor esperando ...\n");
            newsockfd = accept(sockfd, 
                         (struct sockaddr *) &cli_addr, 
                         &clilen);

             if (newsockfd < 0) 
                  error("ERROR on accept");
             bzero(buffer,256);
             n = read(newsockfd,buffer,255);
             if (n < 0) error("ERROR reading from socket");
             printf("Here is the message: %s\n",buffer);
             //n = write(newsockfd,"I got your message",18);
             //if (n < 0) error("ERROR writing to socket");
             ////////////////=-------------------------------------------
             // char *mensagem = strdup(buffer);

             // printf("Mensagem: %s\n", mensagem );
			if (strpbrk(buffer, "-") != 0){
			       		printf("entrou\n");
			          	flag = true;
			       }
             //     //char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
             //    if (strstr(mensagem, "-") != NULL) {
                  char *str = strdup(buffer);
                  size_t num_sub_str;
                  char **sub_strings = str_split(str, '-', num_sub_str);
                  char *endptr;
	                  if(sub_strings && flag){
	                    if(sub_strings[0]) sleep_left = atoi(sub_strings[0]);
	                    if(sub_strings[1]) sleep_right = atoi(sub_strings[1]);
	                    if(sub_strings[2]) sleep_center = atoi(sub_strings[2]);
	                    // if(sub_strings[0]!=NULL) printf("%s\n",sub_strings[0]);
	                    // if(sub_strings[1]!=NULL) printf("%s\n",sub_strings[1]);
	                    // if(sub_strings[2]!=NULL) printf("%s\n",sub_strings[2]);


	          			}
                  //}
                  free(sub_strings);
                  free(str);

            //----------------------------------------------------
             flag = false;
             close(newsockfd);
        }







    
    pthread_join(left_thread, &thread_result);
    pthread_join(center_thread, &thread_result);
    pthread_join(right_thread, &thread_result);
    // pthread_join(update_thread, &thread_result);












	return 0;
}










