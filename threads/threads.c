#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// gibt 20 Zeichen aus, nach jeder Ausgabe wird zufällig lang gewartet
void* showC(void* c){
	for(int i = 0; i < 20; i++){
		printf("%c",*((char *)c));
		fflush(stdout);	//stdout ist gebuffert
		int w = rand() % 100;
		for(long j = 0; j < 1000000*w;j++){
			; // ; = NOP = No Operation
		}
	}	
}

int main(){
	srand(time(0));
	char x = 'V';
	char y = '_';
	//ohne threads
	printf("Ohne Threads");
	printf("\n");
	showC(&x);
	showC(&y);
	printf("\n");
	//Mit Threads
	printf("Mit Threads");
	printf("\n");
	pthread_t t1,t2; 	//Strukturen zur Verwaltung von Thread 1 und 2
	pthread_create(&t1,NULL,showC,&x);
	pthread_create(&t2,NULL,showC,&y);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("\n");
	
	return 0;
}
