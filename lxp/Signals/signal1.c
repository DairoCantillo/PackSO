#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

void manejador(){}

int main(){
	system("clear");
	signal(SIGUSR1, manejador); //Creacion de la conexion señal-funcion
	int hijo;
	hijo = fork(); //Jerarquia

	if(hijo){ //Padre
		sleep(1);
		printf("Padre: %d\n", getpid());
		kill(hijo, SIGUSR1);
		pause();
		printf("Padre: %d\n", getpid());
		kill(hijo, SIGUSR1);
	}else{ // Hijo
		pause();
		printf("Hijo: %d\n", getpid());
		kill(getppid(), SIGUSR1);
		pause();
		printf("Hijo: %d\n", getpid());
	}
	
	return 0;
}
