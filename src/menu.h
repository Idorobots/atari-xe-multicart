#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <atari.h>
#include <unistd.h>

#define CCTL ((unsigned char *) 0xD500)
#define DOSVEC ((unsigned int *) 0x0A)

#define BOOTSTRAP_SIZE 0x400                     // FIXME Compute the size somehow.
#define BOOTSTRAP_AREA (0x8000 - BOOTSTRAP_SIZE) // NOTE Right before the second cart bank.

#define RESET 0xFFFC

#endif // __MENU_H__
