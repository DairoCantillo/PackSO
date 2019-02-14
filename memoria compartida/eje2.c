#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/shm.h>
#include <sys/stat.h>

int main(){
	int h,n,*j,k,*turno, *i, pos,aux,con=0;
	// abrir el archivo
	FILE *f= fopen("archivo.txt","r");
	if(!f) exit(-1);
	fscanf(f,"%d",&k);
	fscanf(f,"%d",&n);
	pos= ftell(f);
	
	while(!feof(f)){
		fscanf(f,"%d",&aux);
		con++;
	
	}

	int shmid,shmid_2,shmid_3;
	shmid = shmget(IPC_PRIVATE, sizeof(int)*con, IPC_CREAT | S_IRUSR | S_IWUSR);
	shmid_2=shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	shmid_3=shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	turno=shmat(shmid, 0, 0);
	i=shmat(shmid_2, 0, 0);
	j=shmat(shmid_3, 0, 0);
	fseek(f,pos,0);
	for(h=0;h<con;h++) fscanf(f,"%d",&turno[h]);

	for(h=0;h<con;h++) if(!fork())break;
	i[0]=0,*j=0;
	while(j[0]<n){
		if(h==turno[*i]){
			printf("%d %d \n ", h,getpid());
			i[0]++;
			if(i[0]==con){
				i[0]=0,j[0]++;
				printf("\n");	
			}
		}else sleep(1);
	}
	
	if(h!= turno[con-1]){
		shmdt(turno),shmdt(i),shmdt(j);
	
	}else{
	shmctl(shmid,IPC_RMID,NULL);
	shmctl(shmid_2,IPC_RMID,NULL);
	shmctl(shmid_3,IPC_RMID,NULL);

	
	}	

//

return 0; 
}
