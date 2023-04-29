#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>
#include "pamiec.h"
#include "semafory.h"
#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5  // Liczba elementow bufora
const char *pointer7;
const char *pointer8;
const char *pointer9;

typedef struct
{
    char buf[NBUF][NELE];
    int wstaw, wyjmij;
} PD;

void koniec()
{
    sem_usun(pointer7);
    sem_usun(pointer8);
    pamiec_usun(pointer9);
    printf("posprzatano\n");
}
void end()
{
    exit(0);
}
//1producent 2producentpath 3konsument 4konsumentpath 5filename1 6filename2 7NameP 8NameK 9NameM
int main(int argc, char const *argv[])
{
    int memfd;
    int semPval = NBUF;
    int semKval = 0;

    //sprawdzanie argumentów
    if (argc != 10)
    {
        printf("nieodpowiednia liczba argumentow:\n");
        return 1;
    }

     pointer7 = argv[7];
     pointer8 = argv[8];
     pointer9 = argv[9];

    //sighandler
    if (signal(SIGINT, end) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGINT");
        exit(1);
    }
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        _exit(1);
    }
    printf("uruchomiono sighandler\n");

    //tworzenie semaforow
    sem_stworz(argv[7], O_CREAT | O_EXCL, 0777, semPval);
    sem_stworz(argv[8], O_CREAT | O_EXCL, 0777, semKval);
    printf("utworzono semafory\n");

    //wypisanie nazw wartosci semaforow
    printf("%s  %d\n", argv[7], semPval);
    printf("%s  %d\n", argv[8], semKval);

    //tworzenie pamieci wspoldzielonej
    memfd = pamiec_otworz(argv[9], O_RDWR | O_CREAT | O_EXCL, 0777);
    pamiec_rozmiar(memfd, sizeof(PD));
    printf("utworzono pamiec wspoldzilona\n");

    //wypisanie nazw dlugosci pamieci
    printf("%d  %ld\n", memfd, sizeof(PD));

    //tworzenie producenta
    switch (fork())
    {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        if (execl(argv[2], argv[1], argv[9], argv[5], argv[7], argv[8], argv[9], NULL) == -1)
        {
            perror("execl error\n");
            exit(1);
        }
        break;
    default:
        break;
    }
    printf("utworzono producenta\n");

    //tworzenie konsumenta
    switch (fork())
    {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        if (execl(argv[4], argv[3], argv[9], argv[6], argv[7], argv[8], argv[9], NULL) == -1)
        {
            perror("execl error\n");
            exit(1);
        }
        break;
    default:
        break;
    }
    printf("utworzono konsumenta\n");

    //wait
    for (int i = 0; i < 2; i++)
    {
        if (wait(NULL) == -1)
        {
            perror("wait error");
        }
    }
    printf("skonczono czekac\n");
    pamiec_zamknij(memfd);
    printf("zamknieto pamiec glowna - koniec glownego\n");
    return 0;
}
