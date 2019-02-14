#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

//void imprimirArchivo2( char archivo);
int main(int argc, char const *argv[])
{
    __pid_t padre = getpid(), childs[2];
     int fd1[2],fd2[2];
    int i,j,k;
    

    pipe(fd1);
    pipe(fd2);

    for(i=0;i<2;i++){
        childs[i]=fork();
        if(childs[i]==0){break;}
    }

    if(padre==getpid()){
        printf("soy el padre \n");
        close(fd1[1]);
        close(fd2[1]);
         int n,n2,c_linea2=0,c_linea1=0;
        read(fd2[0],&c_linea2,sizeof(int));
        printf("PAPA cantidad lineas archivo 2 %d \n",c_linea2);
        //read(fd1[0], &c_linea1, sizeof(int));
        //printf("PAPA cantidad lineas archivo 1 %d \n", c_linea2);
        int n_caracteres2=0;
        int n_caracteres1=0;
        char linea2[1000];
        char linea1[1000];
        for(i=0;i<c_linea2;i++){
            read(fd1[0],&n_caracteres1,sizeof(int));
            linea1[n_caracteres1];
            read(fd1[0],linea1,n_caracteres1);
            printf(" %d -> %s \n", i, linea1);
            read(fd2[0],&n_caracteres2,sizeof(int));
            linea2[n_caracteres2];
            read(fd2[0],linea2,n_caracteres2);
            printf(" %d -> %s \n",i,linea2);
        }
        
        //printf("soy el archivo2 en el padre \n %s \n",Archivo2);
        
        close(fd2[0]);
        close(fd1[0]);


    }
    else{
        if(i==0){
            int c_linea1 = 0, n_caracteres1 = 0;
            close(fd1[0]);
            close(fd2[0]);
            close(fd2[1]);
            FILE * fich1 = fopen("archivo1.txt", "r");
                if(fich1){
                    fseek(fich1,0,2);
                    int n = ftell(fich1);
                    char linea1[n], Archivo1[n];
                    strcpy(Archivo1, "");
                    fseek(fich1,0,0);
                    while(!feof(fich1)){
                        c_linea1++;
                    }
                    fseek(fich1, 0, 0);
                    write(fd1[1],&c_linea1,sizeof(int));
                    while(!feof(fich1)){
                        fgets(linea1,n,fich1);
                        strcat(Archivo1,linea1);
                        n_caracteres1=strlen(linea1);
                        write(fd1[1], &n_caracteres1, sizeof(int));
                        write(fd1[1], linea1, n_caracteres1);
                                        }
                  
                   // printf("soy el proceso %d con id: %d archivo 1 \n %s\n", i, (int)getpid(), Archivo1);
                   
                    close(fd1[1]);
                    }
                    fclose(fich1);
                      
    }
    if(i==1){
         int c_linea2=0,n_caracteres2=0;
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        //close(fd2[1])
        FILE * fich2 = fopen("archivo2.txt", "r");
                if(fich2){
                    fseek(fich2,0,2);
                    int n2 = ftell(fich2);
                    char linea2[n2], Archivo2[n2];
                    strcpy(Archivo2, "");
                    fseek(fich2,0,0);
                    while(!feof(fich2)){
                        fgets(linea2,n2,fich2);
                        c_linea2 ++;
                    }
                    write(fd2[1],&c_linea2,sizeof(int));
                    //printf("cantidad lineas archivo 2 %d \n",c_linea2);
                    fseek(fich2,0,0);
                    while(!feof(fich2)){
                        fgets(linea2,n2,fich2);
                        strcat(Archivo2,linea2);
                        n_caracteres2=strlen(linea2);
                        write(fd2[1], &n_caracteres2, sizeof(int));
                        write(fd2[1], linea2, n_caracteres2);
                        }
                    fclose(fich2);
                 // printf("soy el proceso %d con id: %d archivo 2 \n %s\n", i, (int)getpid(), Archivo2);
                    
                   
                    
                    close(fd2[1]);
                    }
                    

    }
    
    }


        // IMPRESION::
    if(padre==getpid()){
        sleep(2);
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(4);
    }
    // IMPRESION::
    return 0;
}