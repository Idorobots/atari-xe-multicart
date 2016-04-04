#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <atari.h>

extern char _dos_type;                          /* bss variable */

int main(void) {
  unsigned char off = 0;

  clrscr();
  printf("Select game (1-32): ");

  if (_dos_type != 1) scanf("%d", &off);

  // TODO Copy this program into the RAM.

  printf("You may now [RESET] your console.");

  // Swap the game.
  *((unsigned char *) 0xD500) = off & 0x3F; // NOTE At most 6 bits should be used.

  // TODO Jump into the newly swapped game.

  return 0;
}
