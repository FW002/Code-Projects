#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


#define LED1 18
#define LED2 23
#define LED3 24
#define LED4 25
int LEDS[]={LED1,LED2,LED3,LED4};

void getout(int sig);

int freq = 1000; //Standard Frequency

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

void* blink(void* arg){
	while(1){
	  int i = sizeof(LEDS);
	   for(i = 0; i < 4; i++){
		digitalWrite(LEDS[i],HIGH);
	   }
	delay(freq);
		for(i = 0; i < 4; i++){
		digitalWrite(LEDS[i],LOW);
				}
	delay(freq);
   }
}



void* readFile(void* args){
   
   FILE* fp;
   int input;
   fp = fopen ("/home/pi/Desktop/data", "r");
   
   
   fscanf(fp, "%d", &input);
   if(fp == NULL){		//Check if File is OK
	   printf("ERROR");
	   
   }do{
	fscanf(fp, "%d", &input);	//Get data from file
	
	   if(feof(fp)){	//IF End Of File is reached, stop it
		   break;
	   }
   }while(1);
 
   printf("Read Frequency |%d|\n", input );	//Print current freqency

   fclose(fp);	//Close the file to avoid struggle
   
	freq = input;	//set the freq value to the input value
	//rewind(fp);
}


int main(){
	
	setup();
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1,NULL,blink,NULL);
	pthread_create(&t2,NULL,readFile,NULL);
	signal(SIGINT,getout);
	
  while(1){
	  //this does something 
	  delay(1000);
	  printf("%d\n",freq);	//Just to check: print the freq value
  }
	
}

