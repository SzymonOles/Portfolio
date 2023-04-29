/*
autor: Szymon Oleś      data napisania: 06.04.2021
program tworzacy podprocesy
*/

#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define NAME "zada.x"
#define PATH "./zada.x"

int main(int argc, char const *argv[])
{
    int arg2, wstat,wstat2;
    /*
    sprawdzenie ilosci argumentow
    */
    if (argc < 3)
    {
        printf("za malo argumentow\n");
        return 1;
    }
    setpgid(getpid(), getpid());
    printf("PID: %d PGID: %d\n\n", getpid(), getpgrp());
    arg2 = atoi(argv[2]);

    if (signal(arg2, SIG_IGN) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIG_IGN");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error\n");
            exit(1);
        case 0:
            /*
        uruchomienie programu zewnetrznego z execa
        */
            if (execl(PATH, NAME, argv[1], argv[2]) == -1)
            {
                perror("execl error\n");
                _exit(2);
            }
        default:
            break;
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if ((wstat2 = wait(&wstat)) == -1)
        {
            perror("wait error");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("wait status: %d for : %d\n", wstat,wstat2);
        }
    }

    return 0;
}
