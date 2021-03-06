#include "menu.h"

extern const GAME_INFO games[];
extern const unsigned int num_games;

unsigned char selection_mask;
unsigned int DOSVEC_save;

void __fastcall__ bootstrap(void) {
  // Restore the DOS vector.
  *DOSVEC = DOSVEC_save;

  // Swap the game.
  *CCTL = selection_mask;

  // Reset the console.
  __asm__ ("jmp (%w)", RESET);
}

int main(void) {
  *CHECKSUM = 0x23; // Ensure cold-start in case the user resets the console.

  clrscr();
  printf("                       _________ \n");
  printf("                      |         |\n");
  printf("                      |     [Z] |\n");
  printf("                      |XE    \"  |\n");
  printf(" __  _____            |Multicart|\n");
  printf(" \\ \\/ / __|           |_       _|\n");
  printf("  >  <| _|              |||||||\n");
  printf(" /_/\\_\\___|             |||||||\n");
  printf("  __  __      _ _   _             _   \n");
  printf(" |  \\/  |_  _| | |_(_)__ __ _ _ _| |_ \n");
  printf(" | |\\/| | || | |  _| / _/ _` | '_|  _|\n");
  printf(" |_|  |_|\\_,_|_|\\__|_\\__\\__,_|_|  \\__|\n\n");
  printf("%40s", "http://idorobots.org\n\n");
  sleep(1);

  if(num_games == 0) {
    printf("\n\nThere are no games configured.\n\nPlease add some games to make this\npaperweight more usefull!");
    while(1); // Sleep forever.
  } else {
    for(;;) {
      unsigned int i = 0;
      int n = 0, ret = 0;

      for(; i < num_games; ++i) {
        if(i > 0 && i % 22 == 0) {
          printf("\n\nPress any key to continue...");
          cgetc();
        }
        printf("\n%2d. %s", i + 1, games[i].title);
      }

      printf("\n\nSelect a game (1-%d): ", num_games);
      ret = scanf("%d", &n);

      if((ret == 1) && (n > 0) && (n <= num_games)) {
        selection_mask = games[n-1].mask;

        // Backup bootstrap() into the RAM not to loose it later.
        memcpy((void *) BOOTSTRAP_AREA, (const void *) bootstrap, BOOTSTRAP_SIZE);

        // Spoof the return address so we jump back into bootstrap().
        DOSVEC_save = *DOSVEC;
        *DOSVEC = BOOTSTRAP_AREA;

        // Do the cleanup.
        exit(1);
      }

      printf("Bad selection!\n");

      if(ret == 0) {
        scanf("%*[^\n]%1*[\n]"); // Drop errorneous line from the input buffer.
      }

      sleep(1);
      clrscr();
    }

  }

  return 0;
}
