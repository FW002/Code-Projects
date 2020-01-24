#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//#include <stdbool.h>

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
#define TA1 22
#define TA2 27
#define TA3 17
int LEDS[]={LED1,LED2,LED3,LED4};
#define T 500

typedef int bool;
#define true 1
#define false 0

void setup(){
	wiringPiSetupGpio();
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(TA1,INPUT);	
	pinMode(TA2,INPUT);
	pinMode(TA3,INPUT);
}

bool state = 0;
int P = 50;

void* Backwards(void* arg){	
		while(1){
			if(!digitalRead(TA2)){
				state = 1;
			}
		}
}

void* Forward(void* arg){	
	while(1){
			if(!digitalRead(TA2) && state == 1){
				state = 0;
			}
		}
}



void* IamSpeed(void* arg){
	//int T = (int) arg;
	while(1){
		if(!digitalRead(TA1))
		{
			P = P * 0.5;	// Hälfte langsamer
			
		}else if(!digitalRead(TA3)){
			P = P / 0.5; // hälfte schneller
			
		}
		delay(T);
		printf("speed: %d\n",P);
	}
}

int main(){
	
	setup();
	
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	
	pthread_create(&t1,NULL,Backwards,NULL);
	pthread_create(&t2,NULL,Forward,NULL);
	pthread_create(&t3,NULL,IamSpeed,NULL);
	
while(1){
	if(state == 0){
		for(int i = 0; i < 4;i++){
			digitalWrite(LEDS[i],HIGH);
			delay(T);
			digitalWrite(LEDS[i],LOW);
				delay(T);
			}	
		}else if(state == 1){
			for(int i = 4; i > -1;i--){
					digitalWrite(LEDS[i],HIGH);
					delay(T);
					digitalWrite(LEDS[i],LOW);
					delay(T);
				}
			}	
		}
	
}
