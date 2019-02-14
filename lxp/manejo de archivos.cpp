#include <stdio.h> //IO
#include <stdlib.h> //Funciones del sistema

/*
    MANEJO DE ARCHIVOS
    fopen(nombre_archivo, modo_apertura
    
    fclose(FILE);
    feof(FILE); //Fin del archivo
    
    Modo de apertura:
    r: leer
    w: escribir
    a: escribir al final
    
    r+, w+
    
    Posicionamiento del cursor
    fseek(FILE, int, int)
    0:inicio
    1: Posicion actual
    2: final del ARCHIVOS
    
    ftell(FILE): retorna el byte actual
    
    Formas de leer
        - Por formato
        
    string
    strcpy(a,b): a = b
    strcat(a, b): a = a+b
    strcmp(a, b): retorn 0 si son iguales
    strstr(a, b): busca a 'b' en 'a'
    atoi(char *): convierte de cadena a int
    itoa(char *): al reves
    atof
    
*/
int main(){
    FILE *f = fopen("prueba.txt", "r");
    if(!f){ // f== NULL
        exit(-1);
    }else{
        fseek(f, 0, 2);
        int T = ftell(f);
        fseek(f, 0, 0);
        char info[T], linea[T], info2[T];
        
        strcpy(info,"");
        while(!feof(f)){
            fgets(linea, T, f);
            strcat(info, linea); // info+=linea
        }

        fseek(f, 0, 0);
        for(i = 0; i < T; i++) info2[i] = getc(f);
        
    }
    return 0;
}






