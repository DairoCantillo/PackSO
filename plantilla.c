#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[]){

    pid_t child, padre = getpid();
    fork();
    fork();
    fork();

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(1);
    }

    
    return 0;
}