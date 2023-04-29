/*
autor: Szymon Oleś      data napisania: 16.04.2021
program do producent
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
#define BUFSIZE 3
#define MAXSLEEP 2

int main(int argc, char const *argv[]) //arg1:plik1  arg2:potok
{
    //sprawdzanie argumentów
    if (argc != 3)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 2 argumenty: FILE1 POTOK\n");
        return 1;
    }

    int fd;
    char bufp[NMAX];
    int readval2;
    char creadval2[NMAX];
    int plik1;
    srand(time(NULL));

    if ((fd = open(argv[2], O_WRONLY)) == -1) //otwarcie fifo
    {
        perror("potok open error producent\n");
        exit(1);
    }

    plik1 = open(argv[1], O_RDONLY); //pobieranie deskryptora pliku
    if (plik1 == -1)
    {
        perror("open error\n");
        exit(1);
    }

    //niezmienione z poprzedniego zadania

    while ((readval2 = read(plik1, bufp, BUFSIZE)) > 0) //petla pobieranie pliku po rozmiarze bufora
    {
        if (readval2 == -1)
        {
            perror("read error\n");
            exit(1);
        }

        sprintf(creadval2, "%d", readval2); //konwersja zwracanej wartosci z reada zeby mozna puscic przez write

        sleep((rand() % MAXSLEEP) + 1); //rand sleep

        printf("\nPRODUCENT====\n");
        //wypisanie wartosci
        if (write(STDOUT_FILENO, creadval2, readval2) == -1)
        {
            perror("write error\n");
            exit(1);
        }

        if (write(STDOUT_FILENO, bufp, readval2) == -1)
        {
            perror("write error\n");
            exit(1);
        }

        //wpisanie do strumienia
        if (write(fd, bufp, readval2) == -1)
        {
            perror("write error\n");
            exit(1);
        }
    }
    if (close(fd) == -1)
    {
        perror("write error\n");
        exit(1);
    }
    if (close(plik1) == -1)
    {
        perror("write error\n");
        exit(1);
    }
    _exit(0);
}
