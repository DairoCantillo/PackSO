#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 10000
//-lpthread

struct timespec tic, toc;
double Elapsed;

double *p;
double *a, *b;
int i, n;
void *funcion_maneja_hilos(void *);

int main(int argc, char const *argv[])
{
    a = (double *)calloc(MAX_SIZE, sizeof(double));
    b = (double *)calloc(MAX_SIZE, sizeof(double));
    srand(time(NULL));
    for (i = 0; i < MAX_SIZE; i++)
    {
        a[i] = rand() % 50 + 1;
        b[i] = rand() % 50 + 1;
    }

    printf("Ingrese cuantos hilos se ejecutaran\n");
    scanf("%d", &n);
    p = (double *)calloc(n, sizeof(double));
    pthread_t *pidhilo = (pthread_t *)malloc((n) * sizeof(pthread_t));
    int v[n];
    clock_gettime(CLOCK_REALTIME, &tic);
    for (int j = 0; j < n; j++)
    {
        v[j] = j;
        pthread_create(&pidhilo[j], NULL, funcion_maneja_hilos, (void *)&v[j]);
    }
    printf("Hilo principal (idthread -> [%ld])\n", (long int)pthread_self());

    for (int j = 0; j < n; j++)
    {
        pthread_join(pidhilo[j], NULL);
    }
    clock_gettime(CLOCK_REALTIME, &toc);
    Elapsed = (toc.tv_sec - tic.tv_sec) + ((toc.tv_nsec - tic.tv_nsec) / (double)1E9);
    printf("%.61f\n", Elapsed);
    double acum = 0;

    for (i = 0; i < n; i++)
    {
        //printf("vector parcial: %d\n", p[i]);
        acum = acum + p[i];
    }
    printf("MSE: %f", acum / MAX_SIZE);
    return 0;
}

void *funcion_maneja_hilos(void *param)
{
    int delta = MAX_SIZE / n;
    int *hilo = (int *)param;
    double valor;
    int x = (int)*hilo;
    for (int k = 0; k < delta; k++)
    {
        valor = (a[x * delta + k] + b[x * delta + k]) * (a[x * delta + k] + b[x * delta + k]);
    }
    p[x] = valor;
    pthread_exit(0);
}