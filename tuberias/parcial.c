#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>


void create_index(void **m, int rows, int cols, size_t sizeElement)
{
    int i;
    size_t sizeRow = cols * sizeElement;
    m[0] = m + rows;

    for (i = 1; i < rows; i++)
    {
        m[i] = (m[i - 1] + sizeRow);
    }
}
unsigned int sizeof_dm(int rows, int cols, size_t sizeElement)
{
    size_t size = rows * sizeof(void *); // indexSize
    size += (cols * rows * sizeElement); // datasize
    return size;
}

int main()
{
    int n;
    printf("digite n:\n");
    scanf("%d", &n);
    pid_t padre = getpid();
    int **a = NULL, **b = NULL, **result = NULL, shmid1, shmid2, shmid3, i;
    size_t sizeMatrix = sizeof_dm(n, n, sizeof(int));

    shmid1 = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
    shmid2 = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
    shmid3 = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
    a = shmat(shmid1, NULL, 0);
    b = shmat(shmid2, NULL, 0);
    result = shmat(shmid3, NULL, 0);
    create_index((void *)a, n, n, sizeof(int));
    create_index((void *)b, n, n, sizeof(int));
    create_index((void *)result, n, n, sizeof(int));
    float m = round((n + 1) / 2);
    printf("%.f\n", m);
    for (i = 0; i < m; i++)
        if (!(fork()))
            break;
    if (padre == getpid())
    {
        int cont = 0;
        for (int f = 0; f < n; f++)
        {
            for (int c = 0; c < n; c++)
            {
                a[f][c] = cont;
                b[f][c] = cont;
                cont++;
            }
        }
        printf("matriz A\n");
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                printf(" %d ", a[r][c]);
            }
            printf("\n");
        }
        printf("matriz B\n");
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                printf(" %d ", b[r][c]);
            }
            printf("\n");
        }
        printf("\n");
        sleep(2);
        printf("PADRE matriz resultante c\n");
        for (int r = 0; r < n; r++)
        {
            for (int a = 0; a < n; a++)
            {
                printf(" %d ", result[r][a]);
            }
            printf("\n");
        }
        printf("\n");
        shmdt(a);
        shmdt(b);
        shmdt(result);
        shmctl(shmid1, IPC_RMID, 0);
        shmctl(shmid2, IPC_RMID, 0);
        shmctl(shmid3, IPC_RMID, 0);
    }
    else
    {
        sleep(1);
        int irows = n, icols = n;
        for (int c = i; c < n - i; c++)
        {
            for (int k = 0; k < n; k++)
            {
                result[i][c] = (result[i][c] + (a[i][k] * b[k][c]));
                if (i != icols - i - 1)
                {
                    result[(irows - 1) - i][c] = (result[(irows - 1) - i][c] + (a[(irows - 1) - i][k] * b[k][c]));
                }
            }
        }
        for (int f = i + 1; f < (n - 1) - i; f++)
        {
            for (int k = 0; k < n; k++)
            {
                result[f][i] = (result[f][i] + (a[f][k] * b[k][i]));
                result[f][(icols - 1) - i] = (result[f][(icols - 1) - i] + (a[f][k] * b[k][(icols - 1) - i]));
            }

            //           suma += matrix[f][i];
            // suma += matrix[f][(icols-1)-i];
        }

        shmdt(a);
        shmdt(b);
        shmdt(result);
    }
    if (padre == getpid())
    {
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        for (i = 0; i < m; i++)
            wait(NULL);
    }
    else
    {
        sleep(1);
    }

    return 0;
}
