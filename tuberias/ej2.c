#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
/*
[0] = lectura
[1] = escritura
n = cantidad de bytes leidos

*/


int main(int argc, char const *argv[])
{
    pid_t padre = getpid();
    pid_t childs[3];
    int fd1[2];
    int fd2[2];
    char buffer[1024];
    int i,n;
    pipe(fd1);
    pipe(fd2);

    /*
    c=fork();
    if(c==0){
        c=fork();
    }*/
    for( i =0; i<3;i++){
        childs[i]=fork();
        if(childs[i]==0 ){
            break;
        }
    }

    if (padre != getpid()){
        if(i==0){
            close(fd1[0]);
            close(fd2[1]);
            close(fd2[0]);
            strcpy(buffer, "hola mundo pipes\n");
            write(fd1[1], buffer, strlen(buffer));
            close(fd1[1]);
        }
        if(i==1){
            close(fd1[1]);
            close(fd2[0]);
            n = read(fd1[0], buffer, sizeof(buffer));
            write(fd2[1], buffer, strlen(buffer));
            buffer[n] = '\0';
            close(fd1[0]);
            close(fd2[1]);
        }
        if(i==2){
            close(fd1[1]);
            close(fd1[0]);
            close(fd2[1]);
            n = read(fd2[0], buffer, sizeof(buffer));
            buffer[n] = '\0';
            printf("leido: %s\n ", buffer);
            close(fd2[0]);
        }


    }else{
        close(fd1[1]);
        close(fd1[0]);
        close(fd2[1]);
        close(fd2[0]);

    }

        /*
    strcpy(Buffer_out, "hola mundo pipes\n");
    write(fd[1],Buffer_out, strlen(Buffer_out));

    n = read(fd[0], Buffer_in, 1024);
    Buffer_in[n] = '\0';
    printf("leido: %s\n %d\n", Buffer_in, n);
    return 0;*/

        if (padre == getpid())
        {
            char b[500];
            sprintf(b, "pstree -lp %d", getpid());
            system(b);
            if (i == 3)
            {
                for (i = 0; i < 3; i++)
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
