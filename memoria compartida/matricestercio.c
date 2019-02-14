#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int sizeof_dm(int rows, int cols, size_t sizeElement){
    size_t size = rows * sizeof(void *);
    size += (cols * rows * sizeElement);
    return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement){
    int i;
    size_t sizeRow = cols * sizeElement;
    m[0] = m + rows;
    for (i = 1; i < rows; i++){
        m[i] = (m[i - 1] + sizeRow);
    }
}



int main(int argc, char const *argv[]){
    int Rows = 15;
    int Cols = 15;
    double **matrix = NULL;
    double shmId, shmIdR,*resultado;
    int shm_size = 1024;
    size_t sizeMatrix = sizeof_dm(Rows, Cols, sizeof(double));
    shmId = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
    shmIdR = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);
    matrix = shmat(shmId, NULL, 0);
    resultado = shmat(shmIdR,0, 0);
    create_index((void *)matrix, Rows, Cols, sizeof(double));
    int x, y;
    for (x = 0; x < Rows; x++) {
        for (y = 0; y < Cols; y++){
            matrix[x][y] = y + x;
        }
        printf("\n");
    }

    pid_t childs[3];
    int i;
    for(i=0;i<3;i++){
        childs[i]=fork();
        if(childs[i]==0){
            break;
        }

    }

    return 0;
}
