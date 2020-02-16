CC=gcc
CFLAGS=-W -Wall -pedantic 
LDFLAGS=
EXEC=taptap
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

taptap: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

taptap.o: taptap.c constants.h

screen.o: screen.c constants.h

circle.o: circle.c constants.h

utils.o: utils.c constants.h screen.c

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
