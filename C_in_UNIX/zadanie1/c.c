#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n===================================================\n",getuid(),getgid(),getpid(),getppid(),getpgrp());

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            printf("\nUID: %d GID: %d PID: %d PPID: %d PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
            sleep(1);
            break;
        default:
            break;
        };
    }

    return 0;
}
