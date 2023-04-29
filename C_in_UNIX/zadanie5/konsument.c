/*
autor: Szymon Oleś      data napisania: 16.04.2021
program do konsument
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#define NMAX 100
#define BUFSIZE2 2
#define MAXSLEEP 2

int main(int argc, char const *argv[]) //arg0:fifo  arg2:plik2
{
    //sprawdzanie argumentów
    if (argc != 3)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 2 argumenty: POTOK FILE2\n");
        return 1;
    }

    int fd;
    char bufk[NMAX];
    int readval;
    char creadval[NMAX];
    int plik2;
    srand(time(NULL));

    if ((fd = open(argv[1], O_RDONLY)) == -1) //otwarcie fifo
    {
        perror("potok open error konsument\n");
        exit(1);
    }

    plik2 = open(argv[2], O_TRUNC | O_WRONLY); //pobieranie deskryptora pliku
    if (plik2 == -1)
    {
        perror("open error\n");
        exit(1);
    }

    //niezmienione z poprzedniego zadania

    while ((readval = read(fd, bufk, BUFSIZE2)) > 0) //petla pobieranie pliku po rozmiarze bufora
    {
        if (readval == -1)
        {
            perror("read error\n");
            exit(1);
        }

        sprintf(creadval, "%d", readval); //konwersja zwracanej wartosci z reada zeby mozna puscic przez write

        sleep((rand() % MAXSLEEP) + 1); //rand sleep

        printf("\nkonsument----\n");
        if (write(STDOUT_FILENO, creadval, readval) == -1) //wypisanie wartosci
        {
            perror("write error\n");
            exit(1);
        }
        if (write(STDOUT_FILENO, bufk, readval) == -1)
        {
            perror("write error\n");
            exit(1);
        }
        if (write(plik2, bufk, readval) == -1) //wpisanie do pliku
        {
            perror("write error\n");
            exit(1);
        }
    }
    if (close(fd) == -1)
    {
        perror("close error\n");
        exit(1);
    }
    if (close(plik2) == -1)
    {
        perror("close error\n");
        exit(1);
    }
    _exit(0);
}