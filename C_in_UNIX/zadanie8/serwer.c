#include "mylib.h"
#include "nazwy.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#define MAXSLEEP 2 //czas sleepa
#define NMAX 100   //rozmiar dla tabel

void koniec()
{
    kolejka_usun(QNAME);
    printf("\nposprzatano\n");
}
void end()
{
    exit(0);
}

int main(void)
{
    char odebrana[NMAX], wynikstr[NMAX];
    char nazwa[NMAX], liczba1[NMAX], liczba2[NMAX], znak[NMAX];
    int l1, l2, wynik;
    mqd_t kmq, mq;
    struct mq_attr attr;
    attr.mq_curmsgs = 0;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = NMAX;

    srand(time(NULL));

    //tworzenie kolejki serwera
    mq = kolejka_stworz(QNAME, O_RDONLY | O_CREAT, 0777, &attr);

    //wypisanie
    printf("nazwa: %s\n", QNAME);
    printf("deskryptor: %d\n", mq);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n\n", attr.mq_msgsize);

    //sighandler
    if (signal(SIGINT, end) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGINT");
        _exit(1);
    }
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        _exit(1);
    }

    while (1)
    {
        printf("oczekiwanie na wiadomosc\n");
        //pobierz wiadomosc
        kolejka_pobierz(mq, odebrana, sizeof(odebrana), NULL);

        //konwertowanie wiadomosci
        if (sscanf(odebrana, "%s %s %s %s", nazwa, liczba1, znak, liczba2) == EOF)
        {
            perror("sscanf error");
            exit(1);
        }

        //otworz kolejke dla klienta
        kmq = kolejka_otworz(nazwa, O_WRONLY);

        //obliczenia
        l1 = atoi(liczba1);
        l2 = atoi(liczba2);
        printf("otrzymano: %s\n", nazwa);
        printf("otrzymano: %d\n", l1);
        printf("otrzymano: %s\n", znak);
        printf("otrzymano: %d\n", l2);
        if (strcmp(znak, "-") == 0)
        {
            wynik = l1 - l2;
        }
        else if (strcmp(znak, "+") == 0)
        {
            wynik = l1 + l2;
        }
        else if (strcmp(znak, "*") == 0)
        {
            wynik = l1 * l2;
        }
        else if (strcmp(znak, "/") == 0)
        {
            wynik = l1 / l2;
        }
        else
        {
            printf("nieznany operator");
            _exit(1);
        }
        
        //konwertowanie wyniku do stringa
        if (sprintf(wynikstr, "%d", wynik) < 0)
        {
            perror("sscanf error");
            exit(1);
        }

        printf("wynik = %s\n", wynikstr);
        sleep((rand() % MAXSLEEP) + 1);

        //wyslanie do klienta
        kolejka_wyslij(kmq, wynikstr, sizeof(wynikstr), 0);

        //znakniecie kolejki klienta
        kolejka_zamnkij(kmq);
    }

    return 0;
}
