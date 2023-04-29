/*
autor: Szymon Oleś      data napisania: 04.05.2021
program wzajemnego wykluczania procesow - semafory
*/
#include "mycode.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#define NMAX 100
#define FILENAME "./numer.txt"
#define MAXSLEEP 2

char *NAME = "/semafor";

void koniec()
{
    printf("usuwanie semafora\n");
    sem_usun(NAME);
    exit(0);
}

int main(int argc, char const *argv[]) //1-nazwa 2-LProc 3-LSek
{
    char pathname[NMAX];
    sem_t *semadress;
    FILE *fd;
    int wynik;
    int STARTVAL = 1;
    srand(time(NULL));

    //sprawdzanie argumentów
    if (argc != 4)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 3 argumenty: nazwa , lProcesow , lSekcji\n");
        return 1;
    }

    if (sprintf(pathname, "./%s", argv[1])<0)
    {
        perror("niepowodzenie pathname");
        exit(1);
    }
    

    //tworzenie semafora
    semadress = sem_stworz(NAME, O_CREAT | O_EXCL, 0777, STARTVAL);

    //przerwanie z klawiatury
    if (signal(SIGINT, koniec) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGINT");
        exit(1);
    }
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(1);
    }

    //wypisanie nazwy adresu semafora
    printf("nazwa sematora: %s\nadres semafora: %p\nwartosc poczatkowa: %d\n", NAME, semadress, sem_wartosc(semadress));

    //tworzenie pliku
    
    if ((fd = fopen(FILENAME, "w")) == NULL)
    {
        perror("blad tworzenia pliku\n");
        exit(1);
    }

    //wpisanie 0 do pliku
    if (fprintf(fd, "%d", 0)<0)
    {
        perror("niepowodzenie zapisu zera do pliku");
        exit(1);
    }
    

    //zamkniecie pliku
    if (fclose(fd) == -1)
    {
        perror("blad zamykania pliku\n");
        exit(1);
    }

    //tworzenie procesow potomnych
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error\n");
            exit(1);
        case 0:
            if (execl(pathname, argv[1], argv[3], NAME, FILENAME, NULL) == -1)
            {
                perror("execl error\n");
                _exit(2);
            }
            break;
        default:
            break;
        }
    }

    //czekanie na procesy
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        if (wait(NULL) == -1)
        {
            perror("wait error");
        }
    }

    //porownanie pliku
    if ((fd = fopen(FILENAME, "r")) == NULL)
    {
        perror("blad tworzenia pliku\n");
        exit(1);
    }

    if (fscanf(fd, "%d", &wynik) == 0)
    {
        perror("nic nie odczytano\n");
        exit(1);
    }

    if (fclose(fd) == -1)
    {
        perror("blad zamykania pliku\n");
        exit(1);
    }

    printf("koncowa zawartosc pliku: %d\n", wynik);
    if (wynik == (atoi(argv[2]) * atoi(argv[3])))
    {
        printf("wynik zgodny\n");
    }
    else
    {
        printf("wynik niezgodny\n");
    }

    return 0;
}