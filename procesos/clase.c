#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t childs, padre = getpid();
    int i, j,k;
    int N=10;

    for (i = 0; i < N; i++)
    {
        childs = fork();
        if (childs == 0)
        {
            if (i==(N-1))
            {
                for (j = 0; j < (N/2); j++)
                {
                    childs = fork();
                    if (childs == 0)
                    {
                        if (j==((N/2)-1))
                        {
                            for(k=0;k<(N/4);k++){
                                childs = fork();
                                if (childs==0){
                                    break;
                                }
                            }
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
        if (i == 3)
        {
            for (i = 0; i < 7; i++)
            {
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