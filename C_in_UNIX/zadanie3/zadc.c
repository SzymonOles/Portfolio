/*
autor: Szymon Oleś      data napisania: 06.04.2021
program tworzacy podproces i wysylajacy sygnal do grupy
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
#define NAME "zadc2.x"
#define PATH "./zadc2.x"

int main(int argc, char const *argv[])
{
    int pid;
    int arg2;
    /*
    sprawdzenie ilosci argumentow
    */
    if (argc < 3)
    {
        printf("za malo argumentow\n");
        return 1;
    }
    arg2 = atoi(argv[2]);

    switch (pid = fork())
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
        sleep(2);
        if (kill((-1) * (pid), 0) == 0)
        {
            kill((-1) * (pid), arg2);
        }
        else
        {
            perror("kill error\n");
            _exit(2);
        }
        break;
    };
    if (wait(0) == -1)
    {
        perror("wait error");
        exit(EXIT_FAILURE);
    }
    return 0;
}
