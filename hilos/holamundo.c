#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* funcion_manage_hilo(void*);

int main(){
    pthread_t pidhilo;
    pthread_create(&pidhilo,NULL,funtion_manage_hilo,NULL);
    printf("hilo principal (idthread -> [%ld)])\n",(long int) pthread_self());
    pthread_join(pidhilo,NULL);
    return 0;

}

void* funtion_manage_hilo(void *param){

    printf("hilo (idthread -> [%ld])\n",(long int) pthread_self());
    pthread_exit(0);
}