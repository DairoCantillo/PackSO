#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

struct nodo{
    int val;
};

void* funcion_maneja_hilo(void *param);
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int i, T = 0,nMayus = 0, nMinus = 0, nDigitos = 0;
char *info;
int main()
{
    FILE *f = fopen("archivo.txt", "r");
    if(!f)exit(-1);
    fseek(f,0,2);
    T = ftell(f);
    fseek(f,0,0);
    info = (char *) malloc (T*sizeof(char*));
    fread(info,1,T,f);
    fclose(f);
    
    for( i = 0; i < T; i++)
    {
        printf("%c",info[i]);
    }
    
    pthread_t pidhilo[3];
    int n = 3;
    struct nodo *nodo;
    for( i = 0; i < n; i++)
    {
       nodo = (struct nodo *)malloc(sizeof(struct nodo));
       nodo->val = i;
       pthread_create(&pidhilo[i],NULL,funcion_maneja_hilo,(void*)nodo);
    }
    for( i = 0; i < n; i++)pthread_join(pidhilo[i], NULL);
    
    
    return 0;
}

void* funcion_maneja_hilo(void *param){
    
    if(((struct nodo*)param)->val == 0){
        for( int a = 0; a < strlen(info); a++)
        {
            if(isupper(info[a])) nMayus++;
        }
        printf("\nnumero de mayusculas: %d\n",nMayus);
    }else if (((struct nodo*)param)->val == 1) {
        for( int a = 0; a < strlen(info); a++)
        {
            if(islower(info[a]))nMinus++;
        }
         printf("numero de minusculas: %d\n",nMinus);

    }
    else if (((struct nodo*)param)->val == 2) {
        for( int a = 0; a < strlen(info); a++)
        {
            if(isdigit(info[a])) nDigitos++;
        }
    printf("numero de digitos: %d\n",nDigitos);
    }
    
    return NULL;
}
