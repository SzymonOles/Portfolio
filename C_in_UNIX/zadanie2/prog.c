/*
autor: Szymon Oleś      data napisania: 24.03.2021
--------------------------------------------------
program do wypisywania uid gid pid ppid pgid
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    /*
    wypisanie uid gid pid ppid pgid
    */
    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
}
