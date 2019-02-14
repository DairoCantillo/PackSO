#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
int* cadena;
int x=0, numHilos=0, numCiclos=0, k=0, kCiclos=0;
pthread_t pidhilo[3];
void* funcion_maneja_hilo(void *param);
int main(){
    // Lectura de archivo
    FILE *fp = fopen("archivo.txt","r");
    if(!fp)exit(-1);
    rewind(fp);
    fscanf(fp, "%d", &numHilos);
    fscanf(fp, "%d", &numCiclos);
    for(k=0; !feof(fp); k++){
        cadena = (int*)realloc( cadena, (k+1)*(sizeof(int)) );
        fscanf(fp,"%d",&cadena[k]);
    }
    printf("%d",k);
    fclose(fp);
    // fin lectura archivo
    
    //Creacion de hilos
    for(int i=0; i<numHilos; i++) {
        pthread_create(&pidhilo[i], NULL, funcion_maneja_hilo, NULL);    
    }
    for(int i=0; i<numHilos; i++) pthread_join(pidhilo[i], NULL);
    
    return 0;
}
void* funcion_maneja_hilo(void *param){
    while(x < k && kCiclos<numCiclos){ 
        if( pidhilo[cadena[x]] == pthread_self() ){ 
            printf("Ciclo %d| %d.\tPid: %ul -> %c \n", kCiclos+1, x+1, pthread_self(), cadena[x]+65);
            if(x == k-1){
                printf("\n");
                x=0;
                kCiclos++;
            }else{
                x++;
            }
        }   
    }
}