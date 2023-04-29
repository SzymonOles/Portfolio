#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define maxsleep 2

int sekcje, watki;

int counter = 0;
pthread_mutex_t mutex;

void gotoxy(unsigned x, unsigned y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}
void gotoxynodel(unsigned x, unsigned y)
{
    printf("\033[%d;%dH", y, x);
}

void *funkcja(void *attr)
{
    int nr = attr;
    sleep(1);
    int val = 0;
    srand(time(NULL));

    for (int i = 0; i < sekcje; i++)
    {
        //sekcja prywatna
        gotoxy(0, 4 + watki + attr);
        printf("%d prywatna: %d\n", nr, i);
        sleep((rand() % maxsleep) + 1);
        if (pthread_mutex_lock(&mutex) != 0)
        {
            printf("mutex lock error\n");
            return 1;
        }
        //sekcja krytyczna
        val = counter;
        val++;
        gotoxy(20, 4 + watki + attr);
        printf("krytyczna: %d\n", i);
        gotoxynodel(0, 4 + watki + attr);
        printf("%d\n", attr);
        sleep((rand() % maxsleep) + 1);
        counter = val;
        if (pthread_mutex_unlock(&mutex) != 0)
        {
            printf("mutex lock error\n");
            return 1;
        }
    }
    gotoxy(0, 4 + watki + attr);
    printf("%d zakonczono\n", attr);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("nieodpowiednia ilosc argumentow - podaj 2 - watki sekcje\n");
        return 1;
    }
    system("clear");

    watki = atoi(argv[1]);
    sekcje = atoi(argv[2]);
    pthread_t tid[watki];

    //inicjowanie mutexa
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("mutex init error\n");
        return 1;
    }

    //tworzenie watkow
    for (int i = 0; i < watki; i++)
    {
        if (pthread_create(&tid[i], NULL, &funkcja, i) != 0)
        {
            printf("pthread create error\n");
            return 1;
        }
    }

    //wypisanie
    printf("=========wypisanie=======\n");
    printf("mutex: %p\n", &mutex);
    for (int i = 0; i < watki; i++)
    {
        printf("nr: %d id: %ld\n", i, tid[i]);
    }
    printf("=========================\n");

    //czekanie watkow
    for (int i = 0; i < watki; i++)
    {
        if (pthread_join(tid[i], NULL) != 0)
        {
            printf("pthread join error\n");
            return 1;
        }
    }

    //niszczenie mutexa
    if (pthread_mutex_destroy(&mutex) != 0)
    {
        printf("mutex destroy error\n");
        return 1;
    }

    //wypisanie koncowe
    gotoxy(0, 4 + watki + watki);
    printf("licznik globalny: %d\n", counter);
    printf("oczekiwana wartosc: %d\n", watki * sekcje);
    if (counter == watki * sekcje)
    {
        printf("dane zgodne\n");
    }
    else
    {
        printf("dane niezgodne\n");
    }

    return 0;
}
