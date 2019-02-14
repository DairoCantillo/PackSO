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
//buffer=(char*)malloc(sizeof(char)*tam)

int main(int argc, char const *argv[])
{
    pid_t padre = getpid();
    pid_t childs[3];
    int fd1[2];
    int fd2[2];
    char buffer[1024];
    int i, k;
    pipe(fd1);
    pipe(fd2);

    /*
    c=fork();
    if(c==0){
        c=fork();
    }*/
    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if (childs[i] == 0)
        {
            break;
        }
    }

    if (padre != getpid())
    {
        if (i == 0)
        {
            close(fd1[0]);
            close(fd2[1]);
            close(fd2[0]);
            FILE *archivo1 = fopen("archivo1.txt", "r");
            if (!archivo1)
            {
                printf("Erro al abrir el archivo\n");
                exit(-1);
            }
            fseek(archivo1, 0, 2);
            int tam_file = ftell(archivo1);
            fseek(archivo1, 0, 0);

            char lectura[tam_file];
            write(fd1[1], &tam_file, sizeof(int));
            for (int i = 0; i < tam_file; i++)
            {
                lectura[i] = fgetc(archivo1);
                write(fd1[1], &lectura[i], sizeof(char));
            }
            fclose(archivo1);
            close(fd1[1]);
        }
        if (i == 1)
        {
            close(fd2[0]);
            close(fd1[1]);
            close(fd1[0]);
            FILE *archivo2 = fopen("archivo2.txt", "r");
            if (!archivo2)
            {
                printf("Erro al abrir el archivo\n");
                exit(-1);
            }
            fseek(archivo2, 0, 2);
            int tam_file = ftell(archivo2);
            fseek(archivo2, 0, 0);

            char lectura[tam_file];
            write(fd2[1], &tam_file, sizeof(int));
            for (int i = 0; i < tam_file; i++)
            {
                lectura[i] = fgetc(archivo2);
                write(fd2[1], &lectura[i], sizeof(char));
            }



            fclose(archivo2);
            close(fd2[1]);
        }
    }
    else
    {


        close(fd1[1]);
        close(fd2[1]);
        int tam1,tam2;
        read(fd1[0], &tam1, sizeof(int));
        read(fd2[0], &tam2, sizeof(int));
        char lectura1[tam1],lectura2[tam2];
        //lectura archivo1
        for (int k = 0; k < tam1; k++)
        {
            read(fd1[0], &lectura1[k], sizeof(char));
            //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
        }
        //lectura archivo2
        for (int k = 0; k < tam2; k++)
        {
            read(fd2[0], &lectura2[k], sizeof(char));
            //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
        }
        
        printf("\narchivo2\n");
        for (int k = 0; k < tam2; k++)
            printf("%c", lectura2[k]);
        printf("\n");
        printf("\narchivo1\n");
        for (int k = 0; k < tam1; k++)
            printf("%c", lectura1[k]);
        int pos1=0,pos2=0;

        printf("\nintercalado\n");
        for(int h=pos1;h<tam1;h++){
            printf("%c", lectura1[h]);
            if (lectura1[h]=='\n'){
                for(int k=pos2;k<tam2;k++){
                    printf("%c", lectura2[k]);
                    if (lectura2[k]=='\n'){
                        printf("\n");
                        pos2=k+1;
                        break;
                    }
                }

            }
        }
        
        printf("\n");
        close(fd1[0]);
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
                    for (i = 0; i < 2; i++)
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
