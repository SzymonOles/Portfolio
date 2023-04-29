#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <string.h>
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
    int readval;
    int fdfile;
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
    if ((fdfile = open(argv[2], O_RDONLY)) == -1)
    {
        perror("file open error\n");
        exit(1);
    }
    printf("otwarto plik producenta\n");

    //otwieranie semaforow
    semK = sem_otworz(argv[4], O_RDWR);
    semP = sem_otworz(argv[3], O_RDWR);
    printf("otwarto semafory producenta: %p %p\n", (void *)semK, (void *)semP);

    //otwieranie pamieci
    fdshm = pamiec_otworz(argv[5], O_RDWR, 0777);
    printf("otwarto pamiec producenta: %d\n", fdshm);

    //odwzorowanie pamieci
    PD *bufor;
    bufor = (PD *)pamiec_odwzoruj(NULL, sizeof(PD), PROT_READ | PROT_WRITE, MAP_SHARED, fdshm, 0);
    printf("odwzorowano pamiec producenta\n");

    // Umiesc towar w pamieci wspoldzielonej

    while (1)
    {
        sleep((rand() % maxsleep) + 1);

        // Opusc semafor Producenta
        sem_opusc(semP);

        printf("Producent semP: %d semK: %d index: %d\n", sem_wartosc(semP), sem_wartosc(semK), bufor->wstaw);
        printf("index: %d\n", bufor->wstaw);

        //czytanie z pliku
        readval = read(fdfile, bufor->buf[bufor->wstaw], NELE);
        if (readval != NELE)
        {
            printf("wstawia: %d \n\t", readval);
            if (write(STDOUT_FILENO, bufor->buf[bufor->wstaw], readval == -1))
            {
                perror("Błąd write na ekran");
                exit(1);
            }
            printf("\n");
            bufor->buf[bufor->wstaw][readval] = '\0';
            printf("wstawiono eof\n");
            // Podniesc semafor Konsumenta
            sem_podnies(semK);
            break;
        }
        else if (readval == -1)
        {
            printf("read error\n\t");
            exit(1);
        }
        else
        {
            printf("wstawia: %d \n", NELE);
            if (write(STDOUT_FILENO, bufor->buf[bufor->wstaw], NELE) == -1)
            {
                perror("Błąd write na ekran");
                exit(1);
            }
            printf("\n");
        }
        // Przesun pozycje wstawiania o 1 dalej
        bufor->wstaw = (bufor->wstaw + 1) % NBUF;

        // Podniesc semafor Konsumenta
        sem_podnies(semK);
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
    printf("zamknieto odwzorowanie i pamiec producenta\n");
    //zamkniecie semaforow
    sem_zamknij(semK);
    sem_zamknij(semP);
    printf("zamknieto semafory - koniec producenta\n");
    return (0);
}
