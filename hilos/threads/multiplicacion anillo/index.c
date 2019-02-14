#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int **a, **b, **result, n = 0;

void *thread_routine(void *param){
    int *value = (int *)param;
    int v = (int)*value;
    //*value 
    printf("soy el hilo %d\n",v);
        int irows = n,icols = n;
        for (int c=v; c<n-v; c++){
            
            for(int k=0;k<n;k++){
                result[v][c]=(result[v][c]+(a[v][k]*b[k][c]));
                if (v != icols-v-1) {
                    result[(irows-1)-v][c]=(result[(irows-1)-v][c]+(a[(irows-1)-v][k]*b[k][c]));
                }
                
            }
            //if (v != icols-v-1) printf("%d\t",result[(irows-1)-v][c]);
            //printf("%d\n",result[v][c]);
        }
        for (int f=v+1; f<(n-1)-v; f++)
        {
            for(int k=0;k<n;k++){
            result[f][v]=(result[f][v]+(a[f][k]*b[k][v]));
            result[f][(icols-1)-v]=(result[f][(icols-1)-v]+(a[f][k]*b[k][(icols-1)-v]));
            }
            //printf("%d\t",result[f][(icols-1)-v]);
            //printf("%d\n",result[f][v]);
        }
        
        for( int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
            {
                printf("[%d]\t",result[r][c]);
            }
            printf("\n");
        }
        

    pthread_exit(0);
}

int main()
{
    
    int i, temp;
    //printf("nlineas %d\n",n);
    FILE *f = fopen("archivo.txt", "r");
    if(!f) exit(-1);
    fscanf(f,"%d",&n);
    printf("%d",n);
    a = (int**)malloc(n*(sizeof(int *)));
    b = (int**)malloc(n*(sizeof(int *)));
    result = (int**)malloc(n*(sizeof(int *)));

    for(int i=0; i<n; i++){
        a[i] = (int*) malloc(n*sizeof(int));
        b[i] = (int*) malloc(n*sizeof(int));
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
            result[i][j] = 0;
        }
        printf("\n");
    }
    
    int nthreads = (n+1)/2;
    //printf("nhilos es%d\n",nthreads);
    pthread_t th_id[nthreads];
    pthread_t threads[nthreads];

    int values[nthreads];
    for (int k=0; k<nthreads; k++){
        values[k] = k;
        pthread_create(&threads[k], NULL, thread_routine, (void*)&values[k]);
        sleep(2);
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