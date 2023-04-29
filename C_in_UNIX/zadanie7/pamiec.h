#ifndef __PAMIEC_H__
#define __PAMIEC_H__
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stddef.h>

//def funkcji===============================

int pamiec_otworz(const char *name, int flags, mode_t mode); //tworzenie/otwieranie pamieci dzielonej
int pamiec_rozmiar(int fd, off_t length); //okreslanie rozmiaru pamieci dzielonej
int pamiec_zamknij(int fd); //zamykanie pamieci dzielonej
int pamiec_usun(const char *name); //usuwanie pamieci dzielonej
void *pamiec_odwzoruj(void *addr, size_t length, int prot, int flags,int fd, off_t offset); //odwzorowanie pamieci dzielonej w pamieci
int pamiec_usun_odwzorowanie(void *addr, size_t length);    //usuniecie odwzorowania

//==========================================
#endif