#include "menu.h"

const GAME_INFO games[] = {
#include "games.c"
};

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
  clrscr();
  printf("    _  _            _  __  _____ \n");
  printf("   /_\\| |_ __ _ _ _(_) \\ \\/ / __|\n");
  printf("  / _ \\  _/ _` | '_| |  >  <| _| \n");
  printf(" /_/ \\_\\__\\__,_|_| |_| /_/\\_\\___|\n");
  printf("  __  __      _ _   _             _   \n");
  printf(" |  \\/  |_  _| | |_(_)__ __ _ _ _| |_ \n");
  printf(" | |\\/| | || | |  _| / _/ _` | '_|  _|\n");
  printf(" |_|  |_|\\_,_|_|\\__|_\\__\\__,_|_|  \\__|\n\n");
  printf("%40s", "http://idorobots.org\n\n");
  sleep(2);

  for(;;) {
    unsigned int i = 0;
    const unsigned int num_games = sizeof(games)/sizeof(games[0]);
    int n = 0;

    for(; i < num_games; ++i) {
      if(i > 0 && i % 22 == 0) {
        printf("\n\nPress any key to continue...");
        cgetc();
      }
      printf("\n%2d. %s", i + 1, games[i].title);
    }

    printf("\n\nSelect a game (1-%d): ", num_games);
    scanf("%d", &n);

    if((n > 0) && (n < (num_games + 1))) {
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
    sleep(1);
    clrscr();
  }

  return 0;
}
