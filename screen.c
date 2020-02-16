#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "mappings.h"

/* Goto topleft(pos[0,0]) and clear display */
static inline void  __attribute__((always_inline)) clear()
{
	printf("\033[H\033[J");
}

/* Mov cursor to pos[x,y] */
void movCursor(unsigned int x, unsigned int y)
{
	printf("\033[%d;%dH", y, x);
}

void resetFinger(struct tap *t)
{
	int i = 0;
	int j = 0;

	for(;i<9;i++)
		if(strchr(keysPerFingers[i], t->caract) != NULL)
			break;
	switch(i)
	{
		case 0:
			movCursor(38,11);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(44,11);
			fprintf(stdout, "%s%c", RES, ' ');
			break;
		case 1:
			movCursor(30,9);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(30,10);
			fprintf(stdout, "%s%c", RES, ' ');
			break;
		case 8:
			movCursor(52,9);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(52,10);
			fprintf(stdout, "%s%c", RES, ' ');
			break;
		case 2:
		case 3:
		case 4:
			j = 32 + (2 * (i - 2));
			movCursor(j,8);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(j,9);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(j,10);
			fprintf(stdout, "%s%c", RES, ' ');
			break;	
		case 5:
		case 6:
		case 7:
			j = 46 + (2 * (i - 5));
			movCursor(j,8);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(j,9);
			fprintf(stdout, "%s%c", RES, ' ');
			movCursor(j,10);
			fprintf(stdout, "%s%c", RES, ' ');
			break;
	}
}

void colorFinger(struct tap *t)
{
	int i = 0;
	int j = 0;

	for(;i<9;i++)
		if(strchr(keysPerFingers[i], t->caract) != NULL)
			break;
	switch(i)
	{
		case 0:
			movCursor(38,11);
			fprintf(stdout, "%s%c%s", GRE_FG, '$', RES);
			movCursor(44,11);
			fprintf(stdout, "%s%c%s", GRE_FG, '$', RES);
			break;
		case 1:
			movCursor(30,9);
			fprintf(stdout, "%s%c%s", GRE_FG, '?', RES);
			movCursor(30,10);
			fprintf(stdout, "%s%c%s", GRE_FG, '?', RES);
			break;
		case 8:
			movCursor(52,9);
			fprintf(stdout, "%s%c%s", GRE_FG, '?', RES);
			movCursor(52,10);
			fprintf(stdout, "%s%c%s", GRE_FG, '?', RES);
			break;
		case 2:
		case 3:
		case 4:
			j = 32 + (2 * (i - 2));
			movCursor(j,8);
			fprintf(stdout, "%s%c%s", GRE_FG, '@', RES);
			movCursor(j,9);
			fprintf(stdout, "%s%c%s", GRE_FG, '@', RES);
			movCursor(j,10);
			fprintf(stdout, "%s%c%s", GRE_FG, '@', RES);
			break;	
		case 5:
		case 6:
		case 7:
			j = 46 + (2 * (i - 5));
			movCursor(j,8);
			fprintf(stdout, "%s%c%s", GRE_FG, '%', RES);
			movCursor(j,9);
			fprintf(stdout, "%s%c%s", GRE_FG, '%', RES);
			movCursor(j,10);
			fprintf(stdout, "%s%c%s", GRE_FG, '%', RES);
			break;
	}
}
