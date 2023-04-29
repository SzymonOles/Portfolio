#ifndef __MYCODE_H__
#define __MYCODE_H__
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/stat.h>

//def funkcji===============================

sem_t *sem_otworz(const char *name, int oflag);
sem_t *sem_stworz(const char *name, int oflag, mode_t mode, unsigned int value);
int sem_zamknij(sem_t *sem);
int sem_usun(const char *name);
int sem_podnies(sem_t *sem);
int sem_opusc(sem_t *sem);
int sem_wartosc(sem_t *sem);

//==========================================
#endif