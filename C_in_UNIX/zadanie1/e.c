#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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
            switch (setpgid(0,0))
            {
            case -1:
                perror("setpgid error");
                exit(2);
            default:
                break;
            }
            printf("UID: %d GID: %d PID: %d PPID: %d PGID: %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
        default:
            wait(0);
        };
    }
    
    return 0;
}
