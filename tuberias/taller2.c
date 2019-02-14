#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main()
{
    //system("clear");
    pid_t padre = getpid();
    int i, j, k, n;
    char buffer[1024];

    printf("Ingrese el numero de n procesos:");
    scanf("%d", &n);

    pid_t childs[n];
    int fd[n][2];
    int fd1[n][2];

    for (j = 0; j < n; j++)
        if (pipe(fd[j]))
            exit(-1);
    for (j = 0; j < n; j++)
        if (pipe(fd1[j]))
            exit(-1);
    for (i = 0; i < n; i++)
        if (!(childs[i] = fork()))
            break;

    if (getpid() == padre)
    {
        close(fd[0][0]);
        for (j = 1; j < n; j++)
        {
            close(fd[j][0]);
            close(fd[j][1]);
        }
        char lectura[1024];
        printf("\nIngrese el mensaje:\n");
        //scanf("%[^\n]", &lectura);
        scanf("%s", &lectura);
        int tam_file = strlen(lectura);

        //tam_file -= 1;
        write(fd[0][1], &tam_file, sizeof(int));

        for (int i = 0; i < tam_file; i++)
        {
            write(fd[0][1], &lectura[i], sizeof(char));
        }
        close(fd[0][1]);
    }
    else
    {
        if (i == (n - 1))
        {
            for (j = 0; j < n; j++)
            {
                if (i != j)
                {
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
            for (j = 0; j < n; j++)
            {
                if (i != j)
                {
                    close(fd1[j][0]);
                    close(fd1[j][1]);
                }
            }
            int tam;
            read(fd[i][0], &tam, sizeof(int));
            char lectura[tam];
            //printf("tam = %d\n",tam);

            for (k = 0; k < tam; k++)
            {
                read(fd[i][0], &lectura[k], sizeof(char));
                //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
            }

            printf("\nleido\n");
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");
            write(fd1[i][1], &tam, sizeof(int));
            write(fd1[i][1], lectura, tam);

            close(fd[i][0]);
            close(fd[i][1]);
            close(fd1[i][0]);
            close(fd1[i][1]);
            
        }
        else
        {
            for (j = 0; j < n; j++)
            {
                if (i != j)
                    close(fd[j][0]);
                if ((i + 1) != j)
                    close(fd[j][1]);
            }
            int tam;
            read(fd[i][0], &tam, sizeof(int));
            char lectura[tam];
            //printf("tam = %d\n",tam);

            for (k = 0; k < tam; k++)
            {
                read(fd[i][0], &lectura[k], sizeof(char));
                //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
            }
            /*printf("\nleido\n");
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");
            */
            write(fd[i + 1][1], &tam, sizeof(int));
            write(fd[i + 1][1], lectura, tam);
            lectura[strlen(lectura)] = '\0';
            printf("\nleido\n");
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");
            close(fd[i][0]);
            close(fd[i + 1][1]);
        }
        if (i=(n-1))
        {
            for (j = 0; j < n; j++)
            {
                if (i != j)
                {
                    close(fd1[j][0]);
                    close(fd1[j][1]);
                }
            }
            int tam;
            read(fd1[i][0], &tam, sizeof(int));
            char lectura[tam];
            //printf("tam = %d\n",tam);

            for (k = 0; k < tam; k++)
            {
                read(fd1[i][0], &lectura[k], sizeof(char));
                //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
            }
            printf("\nleido\n");
            printf("Process %d:"), getpid();
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");

            close(fd1[i][0]);
            close(fd1[i][1]);
        }
        else
        {
            for (j = 0; j < n; j++)
            {
                if (i != j)
                    close(fd1[j][0]);
                if ((i + 1) != j)
                    close(fd1[j][1]);
            }
            int tam;
            read(fd1[i][0], &tam, sizeof(int));
            char lectura[tam];
            //printf("tam = %d\n",tam);

            for (k = 0; k < tam; k++)
            {
                read(fd1[i][0], &lectura[k], sizeof(char));
                //printf("Process %d: leido: %c\n", getpid(), lectura[k]);
            }
            /*printf("\nleido\n");
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");
            */
            write(fd1[i + 1][1], &tam, sizeof(int));
            write(fd1[i + 1][1], lectura, tam);
            lectura[strlen(lectura)] = '\0';
            printf("\nleido\n");
            for (k = 0; k < tam; k++)
                printf("%c", lectura[k]);
            printf("\n");
            close(fd1[i][0]);
            close(fd1[i + 1][1]);
        }
    }

    if (padre == getpid())
    {
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        for (i = 0; i < n; i++)
            wait(NULL);
    }
    else
    {
        sleep(1);
    }

    return (0);
}