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
int n;
int valor;
int TAM;
void *funcion_maneja_hilos(void *);

int main(int argc, char const *argv[])
{

    FILE *f = fopen("archivo.txt", "r");
    rewind(f);
    printf("ingrese el numero a buscar");

    scanf("%d", &valor);
    fscanf(f, "%d", &TAM);
    printf("tam del vector: %d\n", TAM);
    numeros = (int *)malloc(TAM * sizeof(int));
    for (int i = 0; i < TAM; i++)
    { //Si aún no se ha llegado al final del archivo
        fscanf(f, "%d", &numeros[i]);
    }
    fclose(f);
    printf("Ingrese cuantos hilos se ejecutaran\n");
    scanf("%d", &n);
    pthread_t *pidhilo = (pthread_t *)malloc((n) * sizeof(pthread_t));
    int v[n];
    total = (int *)calloc(n, sizeof(int));
    position = (int *)calloc(TAM, sizeof(int));
    posH = (int *)calloc(TAM, sizeof(int));
    for (int j = 0; j < TAM; j++)
    {
        printf("VEC: %d\n", numeros[j]);
    }
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
    int resultado = 0;
    for (int j = 0; j < n; j++)
    {
        resultado = resultado + total[j];
    }
    printf("Veces encontradas:%d \n", resultado);
    for (int g = 0; g < resultado; g++)
    {
        printf("Encontrado en la posicion: %d, por el hilo: %d\n", position[g], posH[g]);
    }
    return 0;
}

void *funcion_maneja_hilos(void *param)
{
    int delta = TAM / n;
    int *hilo = (int *)param;
    int x = (int)*hilo;
    int sum = 0;
    printf("hilo: %d\n", delta);
    int k;
    for (k = 0; k < delta; k++)
    {
        if (numeros[x * delta + k] == valor)
        {
            sum++;
            position[k] = x * delta + k;
            posH[k] = x;
        }
    }
    total[x] = sum;
    
    pthread_exit(0);
}
