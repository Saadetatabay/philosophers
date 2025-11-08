#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int num = 0;
pthread_mutex_t ledger_lock;
void *ledfer(void *data)
{
    pthread_mutex_lock(&ledger_lock);
    num+=1;
    pthread_mutex_unlock(&ledger_lock);
    return NULL;
}

int main()
{
    int i;
    pthread_mutex_init(&ledger_lock,NULL);
    pthread_t persons[5000];
    
    for(i=0;i<5000;i++)
    {
        pthread_create(persons+i,NULL,ledfer,NULL);
        
    }
    for(i=0;i<5000;i++)
    {
        pthread_join(persons[i],NULL);
    }   
    printf("%d\n",num);
}