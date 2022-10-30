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
void infeccion(){
    boolean seguir = T; 
    while(seguir)
    {
        printf("Tengo covid y ahora juego todo el dia al lol y subi a bronce 3 \n");
        sleep(1);
        if(GenerateRandom() < 0.5)
        {
            seguir = F;
        }
    }
}
int main(int argc, char* argv[]){
    infeccion();
    return 0;
}