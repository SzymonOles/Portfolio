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
#include <signal.h>
#define ACCESS 0777
#define NMAX 100
const char *pointer;

void koniec(void)
{
    if (unlink(pointer) == -1)
    {
        printf("\nUNLINKING\n");
        perror("unlink error\n");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    char path1[NMAX];
    char path2[NMAX];
    char pathfifo[NMAX];

    //sprawdzanie argumentów
    if (argc != 6)
    {
        printf("nieodpowiednia liczba argumentow:\nprosze podac 5 argumenty: FILE1 FIFO FILE2 EXEC2 EXEC3\n");
        return 1;
    }

    sprintf(path1,"./%s",argv[4]);  //nazwy sciezkowe
    sprintf(path2,"./%s",argv[5]);
    sprintf(pathfifo,"./%s",argv[2]);

    pointer = pathfifo;

    //tworzenie potoku
    if (mkfifo(argv[2], ACCESS) == -1)
    {
        perror("mkfifo error\n");
        exit(1);
    }

    //robie bez petli bo przekazuje inne nazwy plikow

    switch (fork()) //tworzenie producenta
    {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        if (execl(path1, argv[4], argv[1], argv[2], NULL) == -1)
        {
            perror("execl error\n");
            exit(1);
        }

        break;
    default:
        break;
    }

    switch (fork()) //tworzenie konsumenta
    {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        if (execl(path2, argv[5], argv[2], argv[3], NULL) == -1)
        {
            perror("execl error\n");
            exit(1);
        }
        break;
    default:
        break;
    }
    //sighandler
    if (signal(SIGINT, koniec) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGINT");
        exit(1);
    }
    //wait
    for (int i = 0; i < 2; i++)
    {
        if (wait(NULL) == -1)
        {
            perror("wait error");
        }
    }
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    return 0;
}
