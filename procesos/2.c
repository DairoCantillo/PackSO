#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{

    pid_t  childs[3],padre = getpid();
    int i,j;
    for(i=0; i<2;i++){
            childs[i]=fork();
            if(childs[i]!=0){
                break;
            }else{
                if(i==1){
                    for(j=0;j<3;j++){
                        childs[j]=fork();
                        if(childs[j]==0){
                            break;
                        }
                    }
                }
            }
    }

    if (padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        if (i == 3){
            for (i = 0; i < 3; i++){
                wait(NULL);
            }
        }
    }
    else{
        sleep(1);
    }
    return 0;
}