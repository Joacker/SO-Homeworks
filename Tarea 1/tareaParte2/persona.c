#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<time.h>


typedef enum {F,T} boolean;
float GenerateRandom()
{
    float max = 1, min = 0;
    boolean first = T;
    if (first)
    {
        srand(time(0));
        first = F;
    }
    if (min > max)
    {
        float temp = max;
        max = min;
        min = temp;
    }
    return min + (float)rand() * (max - min) / (float)RAND_MAX;
}

int main(int argc, char* argv[]){
    //printf("Tetetete: %f \n",GenerateRandom());
    pid_t pid1;
    int status1;
    char *args[] = {"./infeccion",NULL};
    boolean seguir = T;
    while(seguir)
    {
        if(0.5<GenerateRandom()){
            //tiene convid
            printf("Me pegaron la tiña del COVID \n");
            sleep(1);
            if(fork() == 0){
                //hijo
                execv(args[0],args);
            }
            else{
                //padre
                wait(&status1);
                //waitpid(pid1,&status1,0);
                sleep(1);
                printf("Ya me recupere\n");
                seguir = F;
            } 
        }
        else{
            //esta sano
            printf("Estoy sano\n");
        }
        sleep(1);
    }
    return 0;
}