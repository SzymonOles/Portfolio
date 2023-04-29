/*
autor: Szymon Oleś      data napisania: 15.04.2021
program do przesylania potokami
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#define MAXSLEEP 2
#define NMAX 100
#define BUFSIZE 3  //producent
#define BUFSIZE2 2 //konsument

int main(int argc, char const *argv[]) //arg0:plik1  arg2:plik2
{
    //sprawdzanie argumentów
    if (argc != 3)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 2 argumenty: FILE1 FILE2\n");
        return 1;
    }

    int fd[2]; //0-read 1-write     filedescriptor

    if (pipe(fd) == -1) //pipe ktory bedzie dziedziczony
    {
        perror("pipe error\n");
        exit(1);
    }

    switch (fork()) //switch fork
    {
    case -1:
        perror("fork error\n");
        exit(1);

    //konsument=======================================
    case 0:;
        char bufk[NMAX];
        int readval;
        char creadval[NMAX];
        int plik2;
        srand(time(NULL));

        if (close(fd[1]) == -1)
        {
            perror("close error\n");
            exit(1);
        }

        plik2 = open(argv[2], O_TRUNC | O_RDWR); //pobieranie deskryptora pliku
        if (plik2 == -1)
        {
            perror("close error\n");
            exit(1);
        }

        while ((readval = read(fd[0], bufk, BUFSIZE2)) != 0) //petla pobieranie pliku po rozmiarze bufora
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
        if (close(fd[0]) == -1)
        {
            perror("close error\n");
            exit(1);
        }
        if (close(plik2) == -1)
        {
            perror("close error\n");
            exit(1);
        }
        break;

    //producent========================================
    default:;
        char bufp[NMAX];
        int readval2;
        char creadval2[NMAX];
        int plik1;
        srand(time(NULL));

        if (close(fd[0]) == -1)
        {
            perror("close error\n");
            exit(1);
        }

        plik1 = open(argv[1], O_RDONLY); //pobieranie deskryptora pliku
        if (plik1 == -1)
        {
            perror("open error\n");
            exit(1);
        }

        while ((readval2 = read(plik1, bufp, BUFSIZE)) != 0) //petla pobieranie pliku po rozmiarze bufora
        {
            if (readval2 == -1)
            {
                perror("read error\n");
                exit(1);
            }

            sprintf(creadval2, "%d", readval2); //konwersja zwracanej wartosci z reada zeby mozna puscic przez write

            //rand sleep
            sleep((rand() % MAXSLEEP) + 1);

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
            if (write(fd[1], bufp, readval2) == -1)
            {
                perror("write error\n");
                exit(1);
            }
        }
        if (close(fd[1]) == -1)
        {
            perror("write error\n");
            exit(1);
        }
        if (close(plik1) == -1)
        {
            perror("close error\n");
            exit(1);
        }

        if (wait(NULL) == -1)
        {
            perror("wait error\n");
        }
        break;
    }

    return 0;
}
