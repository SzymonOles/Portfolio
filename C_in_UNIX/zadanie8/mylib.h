#ifndef __MYCODE_H__
#define __MYCODE_H__
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>


//def funkcji===============================

mqd_t kolejka_otworz(const char *name, int oflag);  //otwieranie kolejki

mqd_t kolejka_stworz(const char *name, int oflag, mode_t mode, struct mq_attr *attr);   //tworzenie kolejki

int kolejka_zamnkij(mqd_t mqdes);   //zamykanie kolejki 

int kolejka_usun(const char *name); //usuwanie kolejki

int kolejka_pobierzatrybuty(mqd_t mqdes, struct mq_attr *attr); //pobieranie atrybutow kolejki

int kolejka_ustawatrybuty(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);   //ustawianie atrybutow kolejki

int kolejka_wyslij(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);    //wysylanie do kolejki

int kolejka_pobierz(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);    //pobieranie z kolejki

//==========================================
#endif