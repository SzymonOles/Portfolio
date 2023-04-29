#include "semafory.h"
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

//funkcje================================

sem_t *sem_otworz(const char *name, int oflag)
{
    sem_t *temp;
    if ((temp = sem_open(name, oflag)) == SEM_FAILED)
    {
        perror("semaphore open error\n");
        exit(1);
    }
    return temp;
}
sem_t *sem_stworz(const char *name, int oflag, mode_t mode, unsigned int value)
{
    sem_t *temp;
    if ((temp = sem_open(name, oflag, mode, value)) == SEM_FAILED)
    {
        perror("semaphore create error\n");
        exit(1);
    }
    return temp;
}
int sem_zamknij(sem_t *sem)
{
    if (sem_close(sem) == -1)
    {
        perror("semaphore close error\n");
        exit(1);
    }
    return 0;
}
int sem_usun(const char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("semaphore unlink error\n");
        exit(1);
    }
    return 0;
}
int sem_podnies(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("semaphore post error\n");
        exit(1);
    }
    return 0;
}
int sem_opusc(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("semaphore wait error\n");
        exit(1);
    }
    return 0;
}
int sem_wartosc(sem_t *sem)
{
    int temp;
    sem_getvalue(sem,&temp);
    return temp;
}

//=======================================