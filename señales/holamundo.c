
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
void manejador(int s){
    printf("signal No. [%d] procesos [%d]\n", s,getpid());
}

int main(){
    int c;
    signal(SIGUSR1, manejador);
    if(!(c=fork())){
        pause();
    }else{
        kill(c, SIGUSR1);
        wait(NULL);
    }
    return 0;
}