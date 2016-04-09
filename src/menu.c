#include "menu.h"

unsigned char selection;
unsigned int DOSVEC_save;

void __fastcall__ bootstrap(void) {
  // Restore the DOS vector.
  *DOSVEC = DOSVEC_save;

  // Swap the game.
  *CCTL = selection;

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
  scanf("%d", &selection);

  if(selection > 0) {
    // Backup bootstrap() into the RAM not to loose it later.
    memcpy((void *) BOOTSTRAP_AREA, (const void *) bootstrap, BOOTSTRAP_SIZE);

    // Spoof the return address so we jump back into bootstrap().
    DOSVEC_save = *DOSVEC;
    *DOSVEC = BOOTSTRAP_AREA;

    // Do the cleanup.
    exit(1);
  }

  printf("Bye!\n");
  sleep(1);

  return 0;
}
