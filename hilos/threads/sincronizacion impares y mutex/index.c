#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

pthread_mutex_t mutexPares = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexImpares = PTHREAD_MUTEX_INITIALIZER;
int pares=0,impares=0, **matriz, fil=6, col=6;
void* DiagonalSuperior(void* param);
void* DiagonalInferior(void* param);
void* DiagonalPrincipal(void* param);
int main(){
    /* Incializacion de la matriz */
    matriz = (int**)malloc(fil*(sizeof(int *)));
    for(int i=0; i<fil; i++){
        matriz[i] = (int*) malloc(col*sizeof(int));
    }
    int cont=1;
    for(int i=0; i<fil; i++)
        for(int j=0; j<col; j++) matriz[i][j] = cont++;
    
    // Fin de la inicializacion de la matriz
    
    pthread_t th_id[3];
    //Creacion de hilos
    pthread_create(&th_id[0], NULL,DiagonalSuperior,NULL);
    pthread_create(&th_id[1], NULL,DiagonalInferior,NULL);
    pthread_create(&th_id[2], NULL,DiagonalPrincipal,NULL);
    // Fin Creacion de Hilos


    for(int i=0; i<3; i++)
        pthread_join(th_id[i],NULL);
    // Resultados
    printf("Pares: %d | Impares %d\n",pares,impares);
    return 0;
}
void* DiagonalSuperior(void* param){
    printf("Matriz diagonalSuperior: %ul\n",pthread_self());
    for (int i = 0; i < fil; i++){ 
        for (int j = 0; j <col; j++){ 
            if( i < j){
                if(matriz[i][j]%2 == 0){
                    pthread_mutex_lock(&mutexPares);
                    pares++;
                    pthread_mutex_unlock(&mutexPares);
                }else{
                    pthread_mutex_lock(&mutexImpares);
                    impares++;
                    pthread_mutex_unlock(&mutexImpares);
                }
            }
        }
    }
}
void* DiagonalInferior(void* param){
    printf("Matriz diagonalInferior: %ul\n",pthread_self());
    for (int i = 0; i < fil; i++){ 
        for (int j = 0; j <col; j++){ 
            if( i > j){
                if(matriz[i][j]%2 == 0){
                    pthread_mutex_lock(&mutexPares);
                    pares++;
                    pthread_mutex_unlock(&mutexPares);
                }else{
                    pthread_mutex_lock(&mutexImpares);
                    impares++;
                    pthread_mutex_unlock(&mutexImpares);
                }
            }
        }
    }
}
void* DiagonalPrincipal(void* param){
    printf("Matriz diagonalPrincipal: %ul\n",pthread_self());
    for (int i = 0; i < fil; i++){
        if(matriz[i][i]%2 == 0){
            pthread_mutex_lock(&mutexPares);
            pares++;
            pthread_mutex_unlock(&mutexPares);
        }else{
            pthread_mutex_lock(&mutexImpares);
            impares++;
            pthread_mutex_unlock(&mutexImpares);
        }
    }
}