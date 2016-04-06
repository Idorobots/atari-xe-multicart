#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <atari.h>
#include <unistd.h>

#define CCTL ((unsigned char *) 0xD500)
#define COPY_AREA 0x1000 // NOTE This may collide with DOS.
#define RESET 0xFFFC

unsigned char off = 0; // NOTE Game offset in BSS.

void __fastcall__ execute(void) {
  // Swap the game.
  *CCTL = off;

  // Reset the console.
  __asm__ ("jmp (%w)", RESET);
}

int main(void) {
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

  if(off > 0) {
    // Backup exec() into the RAM not to loose it later.
    memcpy((void *) COPY_AREA, (const void *) execute, 1024); // FIXME Compute the size somehow.

    // Jump into the backup.
    __asm__ ("jmp %w", COPY_AREA);
  }

  printf("Bye!\n");
  sleep(1);

  return 0;
}
