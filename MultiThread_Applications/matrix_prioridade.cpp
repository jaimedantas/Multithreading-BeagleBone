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


int sleep_left, sleep_center, sleep_right;
int res;
pthread_mutex_t work_mutex_left, work_mutex_right; /* proteção para: work_area e time_to_exit */
//funcao q atualiza os valores do potenciomentro
void * update (void *arg){
	while(true){
		sleep_left = (int) potenciometro_left.getPercentValue();
		sleep_center = (int) potenciometro_center.getPercentValue();
		sleep_right = (int) potenciometro_right.getPercentValue();
		cout<<"Sleep left: "<<sleep_left<<"    ";
		cout<<"Sleep center: "<<sleep_center<<"		";
        cout<<"Sleep right: "<<sleep_right<<endl;
        sleep(1);
	}
}


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

    res = pthread_create(&update_thread, NULL, update, (void *) 0);
    if(res != 0){
    	cerr << "Erro na criação da upadte";
    }
    
    pthread_join(left_thread, &thread_result);
    pthread_join(center_thread, &thread_result);
    pthread_join(right_thread, &thread_result);
    pthread_join(update_thread, &thread_result);

	return 0;
}










