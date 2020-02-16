#include <termios.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include "constants.h"
#include "screen.h"
#include "circle.h"
#include "utils.h"

/* Goto topleft(pos[0,0]) and clear display */
static inline void  __attribute__((always_inline)) clear()
{
	printf("\033[H\033[J");
}

static volatile enum BOOL run = TRUE;

static void intHandler(int idc)
{
	run = FALSE;
}

int main(int argc, char *argv[])
{
	struct termios old, new;
	struct ply *voidb = calloc(1, sizeof(struct ply));
	struct tap *chain = calloc(1, sizeof(struct tap));
	struct tap *pains = NULL;
	char  *s = NULL;
	char   c = '\0';
	unsigned int size = 0;

	/* catch CTRL-C for freeing memory on interrupt */
	/* In noncanonical mode, input is available immediately */
	enableRaw(&new, &old);
	signal(SIGINT, intHandler);
	bienvenue();
	initPly(voidb);
	if((size = retrvInpt(voidb->blabla, &s)) == 0)
	{
		fprintf(stderr, "YOU failed!");
		exit(EXIT_FAILURE);
	}
	initCircl(chain, s, size);
	clear();
	printf(
	    "\n\nProgress >                 Score > 0000000                   Player > %s\n"            
	    "╔════════════════════════════════════════════════════════════════════════════════╗\n"
	    "║                                                                                ║\n"
	    "╚════════════════════════════════════════════════════════════════════════════════╝\n"
            "                               _.-._         _.-._                                \n"                           
            "                             _| | | |       | | | |_                              \n"  
            "                            | | | | |       | | | | |                             \n"
            "                            | | | | |_     _| | | | |                             \n"
            "                            | `     | |   | |     ` |                             \n"
            "                            ;       /`/   \\`\\       ;                           \n"
            "                            |        /     \\        |                            \n"
            "                             \\      /       \\      /                            \n" 
            "                              |    |         |    |                               \n"
            "                              |    |         |    |                               \n"
	, voidb->pseudo);
	do {
		movCursor(BEG, LIN);
		pains = dispNCircl(chain, 80);
		colorFinger(pains);
		movCursor(MID, LIN);
		c = getc(stdin);
		resetFinger(pains);
		/* handle backspace */
		if (c == 0x7f) {
			chain = chain->tapbck;
			continue;
		}
		checkInput(c, pains);
		chain = chain->tapnxt;
	} while(run);
	restCircl(chain);
	freeBobby(4, s, voidb->blabla, voidb->pseudo, voidb);
	disablRaw(&old);

	return 0;
}
