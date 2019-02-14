/* 

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
// cvha: para romper la recursividad
// n: el numero de niveles
int threeChilds(int cvha, int childs, int n){
    for (int i = 0; i < 3; i++){
        childs = fork();
        if (childs == 0){
            if (i == 1){
                if (cvha == (n - 1))return 0;
                threeChilds(cvha + 1, childs, n);
            }
            break;
        }
    }
}

int main()
{
    pid_t childs, padre = getpid();
    int i, j, k;
    int N = 10;

    threeChilds(0,childs,5);
    if (padre == getpid())
    {
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        if (i == 3)
        {
            for (i = 0; i < 7; i++)
            {
                wait(NULL);
            }
        }
    }
    else
    {
        sleep(1);
    }

    return 0;
}
// cvha: para romper la recursividad
// n: el numero de niveles
