#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <wait.h>
#include <string.h>

int main(void) {
  int i,j, *turno, shmid, shmid_r, *repeticiones, max_repeticiones;
  char id = 'A', *secuencia ="ADCEFHGFECBA";

  printf("# de repeticiones: ");
  scanf("%d", &max_repeticiones);

  if(max_repeticiones < 0) return -1;

  shmid = shmget(IPC_PRIVATE, sizeof(int), 0600);
  turno = shmat(shmid, NULL, 0);
  shmid_r = shmget(IPC_PRIVATE, sizeof(int), 0600);
  repeticiones = shmat(shmid_r, NULL, 0);

  (*repeticiones) = 0;

  for(i = 0 ; i < 3; i++)
    if(!fork()){ //B, C, D
      id += (i + 1);
      if(i == 1){ //Proceso C
        if(!fork()){ //C, E
          id = 'E';
          if(!fork()){//E, F
            id = 'F';
            for(j = 0; j < 2; j++)
              if(!fork()){ //G y H
                id += (1 + j);
                break;
              }
          }
        }
      }
      break;
    }
  
  while((*repeticiones) < max_repeticiones){
    while((*turno < strlen(secuencia)))
      if(secuencia[(*turno)] == id){
        printf("%d %c %d\n", getpid(), id, (*turno));
        (*turno)++;
      }
    if((*turno) == strlen(secuencia) && id == secuencia[(*turno)-1]){
      (*repeticiones)++, (*turno) = 0;
      printf("\n");
    }
  }
  
  return 0;
}