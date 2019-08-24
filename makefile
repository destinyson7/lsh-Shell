CC=gcc
CFLAGS=-I ./ -lncurses
DEPS=def.h
OBJ= main.o cd.o echo.o pwd.o ls.o pinfo.o fg_bg.o history.o prompt.o nightswatch.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lsh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o 