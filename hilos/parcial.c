#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int *numeros;
int *total;
int *position;
int *posH;
int nHilos;
int valor;
int TAM;
int nIntervalo;

void *funcion_maneja_hilos(void *);
int n, **matriz;
int main(int argc, char const *argv[])
{
    int i, temp;
    FILE *f = fopen("archivo.txt", "r");
    if (!f)
        exit(-1);
    fscanf(f, "%d", &n);
    matriz = (int **)malloc(n * (sizeof(int *)));

    for (int i = 0; i < n; i++)
    {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }

    printf("matriz:\n");
    for (i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(f, "%d", &temp);
            matriz[i][j] = temp, printf("%d\t", matriz[i][j]);
        }
        printf("\n");
        
    }
    fclose(f);
    printf("Ingrese cuantos hilos se ejecutaran\n");
    scanf("%d", &nHilos);
    pthread_t *pidhilo = (pthread_t *)malloc((nHilos) * sizeof(pthread_t));
    int v[nHilos];
    /*printf("Ingrese cuantas iteraciones desea\n");
    scanf("%d", &nIntervalo);*/
    for (int j = 0; j < nHilos; j++)
    {
        v[j] = j;
        pthread_create(&pidhilo[j], NULL, funcion_maneja_hilos, (void *)&v[j]);
    }
    //printf("Hilo principal (idthread -> [%ld])\n", (long int)pthread_self());

    for (int j = 0; j < nHilos; j++)
    {
        pthread_join(pidhilo[j], NULL);
    }

    printf("\n\nmatriz:\n");
    for (int h = 0; h < n; h++)
    {
        for (int p = 0; p < n; p++)
        {
            printf("%d\t", matriz[h][p]);
        }
        printf("\n");
    }

    return 0;
}

void *funcion_maneja_hilos(void *param)
{
    int delta = n / nHilos;
    int *hilo = (int *)param;
    int x = (int)*hilo;
    
    for (int f = 1; f < (delta); f++)
    {
        for(int c=1;c<(n-1);c++){
            if(f!=0 || f!=(n-1)){
                    matriz[delta * x + f][c] = ((
                    matriz[(delta * x + f)-1][c] +
                    matriz[(delta * x + f)][c] +
                    matriz[delta * x + f][c+1] +
                    matriz[delta * x + f][c-1])/4);
            }

                    //printf("%d\t", matriz[delta * x + f][c]);
        }

    }

    //total[x] = sum;
    pthread_exit(0);
}
