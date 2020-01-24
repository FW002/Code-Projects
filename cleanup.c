#include <wiringPi.h>
#include <signal.h>

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
int LEDS[]={LED1,LED2,LED3,LED4};
int LEDCOUNT = sizeof(LEDS)/sizeof(int);
#define T 500


void getout(int sig);	//Aufruf bei SIGTERM und SIGINT

void setup(void){
	wiringPiSetupGpio();
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
}

void AllLed(){
	
	for(int c = 0; c < 4; c++){
		digitalWrite(LEDS[c],HIGH);
		delay(T);
		digitalWrite(LEDS[c],LOW);
		delay(T);
	}
	
	for(;;){
	int i = sizeof(LEDS);
	for(i = 0; i < 4; i++){
		digitalWrite(LEDS[i],HIGH);
	}
	delay(T);
	for(i = 0; i < 4; i++){
		digitalWrite(LEDS[i],LOW);
	}
	delay(T);
	}
	
	
}

void cleanup(){
	for(int i = 0; i < LEDCOUNT; i++){
		digitalWrite(LEDS[i],LOW);
	}
	
	
}

void getout(int sig){
	if(sig == 0){
		return EXIT_SUCCESS;
	}else{
		return;
	}
	
}

int main(void){
	
	setup();
	AllLed();
	signal(SIGINT,getout);
	cleanup();
	
	return 0;
	
}
