/*
autor: Szymon Oleś      data napisania: 06.04.2021
program wysylajacy sygnal podprocesowi
*/

#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#define NAME "zada.x"
#define PATH "./zada.x"

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
    arg2=atoi(argv[2]);

    switch (pid=fork())
    {
    case -1:
        perror("fork error\n");
        exit(1);
    case 0:
        /*
        uruchomienie programu zewnetrznego z execa
        */
        if (execl("./zada.x", "zada.x", argv[1], argv[2]) == -1)
        {
            perror("execl error\n");
            _exit(2);
        }

    default:
        sleep(2);
        if (kill(pid, 0) == 0)
        {
            kill(pid,arg2);
        }
        else
        {
            perror("kill error\n");
            _exit(2);
        }
        break;
    };

    return 0;
}
