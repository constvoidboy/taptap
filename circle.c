#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void initCircl(struct tap *chain, const char *s, const unsigned int size)
{
	unsigned int i = 0;
	struct tap *current = chain;
	struct tap    *last = NULL;

	for(; i < size; i++)
	{
		current->caract = s[i];
		current->status = UNDEF;
		current->tapnxt = calloc(1, sizeof(struct tap)); 
		current->tapbck = last;
		last = current;
		current = current->tapnxt;
	}
	free(last->tapnxt);
	last->tapnxt = chain;
	chain->tapbck = last;
}

void restCircl(struct tap *chain)
{
	struct tap *current = chain;
	struct tap    *next = NULL;

	while(current->tapnxt != chain) 
	{
		next = current->tapnxt;
		free(current);
		current = next;
	}
	free(current);
}

struct tap *dispNCircl(struct tap *chain, unsigned int size)
{
	struct tap *current = chain;
	struct tap *middles = NULL;
	unsigned int midsiz = (size / 2) - 1;

	while(size--) 
	{
		switch(current->status)
		{
			case FALSE:
				fprintf(stdout, "%s%c%s", RED_FG, current->caract, RES);
				break;
			case TRUE:
				fprintf(stdout, "%s%c%s", GRE_FG, current->caract, RES);
				break;
			case UNDEF:
				fprintf(stdout, "%c", current->caract);
		}
		if(size == midsiz)
			middles = current;
		current = current->tapnxt;
	}

	return middles;
}
