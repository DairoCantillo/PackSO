#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
    pid_t childs, padre = getpid();
    int i, j;

    for (i = 0; i < 3; i++){
        childs = fork();
        if (childs==0){
            if(i==1){
                for (j = 0; j < 3; j++){
                    childs = fork();
                    if(childs==0){
                        if(j==1){
                            childs=fork();
                        }break;
                    }
                    
                }
            }break;
        }
    }
    if (padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        if (i == 3){
            for (i = 0; i < 7; i++){
                wait(NULL);
            }
        }
    }
    else{
        sleep(1);
    }

    return 0;
}