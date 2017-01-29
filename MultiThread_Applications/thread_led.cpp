#include "BlackGPIO/BlackGPIO.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>   // biblioteca pthread

using namespace std;
using namespace BlackLib;



BlackGPIO botao(GPIO_30, input);
BlackGPIO led(GPIO_60,output);

bool botaoPressionado = false;

void * detectBtPress (void *arg){
		while(true){
			while(!botao.isHigh()){
				botaoPressionado = !botaoPressionado;
				cout<<"<>"<<endl;
				sleep(2);
			}
		}
}

void * acenderLed (void *arg){
	while(true){
		if(botaoPressionado)
		{
			//acender led
			led.setValue(high);
		}
		else{
			//apagar led
			led.setValue(low);
		}
		usleep(400);
	}
}

int main(){
	
	int res, res2;
	
    pthread_t a_thread, b_thread;

    res = pthread_create(&a_thread, NULL, detectBtPress, (void *) 0);
    res2 = pthread_create(&b_thread, NULL, acenderLed, (void *) 0);

    if(res != 0){
    	cerr << "Erro na criação da thread 1";
    }
    if(res2 != 0){
    	cerr << "Erro na criação da thread 2";
    }
    res = pthread_join(a_thread,NULL);
    res2 = pthread_join(b_thread,NULL);

	return 0;
}
