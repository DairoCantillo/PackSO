#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[])
{

    pid_t child, padre = getpid();
    for(int i=0;i<5;i++){
        child=fork();
        if(child==0){
            if(i==2){
                for(int j=0;j<5;j++){
                    child = fork();
                    if(!child){
                        if(j==0 || j==4){
                            fork();
                            break;
                        }
                        break;
                    }
                }
            }
            break;
        }
    }

    if (padre == getpid())
    {
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
    }
    else
    {
        sleep(1);
    }

    return 0;
}