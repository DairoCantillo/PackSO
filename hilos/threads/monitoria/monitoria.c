#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void *f(void *param){
    int x = 0;
    while(x < 5) {
        printf("%d",x);
        x++;
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t hilo1, hilo2;

    char *n1 = "hilo 1", *n2 = "hilo2";
    
    phtreadcreate(&hilo1,NULL, f, (void *)n1);
    phtreadcreate(&hilo2,NULL, f, (void *)n2);
    return 0;
}
