#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "pamiec.h"
#include "semafory.h"
#define NELE 7 // Rozmiar elementu bufora w bajtach
#define NBUF 3 // Liczba elementow bufora
#define maxsleep 2

//1memfd 2filename 3NAMEP 4NAMEK 5NAMEM
int main(int argc, char const *argv[])
{
    int fdshm;
    sem_t *semK;
    sem_t *semP;
    int fdfile;
    int eof;
    srand(time(NULL));

    //sprawdzanie argumentów
    if (argc != 6)
    {
        printf("nieodpowiednia liczba argumentow:\n");
        return 1;
    }

    typedef struct
    {
        char buf[NBUF][NELE];
        int wstaw, wyjmij;
    } PD;
    
    //otwarcie pliku
    if ((fdfile = open(argv[2], O_WRONLY | O_TRUNC | O_APPEND)) == -1)
    {
        perror("file open error\n");
        exit(1);
    }
    printf("otwarto plik konsumenta\n");

    //otwieranie semaforow
    semK = sem_otworz(argv[4], O_RDWR);
    semP = sem_otworz(argv[3], O_RDWR);
    printf("otwarto semafory konsumenta: %p %p\n", (void *)semK, (void *)semP);

    //otwieranie pamieci
    fdshm = pamiec_otworz(argv[5], O_RDWR, 0777);
    printf("otwarto pamiec konsumenta: %d\n", fdshm);

    //odwzorowanie pamieci
    PD *bufor;
    bufor = (PD *)pamiec_odwzoruj(NULL, sizeof(PD), PROT_READ | PROT_WRITE, MAP_SHARED, fdshm, 0);
    printf("odwzorowano pamiec konsumenta\n");

    while (1)
    {
        sleep((rand() % maxsleep) + 1);

        // Opusc semafor Konsumenta
        sem_opusc(semK);

        printf("konsument semP: %d semK: %d index: %d\n", sem_wartosc(semP), sem_wartosc(semK), bufor->wyjmij);
        printf("index: %d\n", bufor->wyjmij);

        //szukanie eof
        eof = 0;
        for (int i = 0; i < NELE; i++)
        {
            if (bufor->buf[bufor->wyjmij][i] == '\0')
            {
                eof = 1;
            }
        }
        if (eof)
        {
            if (write(fdfile, bufor->buf[bufor->wyjmij], strlen(bufor->buf[bufor->wyjmij])) == -1)
            {
                perror("write error");
                exit(1);
            }

            printf("pobiera: %ld\n\t", strlen(bufor->buf[bufor->wyjmij]));
            if (write(STDOUT_FILENO, bufor->buf[bufor->wyjmij], strlen(bufor->buf[bufor->wyjmij])) == -1)
            {
                perror("write error");
                exit(1);
            }
            printf("\n");
            sem_podnies(semP);
            printf("\nznaleziono eof\n");
            break;
        }
        else
        {
            if (write(fdfile, bufor->buf[bufor->wyjmij], NELE) == -1)
            {
                perror("write error");
                exit(1);
            }
            printf("pobiera: %d\n\t", NELE);

            if (write(STDOUT_FILENO, bufor->buf[bufor->wyjmij], NELE) == -1)
            {
                perror("write error");
                exit(1);
            }
            printf("\n");
        }
        // Przesun pozycje wstawiania o 1 dalej
        bufor->wyjmij = (bufor->wyjmij + 1) % NBUF;

        // Podniesc semafor Producenta
        sem_podnies(semP);
    }

    //zamkniecie pliku
    if (close(fdfile) == -1)
    {
        perror("close");
        exit(1);
    }
    //zamkniecie pamieci
    pamiec_usun_odwzorowanie(bufor, sizeof(PD));
    pamiec_zamknij(fdshm);
    printf("zamknieto odwzorowanie i pamiec konsumenta\n");
    //zamkniecie semaforow
    sem_zamknij(semK);
    sem_zamknij(semP);
    printf("zamknieto semafory - koniec konsumenta\n");
    return (0);
}
