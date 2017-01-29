#include "BlackGPIO.h"
#include <iostream>
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "stdlib.h"
using namespace std;
using namespace BlackLib;

int main(){
	cout<<"Executando..."<<endl;
	int randomico;
	clock_t relogio_1, relogio_2;
	int tempo;
	BlackGPIO botao(GPIO_30, input, SecureMode);
	BlackGPIO led(GPIO_60,output, SecureMode);
	BlackGPIO a(GPIO_66,output, SecureMode);
	BlackGPIO b(GPIO_69,output, SecureMode);
	BlackGPIO c(GPIO_45,output, SecureMode);
	BlackGPIO d(GPIO_23,output, SecureMode);
	BlackGPIO e(GPIO_47,output, SecureMode);
	BlackGPIO f(GPIO_27,output, SecureMode);
	BlackGPIO g(GPIO_22,output, SecureMode);
	//seta os valores iniciais
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
	led.setValue(low);
	while(1){
		a.setValue(high);
		b.setValue(high);
		c.setValue(high);
		d.setValue(high);
		e.setValue(high);
		f.setValue(high);
		g.setValue(high);
		randomico = rand()%3399;
		//usleep(10);
		if(randomico==1189){
			cout<<"Atingiu Randomico!"<<endl;
			led.setValue(high);
			relogio_1 = clock();
			while(botao.isHigh()){
			}
			relogio_2 = clock();
			tempo = (relogio_2 - relogio_1)/CLOCKS_PER_SEC;
			cout<<"DELAY: "<<tempo<<endl;
			led.setValue(low);
		
		switch (tempo){
		case 0:
			a.setValue(low);
			b.setValue(low);
			c.setValue(low);
			d.setValue(low);
			e.setValue(low);
			f.setValue(low);
			break;
		case 1:
			b.setValue(low);
			c.setValue(low);
			break;
		case 2:
			a.setValue(low);
			b.setValue(low);
			g.setValue(low);
			e.setValue(low);
			d.setValue(low);
			break;
		case 3:
			a.setValue(low);
			b.setValue(low);
			g.setValue(low);
			c.setValue(low);
			d.setValue(low);
			break;
		case 4:
			a.setValue(low);
			b.setValue(low);
			f.setValue(low);
			g.setValue(low);
			c.setValue(low);
			break;
		case 5:
			a.setValue(low);
			f.setValue(low);
			g.setValue(low);
			c.setValue(low);
			d.setValue(low);
			break;
		case 6:
			a.setValue(low);
			f.setValue(low);
			e.setValue(low);
			d.setValue(low);
			c.setValue(low);
			g.setValue(low);
			break;
		case 7:
			a.setValue(low);
			b.setValue(low);
			c.setValue(low);
			break;
		case 8:
			a.setValue(low);
			b.setValue(low);
			c.setValue(low);
			d.setValue(low);
			e.setValue(low);
			f.setValue(low);
			g.setValue(low);
			break;
		case 9:
			a.setValue(low);
			b.setValue(low);
			c.setValue(low);
			d.setValue(low);
			g.setValue(low);
			f.setValue(low);
			break;
		}
		sleep(2);
		}
	}
	return 0;
}
		
