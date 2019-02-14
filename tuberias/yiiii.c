#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void inicializar(void **vectorMatriz, int filas, int columnnas, size_t sizeElent){
    int i;
    size_t sizeRow = columnnas * sizeElent;
    vectorMatriz[0] = vectorMatriz + filas;
    for( i = 1; i < filas; i++)
    {
        vectorMatriz[i] = (vectorMatriz[i-1] + sizeRow);
    }
}
unsigned int calcularTam(int filas, int columnnas, size_t sizeElement){
    size_t size = filas * sizeof(void *);
    size += (columnnas * filas *sizeElement);
    return size;
}

int main(int argc, char const *argv[])
{
    int n ;
    printf("Numero de filas y columnas(matriz cuadrada):\n");
    scanf("%d",&n);
    pid_t padre = getpid();
    int **a=NULL,**b=NULL,**resultado=NULL,i,contador;
    int matriz1;
    int matriz2;
    int matriz3;
    size_t tamMatriz = calcularTam(n,n,sizeof(int));
    
    matriz1 = shmget(IPC_PRIVATE, tamMatriz, IPC_CREAT|0600);
    matriz2 = shmget(IPC_PRIVATE, tamMatriz, IPC_CREAT|0600);
    matriz3 = shmget(IPC_PRIVATE, tamMatriz, IPC_CREAT|0600);
    a =  shmat(matriz1,NULL,0);
    b =  shmat(matriz2,NULL,0);
    resultado =  shmat(matriz3,NULL,0);
    inicializar((void*)a, n, n, sizeof(int));
    inicializar((void*)b, n, n, sizeof(int));
    inicializar((void*)resultado, n, n, sizeof(int));
    float nVueltas = round((n + 1) / 2);
    for( i = 0; i < nVueltas; i++) 
    if(!(fork())){
        break;
    }
    if(padre != getpid()){
        sleep(1);
        int ifilas = n, icolumnnas = n;
        for (int c = i; c < n - i; c++){
            for (int k = 0; k < n; k++)
            {
                resultado[i][c] = (resultado[i][c] + (a[i][k] * b[k][c]));
                if (i != icolumnnas - i - 1)
                {
                    resultado[(ifilas - 1) - i][c] = (resultado[(ifilas - 1) - i][c] + (a[(ifilas - 1) - i][k] * b[k][c]));
                }
                printf("processo:[%d]  Pos[%d][%d]\n", getpid(), k, c);
            }
        }
        for (int fila = i + 1; fila < (n - 1) - i; fila++)
        {
            for (int k = 0; k < n; k++)
            {
                resultado[fila][i] = ((a[fila][k] * b[k][i]));
                resultado[fila][(icolumnnas - 1) - i] = (resultado[fila][(icolumnnas - 1) - i] + (a[fila][k] * b[k][(icolumnnas - 1) - i]));
                printf("processo:[%d]  Pos[%d][%d]\n", getpid(), fila, k);
            }
        }

        shmdt(a);
        shmdt(b);
        shmdt(resultado);
    }else{
        for (int f = 0; f < n; f++)
        {
            for (int c = 0; c < n; c++)
            {
                a[f][c] = contador;
                b[f][c] = contador;
                contador++;
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
        printf("PADRE matriz procesada\n");
        for (int r = 0; r < n; r++)
        {
            for (int a = 0; a < n; a++)
            {
                printf(" %d ", resultado[r][a]);
            }
            printf("\n");
        }
        printf("\n");
        shmdt(a);
        shmdt(b);
        shmdt(resultado);
        shmctl(matriz1, IPC_RMID, 0);
        shmctl(matriz2, IPC_RMID, 0);
        shmctl(matriz3, IPC_RMID, 0);
    }
    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        for( i = 0; i < nVueltas; i++) wait(NULL);
    }else{
        sleep(1);  
    }
    

    return 0;
}
