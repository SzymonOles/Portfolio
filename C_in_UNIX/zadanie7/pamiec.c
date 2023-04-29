#include "pamiec.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

//funkcje================================

int pamiec_otworz(const char *name, int flags, mode_t mode)
{
    int fd;
    if ((fd = shm_open(name, flags, mode)) == -1)
    {
        perror("shm open error\n");
        exit(1);
    }
    return fd;
}
int pamiec_rozmiar(int fd, off_t length)
{
    int temp;
    if ((temp=ftruncate(fd, length)) == -1)
    {
        perror("ftruncate error\n");
        exit(1);
    }
    return temp;
}
int pamiec_zamknij(int fd)
{
    int temp;
    if ((temp=close(fd)) == -1)
    {
        perror("close error\n");
        exit(1);
    }
    return temp;
}
int pamiec_usun(const char *name)
{
    int fd;
    if ((fd=shm_unlink(name)) == -1)
    {
        perror("shm unlink error\n");
        exit(1);
    }
    return fd;
}
void *pamiec_odwzoruj(void *addr, size_t length, int prot, int flags,int fd, off_t offset)
{
    void *adr;
    if ((adr=mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED)
    {
        perror("mmap error\n");
        exit(1);
    }
    return adr;
}
int pamiec_usun_odwzorowanie(void *addr, size_t length)
{
    int fd;
    if ((fd= munmap(addr, length)) == -1)
    {
        perror("munmap error\n");
        exit(1);
    }
    return fd;
}

//=======================================