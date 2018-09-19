#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[])
{

    pid_t childs[3], padre = getpid();
    int i,j;

    for (i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if (!childs[i])
        {
            break;
        }

    }

    if (i == 1)
    {
        pid_t childsFromC2[4];

        for (j= 0; j < 3; j++){
            childsFromC2[j]=fork();
            if(!childsFromC2[j]){
                break;
            }
        }
        if(j==1){
            childsFromC2[4]=fork();
        }
    }

    if (padre == getpid())
    {
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        if(i==3 || j==4){
            for(i=0;i<7;i++){
                wait(NULL);
            }
        }
    }
    else
    {
        sleep(1);
    }

    return 0;
}