#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <ctype.h>

/*  El hilo pricipal debe leer un archivo, debe crear 3 subhilos
    uno debe contar las mayusculas, otro las minusculas y
    el tercer hilo debe contar los digitos  */

char *buffer;
int ncharacters, uppercases=0, lowercases=0, digits=0;

void *thread_routine(void *arg){
    int *value = (int*)arg;
    if (*value == 0)
        for (int a=0; a<ncharacters; a++)
            if (isupper(buffer[a])) uppercases++;

    if (*value == 1)
        for (int a=0; a<ncharacters; a++)
            if (islower(buffer[a])) lowercases++;

    if (*value == 2)
        for (int a=0; a<ncharacters; a++)
            if (isdigit(buffer[a])) digits++;

    return NULL;
}

int main(){
    system("clear");

    FILE *file = fopen("archivo.txt", "r");
    if (!file){
        printf("Erro al abrir el archivo\n");
        exit(-1);
    }
    fseek(file, 0, 2);
    ncharacters = ftell(file);
    fseek(file, 0, 0);

    buffer = (char*)malloc((ncharacters)*sizeof(char));

    for (int k=0; k<ncharacters; k++) buffer[k] = getc(file);
    fclose(file);

    int nthreads = 3;
    pthread_t threads[nthreads];

    int values[nthreads];
    for (int i=0; i<nthreads; i++){
        values[i] = i;
        pthread_create(&threads[i], NULL, thread_routine, (void*)&values[i]);
    }

    for (int i=0; i<nthreads; i++)
        pthread_join(threads[i], NULL);

    printf("Mayusculas %d\n", uppercases);
    printf("Minusculas %d\n", lowercases);
    printf("Digitos %d\n", digits);

    return 0;
}