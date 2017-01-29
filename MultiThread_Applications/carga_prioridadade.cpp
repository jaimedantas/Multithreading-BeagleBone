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



using namespace std;
using namespace BlackLib;

//variaveis globais
#define pin_prioridade_A 4
#define pin_prioridade_B 6


BlackGPIO 	led_A(GPIO_30, output);
BlackGPIO 	led_B(GPIO_60, output);
//biblioteca do Thiago
ADC 	prioridade_A(pin_prioridade_A);		
ADC 	prioridade_B(pin_prioridade_B);		

int valor_prioridade_A;
int valor_prioridade_B;
int res;
pthread_t a_thread, b_thread, update_thread;
pthread_attr_t thread_attr_A, thread_attr_B, thread_attr_update;
sched_param scheduling_value_A, scheduling_value_B, scheduling_value_update;
int  max_priority, min_priority;

// int res;
// pthread_t a_thread, b_thread, update_thread;
// pthread_attr_t thread_attr, thread_attr_B;
// //void *thread_result;
// sched_param scheduling_value, scheduling_value_B;
// int  max_priority, min_priority;


// função para simular carregamento da CPU
void carga(int k){
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }
}

void * acenderLed_B (void *arg){
	while(true){
        led_B.setValue(low);
        carga(500);
        led_B.setValue(high);
        carga(500);
	}
}

void * acenderLed_A (void *arg){
	while(true){
		led_A.setValue(low);
        carga(500);
        led_A.setValue(high);
        carga(500);
	}
}

void * update (void *arg){
	while(true){
		valor_prioridade_A = (int) prioridade_A.getPercentValue();
		valor_prioridade_B = (int) prioridade_B.getPercentValue();
		cout<<"prioridade A: "<<valor_prioridade_A<<"    ";
		cout<<"prioridade B: "<<valor_prioridade_B<<endl;
        
        scheduling_value_A.sched_priority = valor_prioridade_A;
        res = pthread_attr_setschedparam(&thread_attr_A, &scheduling_value_A);
        pthread_attr_setschedpolicy(&thread_attr_A, SCHED_RR);
        pthread_attr_setdetachstate(&thread_attr_A, PTHREAD_CREATE_DETACHED);
        pthread_attr_setschedparam(&thread_attr_A, &scheduling_value_A);
        pthread_setschedparam(a_thread, SCHED_RR, &scheduling_value_A);
		usleep(500);

        scheduling_value_B.sched_priority = valor_prioridade_B;
        res = pthread_attr_setschedparam(&thread_attr_B, &scheduling_value_B);
        pthread_attr_setschedpolicy(&thread_attr_B, SCHED_RR);
        pthread_attr_setdetachstate(&thread_attr_B, PTHREAD_CREATE_DETACHED);
        pthread_attr_setschedparam(&thread_attr_B, &scheduling_value_B);
        pthread_setschedparam(b_thread, SCHED_RR, &scheduling_value_B);


        sleep(1);
	}
}

int main(int argc, char * argv[]){
    led_A.setValue(low);
    led_B.setValue(low);
    void *thread_result;


    res = pthread_attr_init(&thread_attr_A);
    if (res != 0) {
        perror("Falha na criação de Atributo");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_init(&thread_attr_B);
    if (res != 0) {
        perror("Falha na criação de Atributo");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_init(&thread_attr_update);
    if (res != 0) {
        perror("Falha na criação de Atributo");
        exit(EXIT_FAILURE);
    }
    




    res = pthread_attr_setschedpolicy(&thread_attr_A, SCHED_RR);
    if (res != 0) {
        perror("Falha na configuração de política de escalonamento");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setschedpolicy(&thread_attr_B, SCHED_RR);
    if (res != 0) {
        perror("Falha na configuração de política de escalonamento");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setschedpolicy(&thread_attr_update, SCHED_RR);
    if (res != 0) {
        perror("Falha na configuração de política de escalonamento");
        exit(EXIT_FAILURE);
    }



    res = pthread_attr_setdetachstate(&thread_attr_A, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("Falha na configuração de atributo detached");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setdetachstate(&thread_attr_B, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("Falha na configuração de atributo detached");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setdetachstate(&thread_attr_update, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("Falha na configuração de atributo detached");
        exit(EXIT_FAILURE);
    }




    res = pthread_create(&a_thread, &thread_attr_A, acenderLed_A, (void *) 0);
    if (res != 0) {
        perror("Falha na criação da thread");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&b_thread, &thread_attr_B, acenderLed_B, (void *) 0);
    if (res != 0) {
        perror("Falha na criação da thread");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&update_thread, &thread_attr_update, update, (void *) 0);
    if (res != 0) {
        perror("Falha na criação da thread");
        exit(EXIT_FAILURE);
    }


    scheduling_value_update.sched_priority = 99;
    res = pthread_attr_setschedparam(&thread_attr_update, &scheduling_value_update);
    pthread_attr_setschedpolicy(&thread_attr_update, SCHED_RR);
    pthread_attr_setdetachstate(&thread_attr_update, PTHREAD_CREATE_DETACHED);
    pthread_attr_setschedparam(&thread_attr_update, &scheduling_value_update);
    pthread_setschedparam(update_thread, SCHED_RR, &scheduling_value_update);

    
    while(true){};

    pthread_join(a_thread, &thread_result);
    pthread_join(b_thread, &thread_result);
    pthread_join(update_thread, &thread_result);

    exit(EXIT_FAILURE);


	return 0;
}
