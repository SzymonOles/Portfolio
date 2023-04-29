#ifndef __SEMAFORY_H__
#define __SEMAFORY_H__
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

//def funkcji===============================

sem_t *sem_otworz(const char *name, int oflag); //otwieranie istniejacego semafora
sem_t *sem_stworz(const char *name, int oflag, mode_t mode, unsigned int value);    //tworzenie semafora
int sem_zamknij(sem_t *sem);    //zamykanie semafora(odlaczanie)
int sem_usun(const char *name); //usuwanie semafora
int sem_podnies(sem_t *sem);  //podnoszenie semafora
int sem_opusc(sem_t *sem);  //opuszczanie semafora
int sem_wartosc(sem_t *sem);    //pobieranie wartosci semafora

//==========================================
#endif