#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
/*
[0] = lectura
[1] = escritura
n = cantidad de bytes leidos

*/
typedef struct Nodo{
int fd[2];
}Tuberia;



int main(int argc, char const *argv[]){
    pid_t padre = getpid();
    int i;
    char buffer[1024];
    int n, c;
    printf("ingrese el numero de procesos:");
    scanf("%d", &n);
    Tuberia tuberia[n];
    pipe(tuberia[0].fd);
    pipe(tuberia[1].fd);
    pipe(tuberia[2].fd);
                
    for (int a = 0; a < n; a++)if (pipe(tuberia[a].fd))exit(-1);

    pid_t childs[n];

    for(i=0;i<n;i++){
        childs[i]=fork();
        if(childs[i]==0)break;

    }

    if (padre == getpid()){
        close(tuberia[0].fd[0]);
        for (int x = 0; x < (n - 1); x++){
                close(tuberia[x].fd[1]);
                close(tuberia[x].fd[0]);
        }
        strcpy(buffer, "tierro mk");
        write(tuberia[0].fd[1], buffer, strlen(buffer));
        close(tuberia[0].fd[1]);
                
    }
    else{
        
        if (i == (n - 1)){
            //printf("leido: %s\n ", buffer);
            close(tuberia[i].fd[1]);
            for (int x = 0; x < n; x++){
                if (x != i || x != (i + 1)){
                    close(tuberia[x].fd[1]);
                    close(tuberia[x].fd[0]);
                }
            }
            close(tuberia[(i)].fd[1]);
            close(tuberia[(i + 1)].fd[0]);
            c = read(tuberia[i].fd[0], buffer, sizeof(buffer));
            buffer[c] = '\0';
            printf("leido: %s\n ", buffer);
            close(tuberia[i].fd[0]);
        }
        else{
            for (int x = 0; x < n; x++){
                if (x != i){
                    close(tuberia[x].fd[1]);
                    close(tuberia[x].fd[0]);
                }
            }
            c = read(tuberia[i].fd[0], buffer, sizeof(buffer));
            write(tuberia[i+1].fd[1], buffer, strlen(buffer));
            buffer[c] = '\0';
            close(tuberia[i].fd[0]);
            close(tuberia[i + 1].fd[1]);
        }
    }

    if (padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        if (i == n){
            for (int a = 0; a < n; a++)
            {
                wait(NULL);
            }
        }
    }
        else{
        sleep(1);
    }
    return 0;
}
