#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
#include "constants.h"
#include "screen.h"

/* Goto topleft(pos[0,0]) and clear display */
static inline void  __attribute__((always_inline)) clear()
{
	printf("\033[H\033[J");
}

void freeBobby(int count, ...)
{
	va_list ap;

	va_start(ap, count);
	while(count--)
		free(va_arg(ap, void *));
	va_end(ap);
}

void cleanBuf(char *buff, int size)
{
	int i;

	for(i = 0; i < size; i++)
		if(buff[i] < 0x20 || buff[i] > 0x7e)
			buff[i] = ' ';
}

void preview(const char *f)
{
	FILE *fp;
	char *s = calloc(42, sizeof(char));
	char *d = calloc(42, sizeof(char));
	
	snprintf(d, 41, ALB);
	strncat(d, f, 40-strlen(d));
	if((fp = fopen(d, "rb")) != NULL)
	{
		fread(s, sizeof(char), 41, fp);
		fclose(fp);
		cleanBuf(s, 41);
		printf("- [%s]\n", s);
		freeBobby(2, s, d);
	}
}

char *pickBlabla(void) 
{
	DIR *dd;
	struct dirent *dir;
	char *fileList[MAX_FILES_COUNT];
	char *relativePath = NULL;
	int c,i = 0;
	
	if((dd = opendir(ALB)) != NULL) 
	{
		printf("[?] - Choose your playbook : \n");
		/* loop over files in directory */
		while ((dir = readdir(dd)) != NULL)
			/* check if it is a regular file */
			if(dir->d_type == DT_REG && i<= MAX_FILES_COUNT)
			{
				printf("\t%d] - %-20s ", i, dir->d_name);
				/* add 1 to size for null char */ 
				fileList[i] = calloc(strlen(dir->d_name)+1, sizeof(char));
				sprintf(fileList[i], "%s", dir->d_name); 
				preview(dir->d_name);
				i++;
			}
		closedir(dd);
	}
	printf("> ");
	c = getc(stdin)-'0';
	if(c >= 0 && c <= i)
	{
		/* add 1 to size for null char */
		relativePath = calloc(strlen(ALB)+strlen(fileList[c])+1, sizeof(char));
		sprintf(relativePath, "%s%s", ALB, fileList[c]);
	}
	for(i=i-1;i>=0;i--)
		free(fileList[i]);

	return relativePath;
}

void initPly(struct ply *p)
{
	p->score = 0;
	p->progr = 0;
	p->pseudo = calloc(MAX_PSEUDO_SIZE, sizeof(char));
	printf("\n\n[?] - Please enter your pseudo : ");
	fgets(p->pseudo, MAX_PSEUDO_SIZE, stdin);
	/* delete carriage return */ 
	p->pseudo[strlen(p->pseudo) - 1] = '\0';
	p->blabla = pickBlabla();
}
	
int retrvInpt(char *path, char **s)
{
	/* Since we want to start typing at offset 40, we had 40 spaces at the
	 * beginning of the input text(foo.txt). This trick should be replaced
	 * by using \033[x;yH escape sequence which allow us to manipulate the
	 * terminal cursor. */

	FILE *fp;
	int size;
	
	if((fp = fopen(path, "rb")) == NULL)
		return 0;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp) + 1 + PAD;
	fseek(fp, 0, SEEK_SET);
	/* Add PAD to the size for padding */
	if((*s = calloc(size, sizeof(char))) == NULL)
		return 0;
	/* Set s[0:PAD] to ' ', this centered text at beginning */  
	memset(*s, ' ', PAD);
	fread(*s+PAD, sizeof(char), size-PAD, fp);
	fclose(fp);
	cleanBuf(*s, size);

	return size;
}

void blzConstr(char s[])
{
	static unsigned int i = 1;

	if(i == 0)
		s[BLA_SIZE - 1] = s[BLA_SIZE - 1] + 0x20;
	else
		s[i - 1] = s[i - 1] + 0x20;
	s[i] = s[i] - 0x20;
	i = (i + 1) % BLA_SIZE;
}

void barConstr(char s[])
{
	unsigned int j = 0;
	static unsigned int i = 0;

	for(; j < strlen(BAR); j++)
	{
		s[j] = BAR[(j + i) % BAR_SIZE];
		s[j + 5] = s[j];
	}
	i = (i + 1) % BAR_SIZE;
}

void bienvenue(void)
{
	struct timespec ts = { .tv_sec  = 0,
			       .tv_nsec = 250000000L};
	unsigned int i;
	unsigned int j = 3;
	char *chain = calloc(BUF_SIZE,   sizeof(char));
	char *blazz = calloc(BLA_SIZE_N, sizeof(char));

	strncpy(blazz, BLA, BLA_SIZE_N);
	while(j)
	{
		for(i = 0; i < BAR_SIZE; i++)
		{
			barConstr(chain);
			blzConstr(blazz);
			clear();
			/* Middle of the screen(~80) */
			movCursor(MID-7, LIN-5);
			fprintf(stdout, "%s %s %s", chain, blazz, chain+5);
			fflush(stdout);
			nanosleep(&ts, NULL);
		}
		j--;
	}
	freeBobby(2, chain, blazz);
}

void enableRaw(struct termios *new, struct termios *old)
{
	/* backup old conf */
	tcgetattr(STDIN_FILENO, old);
	new = old;
	/* set new to raw mode */
	new->c_lflag &= ~(ICANON);
	/* force apply imm. */ 
	tcsetattr(STDIN_FILENO, TCSANOW, new);
}

void disablRaw(struct termios *old)
{
	/* force rest. imm. */ 
	tcsetattr(STDIN_FILENO, TCSANOW, old);
}

enum BOOL checkInput(char c, struct tap *t)
{
	if(c == t->caract)
		t->status = TRUE;
	else
		t->status = FALSE;

	return t->status;
}	
