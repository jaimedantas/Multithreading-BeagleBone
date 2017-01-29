#include "BlackGPIO.h"
#include <iostream>
#include <vector>
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "stdlib.h"
#include <pthread.h>   // biblioteca pthread

using namespace std;
using namespace BlackLib;




int main(){
	BlackGPIO botao(GPIO_30, input, SecureMode);
	BlackGPIO led(GPIO_60,output, SecureMode);
	cout<<"Executan gggg SSS  do..."<<endl;

	led.setValue(low);
	while(1){
		led.setValue(high);
	}
	return 0;
}