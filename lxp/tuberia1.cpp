#include <stdio.h> //IO
#include <stdlib.h> //Funciones del sistema
#include <unistd.h> //Fork()
#include <string.h>
#include <sys/types.h> //Macros de los tipos pid_t, size_t (typedef)

/*
    Tuberias:
        pipe
        write
        read
*/

int main(){
    int fd[2];
    pid_t hijo;
    
    if(pipe(fd) != 0){
        perror("La tuberia no se creo!");
        exit(-1);
    }

    hijo = fork();
    
    if(hijo == 0){ //Proceso hijo
        close(fd[1]);
        int k;
        read(fd[0], &k, sizeof(int));
        char mensaje2[k];
        read(fd[0],  mensaje2, k);
        printf("Mensaje desde el proceso hijo: %s\n", mensaje2);
        close(fd[0]);
    }else{
        close(fd[0]);
        char mensaje[100]; //Tamaño de un char: 1 byte
        printf("Mensaje: ");
        scanf("%s", mensaje);
        
        int n = (int)strlen(mensaje);
        write(fd[1], &n, sizeof(int));
        write(fd[1], mensaje, n);
        close(fd[1]);
    }
    
    return 0;
}
