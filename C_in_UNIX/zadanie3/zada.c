/*
autor: Szymon Oleś      data napisania: 06.04.2021
program do obslugi bledow
*/
#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NMAX 100

extern const char *const sys_siglist[];

/*funkcja do konwersji numeru sygnalu na nazwe*/
void upcase(char *s)
{
    while (*s)
    {
        *s = toupper(*s);
        s++;
    }
}
/*funkcja do wlasnej obslugi sygnalow*/
void my_sighandler(int signo)
{
    /*konwersja numeru sygnalu na nazwe*/
    char *nazwa = strdup(sys_siglist[signo]);
    if (!nazwa)
    {
        printf("blad konwersji na nazwe\n");
        return;
    }
    upcase(nazwa);
    printf("\nnumer: %d\nnazwa: %s\n", signo, nazwa);
    free(nazwa);
    return;
}

int main(int argc, char const *argv[])
{
    int arg,arg2;

    /*  sprawdzenie ilosci argumentow   */
    if (argc < 3)
    {
        printf("za malo argumentow\n");
        return 1;
    }
    arg = atoi(argv[1]);
    arg2 = atoi(argv[2]);

    /*  wypisanie pid   */
    printf("PIDa: %d\n", getpid());

    /*  obsluga sygnalow  */
    switch (arg)
    {
    case 1:
        if (signal(arg2, SIG_DFL) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z SIG_DFL");
            exit(EXIT_FAILURE);
        }
        break;
    case 2:
        if (signal(arg2, SIG_IGN) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z SIG_IGN");
            exit(EXIT_FAILURE);
        }
        break;

    case 3:
        if (signal(arg2, my_sighandler) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z my_sighandler");
            exit(EXIT_FAILURE);
        }
        break;

    default:
        printf("podano nieodpowiedni typ sygnalu");
        return 1;
    }
    /*  pauza   */
    if (pause() != -1)
    {
        perror("pause error");
        exit(EXIT_FAILURE);
    }
    return 0;
}
