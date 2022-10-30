#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int n_personas;
int n,m,k;
int libre=0, condenao=0;
int atrapados=0;
int personas=0;
sem_t semaforo1;
pthread_mutex_t mutex, mutex2; //mutex para variable de personas custodia, condenados.

typedef enum {F,T} boolean;
float GenerateRandom()
{
    float max = 1, min = 0;
    boolean first = T;
    if (first)
    {
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

void* threadFunction()
{
    while((atrapados) < n_personas)
    {
        pthread_mutex_lock(&mutex);
        if(atrapados < n_personas)
        {
            atrapados++;
            personas++;
            printf("Martin lo pillaron jugando Mundial Ronaldinho Soccer 64 en la plaza\n");
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* condenar()
{
    sem_wait(&semaforo1);
    pthread_mutex_lock(&mutex2);
    condenao++;
    pthread_mutex_unlock(&mutex2);

    printf("Entro a proceso \n");

    printf("Eso no era cilantro, era peregil 10 anios de carcel para ti\n");
    sleep(1); //10 aÃ±os en 1 segundo
    printf("fin del proceso\n");

    sem_post(&semaforo1);
}

void* juhgao()
{
    boolean seguir = T;
    while(seguir)
    {        
        pthread_mutex_lock(&mutex); 
        if(personas > 0)
        {
            personas--;
            pthread_mutex_unlock(&mutex); //
            if(GenerateRandom() > 0.5)
            {
                printf("Soy el paopa de jorge nos vemos en tribunales (===)\n");
                condenar();
            }
            else
            {
                printf("no era kripi era oregano rey (===)\n");
                pthread_mutex_lock(&mutex2);
                libre++;
                pthread_mutex_unlock(&mutex2);
            }
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
        if((condenao+libre) >= n_personas)
        {
            seguir = F;
        }
    }
    //printf("==============================thread saliendo=================================================\n");
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    printf("Cantidad de personas que seran atrapadas: ");
    scanf("%d",&n_personas);
    printf("Ingrese cantidad de pacos que llevan personas al tribunal: ");
    scanf("%d",&n);
    printf("Ingrese cantidad de tribunales: ");
    scanf("%d",&m);
    printf("Maximo de procesados: ");
    scanf("%d",&k);
    if(n<0 || k<0 || m<0)
    {
        //Caso de negativos en m o n o k
        return -1;
    }
    if(n <= m || m <= k)
    {
        printf("Ha retornado -1 \n");
        return (-1);
    }

    sem_init(&semaforo1,0,k); //procesar

    //============================tribunales==============================

    pthread_t tribunales[m];
    for (int i = 0; i < m; i++)
    {
        //pthread_t id;
        pthread_create(&tribunales[i],NULL,juhgao,NULL);
    }
    //=============================pac
    pthread_t Pacos[n]; //
    for (int i = 0; i < n; i++)
    {
        //pthread_t id;
        pthread_create(&Pacos[i],NULL,threadFunction,NULL);
    }
    
    for (int i = 0; i < m; i++)
    {
        pthread_join(tribunales[i],NULL);
    }

    sem_destroy(&semaforo1);

    printf("Atrapados: %d\n",atrapados);
    printf("Cantidad de personas libres: %d\n", libre);
    printf("Cantidad de personas condenadas: %d\n", condenao);

    return 0;
}