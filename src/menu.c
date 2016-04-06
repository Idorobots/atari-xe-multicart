#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <atari.h>
#include <unistd.h>

#define CCTL ((unsigned char *) 0xD500)
#define CART_START 0xBFFA
#define COPY_AREA 0x1000 // NOTE This may collide with DOS.

void __fastcall__ menu(void) {
  unsigned char off = 0;
  unsigned int *address = (unsigned int *) 0xBFFA;

  clrscr();
  printf("    _  _            _  __  _____ \n");
  printf("   /_\\| |_ __ _ _ _(_) \\ \\/ / __|\n");
  printf("  / _ \\  _/ _` | '_| |  >  <| _| \n");
  printf(" /_/ \\_\\__\\__,_|_| |_| /_/\\_\\___|\n");
  printf("  __  __      _ _   _             _   \n");
  printf(" |  \\/  |_  _| | |_(_)__ __ _ _ _| |_ \n");
  printf(" | |\\/| | || | |  _| / _/ _` | '_|  _|\n");
  printf(" |_|  |_|\\_,_|_|\\__|_\\__\\__,_|_|  \\__|\n\n");

  // TODO Needs a better selection menu.
  printf("Select a game (1-32): ");
  scanf("%d", &off);

  // Swap the game.
  *CCTL = off;

  // Jump into the newly swapped game.
  if(off > 0) {
    __asm__ ("jmp (%w)", CART_START);
  }

  printf("Bye!\n");
  sleep(1);
}

int main(void) {
  // Backup menu() into the RAM not to loose it later.
  memcpy((void *) COPY_AREA, (const void *) menu, 1024); // FIXME Compute the size somehow.

  // Jump into the backup.
  __asm__ ("jmp %w", COPY_AREA);

  return 0;
}
