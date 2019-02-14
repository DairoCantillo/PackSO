#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int **a, **b, **result, n = 0;

void *thread_routine(void *param){
    int *value = (int *)param;

    if(*value == 0){
        printf("soy el hilo 1\n");
        for(int i = 0; i < n/2; i++)
        {
            for(int j = 0; j < n/2; j++)
            {
                result[i][j]=0;
                    for(int r=0;r<n;r++){
                        result[i][j]=(result[i][j]+(a[i][r]*b[r][j]));
                    }
                    printf("%d\t",result[i][j]);
            }
            printf("\n");
        }
    }
    if(*value == 1){
        printf("soy el hilo 2\n");
        for(int i = 0; i < n/2; i++)
        {
            for(int j = n/2; j < n; j++)
            {
                result[i][j]=0;
                    for(int r=0;r<n;r++){
                        result[i][j]=(result[i][j]+(a[i][r]*b[r][j]));
                    }
                    printf("%d\t",result[i][j]);
            }
            printf("\n");
        }
    }
    if(*value == 2){
        printf("soy el hilo 3\n");
        for(int i = n/2; i < n; i++)
        {
            for(int j = 0; j < n/2; j++)
            {
                result[i][j]=0;
                    for(int r=0;r<n;r++){
                        result[i][j]=(result[i][j]+(a[i][r]*b[r][j]));
                    }
                    printf("%d\t",result[i][j]);
            }
            printf("\n");
        }
    }
    if(*value == 3){
        printf("soy el hilo 3\n");
        for(int i = n/2; i < n; i++)
        {
            for(int j = n/2; j < n; j++)
            {
                result[i][j]=0;
                    for(int r=0;r<n;r++){
                        result[i][j]=(result[i][j]+(a[i][r]*b[r][j]));
                    }
                    printf("%d\t",result[i][j]);
            }
            printf("\n");
        }
    }
    
    pthread_exit(0);
}
//contar las lineas del archivo
int nLineasArchivo(){
    int r = 0;
    FILE *f = fopen("archivo.txt","r");
    char c;
    if( f ){
        c = fgetc(f);
        while( c != EOF){
            if( c == '\n' ) r++;
            c = fgetc(f);
        }
    }
    fclose(f);
    return r+1;
}

int main()
{
    int nLineas = nLineasArchivo();
    int i, temp;
    n = nLineas/2;
    //printf("nlineas %d\n",n);
    FILE *f = fopen("archivo.txt", "r");
    if(!f) exit(-1);
   
    a = (int**)malloc(n*(sizeof(int *)));
    b = (int**)malloc(n*(sizeof(int *)));
    for(int i=0; i<n; i++){
        a[i] = (int*) malloc(n*sizeof(int));
        b[i] = (int*) malloc(n*sizeof(int));
    }
    result = (int**)malloc(n*(sizeof(int *)));
    for(int i=0; i<n; i++){
        result[i] = (int*) malloc(n*sizeof(int));
    }
    printf("matriz A:\n");
    for( i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            fscanf(f,"%d",&temp);
            a[i][j] = temp,printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    printf("matriz B:\n");
    for( i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            fscanf(f,"%d",&temp);
            b[i][j] = temp,printf("%d\t",b[i][j]);
        }
        printf("\n");
    }
    pthread_t th_id[4];
    int nthreads = 4;
    pthread_t threads[nthreads];

    int values[nthreads];
    for (int k=0; k<nthreads; k++){
        values[k] = k;
        pthread_create(&threads[k], NULL, thread_routine, (void*)&values[k]);
    }
    for (int k=0; k<nthreads; k++){
        pthread_join(threads[k], NULL);
    }        
    printf("matriz resultante es:\n");
    for( i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d\t",result[i][j]);
        }
        printf("\n");
    }
    return 0;
}


