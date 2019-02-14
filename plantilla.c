#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int c;
int main(int argc, char const *argv[]){

    pid_t child, padre = getpid();
    c = fork();
    if (c == 0)
    {
        c = fork();
    }
    

    if (padre == getpid())
    {
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(1);
    }

    
    return 0;
}