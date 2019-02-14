#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    void *ptr;
    int shm_id;
    int shm_size = 1024;
//key,tamaño,lo crea, lectura(a nivel de usuario), (a nivel se usuario)escritura
    shm_id = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);
    ptr = shmat(shm_id, 0, 0);

    if (!fork()){
        sleep(2);
        printf("[%d] %s\n", getpid(), (char *)ptr);
        sprintf(ptr, "bye!");
        printf("[%d] %s\n", getpid(), (char *)ptr);
        //shmdt(ptr);
    }
    else{
        sprintf(ptr, "Holaa Mundo");
        printf("[%d]%s\n", getpid(), (char *)ptr);
        shmdt(ptr);
        shmctl(shm_id, IPC_RMID, 0);
        wait(NULL);
    }
    return 0;
}