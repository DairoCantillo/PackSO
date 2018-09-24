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
    int fd[2],n;
    char Buffer_out[1024];
    char Buffer_in[1024];
    pipe(fd);
strcpy(Buffer_out,"hola mundo pipes\n");
//write(fd[1],Buffer_out, strlen(Buffer_out));

n = read(fd[0],Buffer_in,1024);
Buffer_in[n] = '\0';
printf("leido: %s\n %d\n", Buffer_in,n);
    return 0;
}
