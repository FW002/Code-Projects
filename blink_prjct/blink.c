#include <wiringPi.h>

#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
int LEDS[]={LED1,LED2,LED3,LED4};
#define T 500

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




int main(void){
	
	setup();
	AllLed();
	
	return 0;
	
}
