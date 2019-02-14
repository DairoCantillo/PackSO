#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/shm.h>
#include <sys/stat.h>

int main(){
	int n,i,j=0,k,*turno;
	printf("Ingrese la cantidad de proceso: ");
	scanf("%d",&k);	
	printf("ingrese la cantidad de veces a repetir: ");
	scanf("%d",&n);

	int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	turno=shmat(shmid, 0, 0);
	turno[0]=k;
	
	for(i=0;i<k;i++) if(!fork()) break;

	while(j<n)
		if(i==turno[0]){
			printf("%d (%d) \n",i+1,getpid());
			j++, turno[0]--;
			if(turno[0]==-1){
				turno[0]=k;
				printf("\n");
			}
		}else (1);
	
	shmdt(turno);
	if(i==0) shmctl(shmid,IPC_RMID,NULL);
return 0;
}
