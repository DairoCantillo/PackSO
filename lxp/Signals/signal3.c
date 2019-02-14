#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

void manejador(){}

int main(){
    system("clear");
    signal(SIGUSR1, manejador);
    pid_t pids[4], padre = getpid();
    int i, j = -1;

    for(i = 3; i >= 0;i--)
        if(!(pids[i] = fork())){
            if(i != 3) pids[i] = fork();
            else
                for(j = 0; j < 2; j++) if(!(pids[j] = fork())) break;
            break;
        }

    if(i == -1){
        sleep(2);
        char* a = (char*)calloc(50, 1);
        sprintf(a, "pstree -lp %d", getpid());
        system(a);
    }else sleep(3);

   
    if(getppid() == padre || getpid() == padre){
        if(i != 3){
            if(i == 1) sleep(3);
            else pause();
            printf("Proceso: %d\n", getpid());

            if(i == -1) goto goAhead;
            kill(pids[i], SIGUSR1);
            pause();
            printf("Proceso: %d\n", getpid());

            goAhead:
            if(i != 0) kill(pids[i+1], SIGUSR1);
        }else{
            pause();
            printf("Proceso: %d\n", getpid());
            kill(pids[1], SIGUSR1);
            pause();
            printf("Proceso: %d\n", getpid());
            kill(getppid(), SIGUSR1);
        }
    }else{
        pause();
        printf("Proceso: %d\n", getpid());
        if(j != 1) kill(getppid(), SIGUSR1);
        else kill(pids[0], SIGUSR1);
    }

    return 0;
}