#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{   
    int n_procesos = 16;
    pid_t pid;
    int i;
    int p[2];

    if(pipe(p) == -1)
    {
        printf("error al crear la tuberia");
        return 1;
    }

    for(i = 0; i < n_procesos; i++)
    {
        pid = fork();
        if(pid == 0)
        {   
            break;
        }
        sleep(1);
    }

    if(pid==0)
    {
        srand(time(NULL));
        printf("Region %d: ", i+1);
        int ps5_pr = (random())%32;
        write(p[1], &ps5_pr, sizeof(int));
        printf("Se vendieron %d Kaiba(PS5)\n", ps5_pr);
        //exit(0);
    }    
    else
    {
        int reader=0;
        int total = 0;
        for (int i=0;i<n_procesos;i++)
        {
            if(wait(NULL)>=0)
            {
                read(p[0],&reader,sizeof(int));
                total = reader + total;
            }
        }
        printf("Kaibas vendidos en el pais: %d\n",total);
    }
    return 0; 
}