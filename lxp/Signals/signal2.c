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
    int n, i;
    printf("Cantidad de procesos: ");
    scanf("%d", &n);

    if(n < 0) abort();

    pid_t *pids = (pid_t*)calloc(n, sizeof(pid_t));

    for(i = (n-1); i >= 0; i--) if(!(pids[i] = fork())) break;

    if(i == -1){
        sleep(3);
        printf("Padre: %d\n", getpid());
        kill(pids[0], SIGUSR1);
        pause();
        printf("Padre: %d\n", getpid());
    }else{
        pause();
        printf("Hijo: %d\n", getpid());
        
        if(i != (n-1)) kill(pids[i+1], SIGUSR1);
        else kill(getppid(), SIGUSR1);
    }

    if(i == -1){
        char* a = (char*)calloc(50, 1);
        sprintf(a, "pstree -lp %d", getpid());
        system(a);
    }else sleep(3);

    return 0;
}