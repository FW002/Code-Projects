#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//#include <stdbool.h>
typedef int bool;
#define true 1
#define false 0

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
#define TA1 22
#define TA2 27
#define TA3 17
int LEDS[]={LED1,LED2,LED3,LED4};
//#define T 500
int T = 500;

void setup(){
	wiringPiSetupGpio();
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(TA2,INPUT);	
	pinMode(TA1,INPUT);
}

void* led2(void* arg){
	delay(T);
	for(int i = 0; i< 5;i++){
		digitalWrite(LED3,HIGH);
		delay(T);
		digitalWrite(LED3,LOW);
		delay(T);
	}
	
}

bool state = 0;

void* Button(void* arg){
	while(1){
	//printf("Thread is live\n");
	if(!digitalRead(TA1)){
		state = 1;
	}else if(state == 1 && !digitalRead(TA1)){
		state = 0;
	}else{
		state = 0;
	}
}
}

int main(){
	
	
	setup();
	
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1,NULL,led2,NULL);
	pthread_create(&t2,NULL,Button,NULL);
	
	for(int i = 0; i< 8;i++){
		digitalWrite(LED2,HIGH);
		delay(T);
		digitalWrite(LED2,LOW);
		delay(T);
	}
	
	while(1){
		if(state == 1){
			for(int i = 4; i > -1; i--){
				digitalWrite(LEDS[i],HIGH);
				delay(T);
				digitalWrite(LEDS[i],LOW);
				delay(T);
			}
		}
		//printf("State: %d",state);

	}
	
}
