#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
sem_t s;
void signal_handler(int signal)
{
    sem_post(&s);
}
void *f(void *param)
{
    sem_wait(&s);
    printf("I had to wait until your signal released me!\n");
}

int main()
{
    int ok = sem_init(&s, 0, 0);
    if (ok == -1) {
       perror("Could not create unnamed semaphore");
       return 1;
    }
    signal(SIGINT,signal_handler);

    pthread_t id;
    pthread_create(&id, NULL, f, NULL);
    pthread_exit(NULL);
}