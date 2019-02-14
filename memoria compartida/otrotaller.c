#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i,n,n2;
    int myTurno = 0;
    int *turno;
    int shm_id;
    int shm_size = 1;
    pid_t padre = getpid();
    pid_t *childs;
    printf("ingrese en numero de hijos:");
    scanf("%d",&n);
    printf("ingrese en numero de iteraciones:");
    scanf("%d", &n2);
    childs = (pid_t*) malloc(sizeof(pid_t)*n);
    //key,tamaño,lo crea, lectura(a nivel de usuario), (a nivel se usuario)escritura
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    turno = shmat(shm_id, NULL, 0);
    *turno=0;

    for(i=0;i<n;i++){
        childs[i]=fork();
        if(childs[i]==0){
            myTurno = n-i;
            break;
        }
    }

    for(int j=0;j<n2;j++){
        while(myTurno !=*turno);
        if(*turno==0)
            printf("\nturno[%d] PADRE[%d]\n", *turno, getpid());
        else
            printf("\nturno[%d]  Hijo[%d][%d]\n", *turno, i, getpid());
        if(n==*turno){
            *turno=0;
            printf("\n");
        }
        else ++*turno;
    }



}