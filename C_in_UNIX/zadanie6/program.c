/*
autor: Szymon Oleś      data napisania: 04.05.2021
program wzajemnego wykluczania procesow - semafory
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "mycode.h"
#define MAXSLEEP 2

int main(int argc, char const *argv[]) //1-LSekcji 2-NazwaSem 3-nazwapliku
{
    FILE *fd;
    sem_t *Sadr;
    int numer = 0;
    srand(time(NULL));

    //sprawdzanie argumentów
    if (argc != 4)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 1 argumenty: lSekcji, SemName, FilName\n");
        return 1;
    }

    //otwieranie semafora
    Sadr = sem_otworz(argv[2], O_RDWR);

    for (int j = 0; j < atoi(argv[1]); j++)
    {
        printf("przed PID: %d Val: %d SK: %d\n", getpid(), sem_wartosc(Sadr), j);

        sleep((rand() % 2) + 1);

        //sekcja krytyczna
        sem_opusc(Sadr);

        //otwarcie pliku
        if ((fd = fopen(argv[3], "r")) == NULL)
        {
            perror("blad tworzenia pliku\n");
            exit(1);
        }

        //czytanie z pliku
        if (fscanf(fd, "%d", &numer)==0)
        {
            perror("nic nie odczytano\n");
            exit(1);
        }

        //zamkniecie pliku
        if (fclose(fd) == -1)
        {
            perror("blad zamykania pliku\n");
            exit(1);
        }

        printf("    PID: %d Val: %d SK: %d\n", getpid(), sem_wartosc(Sadr), j);
        printf("    odczytano: %d\n",numer);

        numer++;

        printf("    wpisano: %d\n",numer);
        sleep((rand() % 2) + 1);

        //otwarcie pliku
        if ((fd = fopen(argv[3], "w")) == NULL)
        {
            perror("blad tworzenia pliku\n");
            exit(1);
        }

        //zapis do pliku
        if (fprintf(fd, "%d", numer)<0)
        {
            perror("blad zapisu do pliku\n");
            exit(1);
        }
        

        //zamkniecie pliku
        if (fclose(fd) == -1)
        {
            perror("blad zamykania pliku\n");
            exit(1);
        }

        sem_podnies(Sadr);
        printf("po PID: %d Val: %d SK: %d\n", getpid(), sem_wartosc(Sadr), j);
    }

    sem_zamknij(Sadr); //zamkniecie semafora

    _exit(0);
}