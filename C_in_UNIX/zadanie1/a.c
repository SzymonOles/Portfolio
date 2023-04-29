#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
    return 0;
}
