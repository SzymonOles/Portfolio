/*
autor: Szymon Oleś      data napisania: 24.03.2021
program wypisujący identyfikatory z zewnętrznego programu
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define NMAX 100

int main(int argc, char const *argv[])
{
    
    char nazwa[NMAX], dir[NMAX] = "./";
    /*
    sprawdzenie ilosci argumentow
    */
    if (argc < 2)
    {
        printf("za malo argumentow\n");
        return 1;
    }
    /*
    pobranie argumentow z maina i przeksztalcenie na sciezke
    */
    strcpy(nazwa, argv[1]);
    strcat(dir, nazwa);

    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n===================================================\n", getuid(), getgid(), getpid(), getppid(), getpgrp());

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
        /*
        uruchomienie programu zewnetrznego z execa
        */
            switch (execl(dir, nazwa, NULL))
            {
            case -1:
                perror("execl error");
                _exit(2);
                break;
            default:
                break;
            }

        default:
            switch (wait(0))
            {
            case -1:
                perror("wait error");
                exit(1);
                break;

            default:
                break;
            }
        };
    }

    return 0;
}
