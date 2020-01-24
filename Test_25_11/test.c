#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
int LEDS[]={LED1,LED2,LED3,LED4};
int LEDCOUNT = sizeof(LEDS)/sizeof(int);
#define T 50 // periodendauer 50 Hz
//wenn 30 eingabe: dann 30% von T = on time

void getout(int sig);
	int onTimeV = 40;
	int standardV = 40;
    int newV;


void cleanup(){
	for(int i = 0; i < 4; i++){
		digitalWrite(LEDS[i],LOW);
	}
}

void getout(int sig){
	if(sig != SIGINT){
		return;
	}else{
		cleanup();
		exit(EXIT_SUCCESS);
		//return;
	}
	
}

void setup(void){
	wiringPiSetupGpio();
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
}

void* input(void* arg){
	while(1){
		printf("Enter Value: ");
		scanf("%d", &onTimeV);
		if(onTimeV > 100 || onTimeV < 0){
			standardV = standardV;
			printf("Between 0%%...100%% ");
		}else{
		standardV = onTimeV;
	}
		newV = (onTimeV * 0.001/0.020) * 10;	
		//newV * 0.001;
		printf("[%d]>%d %%\n",standardV,onTimeV);
	}
}

int main(){
	
	setup();
	signal(SIGINT, getout);
	pthread_t t1;
	pthread_create(&t1,NULL,input,NULL);

	
	while(1){
		
		while(newV != 0){
			int i = sizeof(LEDS);
			for(i = 0; i < 4; i++){
				digitalWrite(LEDS[i],HIGH);
			}
			delay(newV);
				for(i = 0; i < 4; i++){
					digitalWrite(LEDS[i],LOW);
				}
			delay(newV);
		
		}
	}
	
}
