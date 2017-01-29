#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>   // biblioteca pthread

using namespace std;
using namespace BlackLib;

//variaveis globais
#define pin_Intensidade 4
#define pin_Frequencia 6


BlackGPIO 	botao(GPIO_30, input);
BlackGPIO 	led(GPIO_60, output);
//biblioteca do Thiago
ADC 	intensidade(pin_Intensidade);		
ADC 	frequencia(pin_Frequencia);		
float valor_int = 50;
float valor_freq;

bool botaoPressionado = false;

void * detectBtPress (void *arg){
		while(true){
			while(!botao.isHigh()){
				botaoPressionado = !botaoPressionado;
				usleep(2000);
			}
		}
}

void * acenderLed (void *arg){
	while(true){
		if(botaoPressionado)
		{
			//acender led
    		led.setValue(high);
     		usleep(valor_int);
     		led.setValue(low);
     		usleep(valor_int);
			 //cout<<"eh pra ligar"<<endl;
			usleep(valor_freq);
		}
		else{
			//apagar led
			led.setValue(low);
			usleep(400);
			//cout<<"eh pra APAGAR"<<endl;

		}

	}
}

void * update (void *arg){
	while(true){
		valor_int = 1000 * intensidade.getPercentValue();
		valor_freq = 5000 *frequencia.getPercentValue();
		cout<<"intensidade: "<<valor_int<<"    ";
		cout<<"frequencia: "<<valor_freq<<endl;
		sleep(1);
	}
}

int main(){
	
	int res, res2, res3;
	
    pthread_t a_thread, b_thread, update_thread;



    res = pthread_create(&a_thread, NULL, detectBtPress, (void *) 0);
    res2 = pthread_create(&b_thread, NULL, acenderLed, (void *) 0);
    res3 = pthread_create(&update_thread, NULL, update, (void *) 0);

    if(res != 0){
    	cerr << "Erro na criação da thread 1";
    }
    if(res2 != 0){
    	cerr << "Erro na criação da thread 2";
    }
    if(res3 != 0){
    	cerr << "Erro na criação da thread 3";
    }
    res = pthread_join(a_thread,NULL);
    res2 = pthread_join(b_thread,NULL);
    res3 = pthread_join(b_thread,NULL);

	return 0;
}
