#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("PID: %d PPID: %d PGID: %d\n===================================================\n",getpid(),getppid(),getpgrp());
    /*printf("PID: %d PPID: %d PGID: %d\n==================================\n",getpid(),getppid(),getpgrp());   do drzewa*/

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n",getuid(), getgid(), getpid(), getppid(), getpgrp());
            /*printf("PID: %d PPID: %d PGID: %d\n", getpid(), getppid(), getpgrp());    do drzewa*/
            sleep(1);
        default:
            break;
        };
    }

    sleep(4);
    return 0;
}
