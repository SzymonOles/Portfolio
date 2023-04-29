#include "mylib.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//funkcje================================

mqd_t kolejka_otworz(const char *name, int oflag)
{
    mqd_t temp;
    if ((temp = mq_open(name, oflag)) == -1)
    {
        perror("mq_open error\n");
        exit(1);
    }
    return temp;
}

mqd_t kolejka_stworz(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
    mqd_t temp;
    if ((temp = mq_open(name, oflag, mode, attr)) == -1)
    {
        perror("mq_create error\n");
        exit(1);
    }
    return temp;
}

int kolejka_zamnkij(mqd_t mqdes)
{
    int temp;
    if ((temp = mq_close(mqdes)) == -1)
    {
        perror("mq_close error\n");
        _exit(1);
    }
    return temp;
}

int kolejka_usun(const char *name)
{
    int temp;
    if ((temp = mq_unlink(name)) == -1)
    {
        perror("mq_unlink error\n");
        _exit(1);
    }
    return temp;
}

int kolejka_pobierzatrybuty(mqd_t mqdes, struct mq_attr *attr)
{
    int temp;
    if ((temp = mq_getattr(mqdes, attr)) == -1)
    {
        perror("mq_getattr error\n");
        exit(1);
    }
    return temp;
}

int kolejka_ustawatrybuty(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr)
{
    int temp;
    if ((temp = mq_setattr(mqdes, newattr, oldattr)) == -1)
    {
        perror("mq_setattr error\n");
        exit(1);
    }
    return temp;
}

int kolejka_wyslij(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    int temp;
    if ((temp = mq_send(mqdes, msg_ptr, msg_len, msg_prio)) == -1)
    {
        perror("mq_send error\n");
        exit(1);
    }
    return temp;
}

int kolejka_pobierz(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio)
{
    int temp;
    if ((temp = mq_receive(mqdes, msg_ptr, msg_len, msg_prio)) == -1)
    {
        perror("mq_receive error\n");
        exit(1);
    }
    return temp;
}
//=======================================