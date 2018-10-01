#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main()
{
    //system("clear");
    pid_t padre = getpid();
    int i, j,k, n;
    char buffer[1024];

    printf("Ingrese el numero de n procesos:");
    scanf("%d", &n);

    pid_t childs[n];
    int fd[n][2];

    for (j=0; j<n; j++) if( pipe(fd[j]) ) exit(-1);
    for (i=0; i<n; i++) if(!(childs[i] = fork())) break;

    if (getpid() != padre){
        for (j=0; j<n; j++){
            if (i != j) close(fd[j][0]);
            if ((i+1) != j) close(fd[j][1]);
        }
        int tam;
        read(fd[i][0], &tam, sizeof(int));
        char lectura[tam];
        //printf("tam = %d\n",tam);
        
        for( k = 0; k < tam; k++)
        {
            read(fd[i][0], &lectura[k], sizeof(char));
            //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
        }
        printf("\nleido\n");
        for (k = 0; k < tam; k++)printf("%c",lectura[k]);
        lectura[strlen(lectura)] = '\0';
        printf("\n");

        write(fd[i+1][1], &tam, sizeof(int));
        write(fd[i+1][1], lectura, tam);
        close(fd[i][0]);
        close(fd[i+1][1]);
    }else{
        close(fd[0][0]);
        for (j=1; j<n; j++){
            close(fd[j][0]);
            close(fd[j][1]);
        }
        FILE *archivo = fopen("caracteres.txt", "r");
        if (!archivo){
            printf("Erro al abrir el archivo\n");
            exit(-1);
        }
        fseek(archivo, 0, 2);
        int tam_file = ftell(archivo);
        fseek(archivo, 0, 0);

        //tam_file -= 1;
        char lectura[tam_file];
        write(fd[0][1], &tam_file, sizeof(int));
        for (int i=0; i< tam_file; i++){
            lectura[i] = fgetc(archivo);
            write(fd[0][1], &lectura[i], sizeof(char));
        }
        fclose(archivo);     
        close(fd[0][1]);
    }

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        for( i = 0; i < n; i++) wait(NULL);
    }else{
        sleep(1);
    }

    return (0);
}