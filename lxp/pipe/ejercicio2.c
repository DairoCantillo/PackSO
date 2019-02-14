#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

int main(){
    system("clear");
    int fd[3][2], i, T, j;
    char mensaje[11];

    for(i = 0; i < 3; i++) if(pipe(fd[i]) != 0 ) abort();

    for(i = 0; i < 3; i++) if(fork()) break; //Si es un padre que salga del ciclo
    
    if(i == 3){
        for(j= 0; j < 3; j++){
            close(fd[j][0]); //Cerramos todos los canales de lectura
            if(j != 2) close(fd[j][1]); //Cerramos todos los canales de escritura 
        }

        //printf("Digite un mensaje: ");
        strcpy(mensaje, "Hola mundo");
        
        T = strlen(mensaje); //Longitud de la cadena (Bytes)
        mensaje[T] = '\0';
        write(fd[2][1], &T, sizeof(int));
        write(fd[2][1], mensaje, T);
        close(fd[2][1]);
    }else if(i == 2 || i == 1){ //Proceso 4 o 5
        for(j= 0; j < 3; j++){
            if(j != i) close(fd[j][0]); //Cerramos todos los canales de lectura
            if(j != (i-1)) close(fd[j][1]); //Cerramos todos los canales de escritura 
        }

        read(fd[i][0], &T, sizeof(int));
        char mensaje2[T]; //Una cadena de tamaño exacto de la palabra leida
        read(fd[i][0], mensaje2, T);

        close(fd[i][0]);

        printf("soy el proceso %d con id: %d mensaje %s\n", i, (int)getpid(), mensaje2 );
        write(fd[i-1][1], &T, sizeof(int));
        write(fd[i-1][1], mensaje2, T);
        close(fd[i-1][1]);
    }else{
        for(j = 0; j < 3; j++){
            close(fd[j][1]);
            if(j != i) close(fd[j][0]);
        }

        read(fd[i][0], &T, sizeof(int));
        char mensaje3[T];
        read(fd[i][0], mensaje3, T);
        printf("soy el proceso %d con id: %d mensaje %s\n", i, (int)getpid(), mensaje3);

    }
    
    
    return 0;
}