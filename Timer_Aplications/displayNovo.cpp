#include "BlackGPIO.h"
#include <iostream>
#include <vector>
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "stdlib.h"
using namespace std;
using namespace BlackLib;


void split_into_digits( vector<unsigned int> &v, unsigned int value )
{
   constexpr unsigned int base = 10;
   unsigned int digit = value % base;
   
   if ( value /= base ) split_into_digits( v, value );
   
   v.push_back( digit );
}


int main(){
	cout<<"Executando..."<<endl;
	BlackGPIO botao(GPIO_30, input, SecureMode);
	BlackGPIO led(GPIO_60,output, SecureMode);
	BlackGPIO a(GPIO_31,output, SecureMode);
	BlackGPIO b(GPIO_48,output, SecureMode);
	BlackGPIO c(GPIO_5,output, SecureMode);
	BlackGPIO d(GPIO_3,output, SecureMode);
	BlackGPIO e(GPIO_49,output, SecureMode);
	BlackGPIO f(GPIO_61,output, SecureMode);
	BlackGPIO g(GPIO_20,output, SecureMode);
	BlackGPIO D1(GPIO_7,output, SecureMode);
	BlackGPIO D2(GPIO_51,output, SecureMode);
	BlackGPIO D3(GPIO_4,output, SecureMode);
	BlackGPIO D4(GPIO_2,output, SecureMode);
	BlackGPIO ponto(GPIO_15,output, SecureMode);
	int randomico, primeiro, segundo, terceiro, quarto;
	long int cont;
	clock_t relogio_1, relogio_2;
	int tempo;


	//seta os valores iniciais
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
	ponto.setValue(high);
	D1.setValue(low);
	D2.setValue(low);
	D3.setValue(low);
	D4.setValue(low);
	led.setValue(low);
	while(1){
	vector<unsigned int> v;
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
	ponto.setValue(high);
	D1.setValue(low);
	D2.setValue(low);
	D3.setValue(low);
	D4.setValue(low);
		randomico = rand()%3000;
		//usleep(10);
		if(randomico==1189){
			cout<<"Atingiu Randomico!"<<endl;
			led.setValue(high);
			relogio_1 = clock();
			while(botao.isHigh()){
			}
			relogio_2 = clock();
			tempo = (relogio_2 - relogio_1)/double(CLOCKS_PER_SEC)*1000;
			led.setValue(low);
			cout<<"DELAY: "<<tempo<<endl;
			split_into_digits( v, tempo );
			cout<<"tempo dividido: "<<endl;
			if(v.size()==3){
			primeiro = 0;
			segundo = v.at(0);
			terceiro = v.at(1);
			quarto = v.at(2);
			}
			else if(v.size()==2){
			primeiro = 0;
			segundo = 0;
			terceiro = v.at(0);
			quarto = v.at(1);		

			}
			else if (v.size()==4){
			primeiro = v.at(0);
			segundo = v.at(1);
			terceiro = v.at(2);
			quarto = v.at(3);	
			}
			else {
			primeiro = 0;
			segundo = 0;
			terceiro = 0;
			quarto = 0;
			}
			cont = 0;
		while(cont<50){

	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
		ponto.setValue(low);

			D1.setValue(high);
			D2.setValue(low);
			D3.setValue(low);
			D4.setValue(low);

switch (primeiro){
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
			break;}			
			usleep(1000);
	//seta os valores iniciais
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
			ponto.setValue(high);


			D1.setValue(low);
			D2.setValue(high);
			D3.setValue(low);
			D4.setValue(low);

			switch (segundo){
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
			break;	}		
			usleep(1000);
	//seta os valores iniciais
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
			ponto.setValue(high);

			D1.setValue(low);
			D2.setValue(low);
			D3.setValue(high);
			D4.setValue(low);
			switch (terceiro){
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
			break;	}		
			usleep(1000);
	//seta os valores iniciais
	a.setValue(high);
	b.setValue(high);
	c.setValue(high);
	d.setValue(high);
	e.setValue(high);
	f.setValue(high);
	g.setValue(high);
			ponto.setValue(high);

			D1.setValue(low);
			D2.setValue(low);
			D3.setValue(low);
			D4.setValue(high);

			switch (quarto){
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
			break;}
			usleep(1000);
			cont++;
		}
		//sleep(3);
		}
	}
	return 0;
}
		
