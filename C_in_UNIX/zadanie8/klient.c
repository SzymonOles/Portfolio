#include "mylib.h"
#include "nazwy.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#define MAXSLEEP 2  //dla sleep
#define NMAX 100 //rozmiar dla tabel
mqd_t *pointer1;
mqd_t *pointer2;
char *pointer3;

void koniec()
{
    kolejka_zamnkij(pointer1);
    kolejka_zamnkij(pointer2);
    kolejka_usun(pointer3);
    printf("\nposprzatano\n");
}
void end()
{
    exit(0);
}

int main(void)
{
    mqd_t mq,smq;
    pid_t pid;
    char pathname[NMAX];
    char buf[NMAX];
    char wiadomosc[NMAX];
    char odebrana[NMAX];
    struct mq_attr attr;
    attr.mq_curmsgs=0;
    attr.mq_flags=0;
    attr.mq_maxmsg=5;
    attr.mq_msgsize=NMAX;

    sleep(1);
    srand(time(NULL));

    //nazwa kolejki
    pid = getpid();
    if (sprintf(pathname, "/%d", pid)<0)
    {
        perror("sprintf error");
        exit(1);
    }

    //wypisanie
    printf("nazwa: %s\n",pathname);
    printf("deskryptor: %d\n",pid);
    printf("mq_curmsgs: %ld\n",attr.mq_curmsgs);
    printf("mq_flags: %ld\n",attr.mq_flags);
    printf("mq_maxmsg: %ld\n",attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n\n",attr.mq_msgsize);

    //tworzenie kolejki
    mq = kolejka_stworz(pathname, O_RDONLY | O_CREAT , 0777, &attr);
    pointer3 = pathname;
    pointer1 = mq;

    //sighandler
    if (signal(SIGINT, end) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGINT");
        _exit(1);
    }
    if (atexit(koniec) != 0)
    {
        perror("atexit error");
        _exit(1);
    }

    //otworzenie kolejki serwera
    smq= kolejka_otworz(QNAME, O_WRONLY);
    pointer2 = smq;

    strcat(wiadomosc,pathname);
    strcat(wiadomosc,"\n");

    //wczytanie komunikatu
    printf("podaj: LICZBA ZNAK LICZBA\n");
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        if (feof(stdin))
        {
            break;
        }
        strcat(wiadomosc,buf);
    }

    //wyslanie komunikatu
    kolejka_wyslij(smq,wiadomosc,sizeof(wiadomosc),0);

    sleep((rand()%MAXSLEEP)+1);

    //odbieranie komunikatu
    kolejka_pobierz(mq,odebrana,sizeof(odebrana),NULL);

    printf("odebrano: %s\n",odebrana);

    return 0;
}
