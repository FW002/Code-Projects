#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
#define TA1 17
#define TA2 27
#define TA3 22
int direction = 0;
int LEDS[]={LED1,LED2,LED3,LED4};
#define T 500


void* RunLed(void* dir)
{
	
	while(1){		
			
		if(*dir == 1){		
		for(int i = 3; i < 4;i--){	
						
			digitalWrite(LEDS[i],HIGH);
			delay(T);
			digitalWrite(LEDS[i],LOW);
			delay(T);
			
				}	
	}
	else{
			for(int i = 0; i < 4;i++){		
				digitalWrite(LEDS[i],HIGH);
				delay(T);
				digitalWrite(LEDS[i],LOW);
				delay(T);
			}
		}
}
}

void setup(){
	wiringPiSetupGpio();
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);	
	pinMode(TA2,INPUT);
}


//Mitlerer Knopf GPIO27= Richtung ändern
//GPIO17 = Schneller
//GPIO22 = langsamer 		MIT THREADS


int main(){
	
	setup();
	
	pthread_t t1; 
	pthread_create(&t1,NULL,RunLed,&direction);
	
	while(1){
		if(digitalRead(TA2)==1){
				direction = 1;	
			}		
			for(int i = 0; i < 4;i++){		
				digitalWrite(LEDS[i],HIGH);
				delay(T);
				digitalWrite(LEDS[i],LOW);
				delay(T);
			}
		
		}
	
	
	
	
	
	printf("\n");
	//RunLed();

	
	return 0;
	
}
