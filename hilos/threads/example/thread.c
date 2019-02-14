#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* funcion_majena_hilo(void *);

int main()
{
    pthread_t pidhilo;
    pthread_create(&pidhilo,NULL,funcion_majena_hilo,NULL);
    printf("hilo principal (idthread -> [%ld])\n",(long int) pthread_self());
    pthread_join(pidhilo,NULL);
    return 0;
}

void* funcion_majena_hilo(void *param){
    printf("hilo (idthread -> [%ld])\n",(long int) pthread_self());
    pthread_exit(0);
}
