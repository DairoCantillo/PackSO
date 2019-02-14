#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

int main(){
    system("clear");
    int fd[4][2], i;
    pid_t pids[3]; //Almacenar id de los procesos
    for(i = 0; i < 4; i++) if(pipe(fd[i]) != 0) abort();

    for(i = 0; i < 3; i++){
        pids[i] = fork();
        if(pids[i] == 0){ //Proceso hijo
            break;
        }
    }

    if(i == 3){ //Proceso padre
        int j, minus, puntos, numeros;
        for(j = 0; j < 4; j++){
            if(j != i) close(fd[j][1]); //Canal de escritura
            if(j != 0) close(fd[j][0]); //Canal de lectura
        }

        FILE *f = fopen("prueba.txt", "r");
        
        if(f == NULL) return -1;

        fseek(f, 0, SEEK_END);
        int TAM = (int)ftell(f);
        fseek(f, 0, SEEK_SET);

        char info[TAM], linea[TAM];
        strcpy(info, "");
        /*//Por concatenacion
        while(!feof(f)){
            fgets(linea, TAM, f);
            strcat(info, linea); //Acumulador de linea
        }*/

        //Por asignacion termino a termino
        for(j = 0; j < TAM; j++) info[j] = fgetc(f);
        info[strlen(info)] = '\0';

        write(fd[3][1], &TAM, sizeof(int));
        write(fd[3][1], info, TAM/* *sizeof(char)*/);

        read(fd[0][0], &minus, sizeof(int));
        read(fd[0][0], &puntos, sizeof(int));
        read(fd[0][0], &numeros, sizeof(int));

        printf("Proceso padre\nMinusculas: %d\nPuntos: %d\nNUmeros: %d\n",minus, puntos, numeros);
        

        //Evitar procesos huerfanos o zombies
        for(i = 0; i < 3; i++) wait(NULL);

        //Cerramos los canales utilizados
        close(fd[0][0]);
        close(fd[3][1]);
    }else if(i == 2){
        int j;
        for(j = 0; j < 4; j++){
            if(j != i) close(fd[j][1]); //Canal de escritura
            if(j != 3) close(fd[j][0]); //Canal de lectura
        }

        int T, minus = 0;
        read(fd[3][0], &T, sizeof(int));
        char info[T];
        read(fd[3][0], info, T);

        for(j = 0; j < T; j++) if(info[j] >= 'a' && info[j] <= 'z') minus++;
        
        write(fd[2][1], &T, sizeof(int));
        write(fd[2][1], info, T);
        write(fd[2][1], &minus, sizeof(int));
        close(fd[2][1]);
        close(fd[3][0]);

        
    }else if(i == 1){
        int j;
        for(j = 0; j< 4; j++){
            if(j != i) close(fd[j][1]); //Canal de escritura
            if(j != 2) close(fd[j][0]); //Canal de lectura
        }

        int T, minus, puntos = 0;
        read(fd[2][0], &T, sizeof(int));
        char info[T];
        read(fd[2][0], info, T);
        read(fd[2][0], &minus, sizeof(int));

        for(j = 0; j < T; j++) if(info[j] == '.') puntos++;

        write(fd[1][1], &T, sizeof(int));
        write(fd[1][1], info, T);
        write(fd[1][1], &minus, sizeof(int));
        write(fd[1][1], &puntos, sizeof(int));
        
        close(fd[2][0]);
        close(fd[1][1]);
    }else if(i == 0){
        int j;
        for(j = 0; j< 4; j++){
            if(j != i) close(fd[j][1]); //Canal de escritura
            if(j != 1) close(fd[j][0]); //Canal de lectura
        }

        int T, minus, puntos, numeros = 0;
        read(fd[1][0], &T, sizeof(int));
        char info[T];
        read(fd[1][0], info, T);
        read(fd[1][0], &minus, sizeof(int));
        read(fd[1][0], &puntos, sizeof(int));

        for(j = 0; j < T; j++) if(info[j] >= '0' && info[j] <= '9') numeros++;

        write(fd[0][1], &minus,sizeof(int));
        write(fd[0][1], &puntos,sizeof(int));
        write(fd[0][1], &numeros,sizeof(int));

        close(fd[0][1]);
        close(fd[1][0]);
    }
    return 0;
}