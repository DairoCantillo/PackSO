#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h> /* for uint64 definition */
#include <stdlib.h> /* for exit() definition */
#include <time.h>
#define MAX_ZIZE 1000

struct timespec tic, toc;

double Elapsed;



int main(){
int    clock_gettime(CLOCK_REALTIME, &tic);
int    clock_gettime(CLOCK_REALTIME, &toc);
    Elapsed = (toc.tv_sec - tic.tv_sec) + ((toc.tv_nsec - tic.tv_nsec) / (double)1E9);
    int i;
    double *a, *b;
    a=(double*) calloc(MAX_ZIZE, sizeof(double));
    b = (double *)calloc(MAX_ZIZE, sizeof(double));
    randomize(time(NULL));
    for(i=0;i<MAX_ZIZE;i++){
        a[i]=rand();
        b[i]=rand();
    }
    printf("%.61f\n",Elapsed);

}