#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#define NUM_THREADS 4 

void *thread1 (void *);
void *thread2 (void *);
void *thread3 (void *);
void *thread4 (void *);

int main(int argc, char *argv[]) 
{ 
    int i, scope;
    pthread_t tid[NUM_THREADS]; 
    pthread_attr_t attr; /* get the default attributes */ 
    pthread_attr_init(&attr); /* first inquire on the current scope */
    if (pthread_attr_getscope(&attr, &scope) != 0) 
        fprintf(stderr, "Unable to get scheduling scope\n"); 
    else { 
        if (scope == PTHREAD_SCOPE_PROCESS) 
            printf("PTHREAD_SCOPE_PROCESS"); 
        else if (scope == PTHREAD_SCOPE_SYSTEM) 
            printf("PTHREAD_SCOPE_SYSTEM"); 
        else
            fprintf(stderr, "Illegal scope value.\n"); 
    } 

    /* set the scheduling algorithm to PCS or SCS */ 
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); 

    /* create the threads */
    for (i = 0; i < NUM_THREADS; i++) 
    {
        if (i == 0)
        {
            pthread_create(&tid[i],&attr,thread1,NULL); 
        }
        else if (i == 1)
        {
            pthread_create(&tid[i],&attr,thread2,NULL);
        } 
        else if (i == 2)
        {
            pthread_create(&tid[i],&attr,thread3,NULL); 
        }
        else if (i == 3)
        {
            pthread_create(&tid[i],&attr,thread4,NULL); 
        }
    }

    /* now join on each thread */
    for (i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(tid[i], NULL); 
    }
    pthread_exit(NULL);
    return 0;
}

// use top command
void *thread1 (void *para)
{
    system("gnome-terminal -x sh -c 'ps; exec bash'");
}

// use ls -l command
void *thread2 (void *para)
{
    system("gnome-terminal -x sh -c 'ls -l; exec bash'");
}

//use ps command
void *thread3 (void *para)
{
    system("gnome-terminal -x sh -c 'cd /HDH ; nano Pthread-Scheduling-API.c; exec bash'");
}

// use nano file.txt 
void *thread4 (void *para)
{
    system("gnome-terminal -x sh -c 'top; exec bash'");
}

 