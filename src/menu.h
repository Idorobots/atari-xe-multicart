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

typedef struct game_info {
  unsigned char mask;
  const char *title;
} GAME_INFO;

#define MASK_RD5 0x80 // NOTE Game occupies both cartridge memory banks.

#define CART_8KB(offset, title) {(offset), (title)}
#define CART_16KB(offset, title) {(offset) | MASK_RD5, (title)}

#endif // __MENU_H__
