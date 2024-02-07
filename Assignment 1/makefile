CC=gcc
CFLAGS=-I. -g -w
DEPS= 
OBJ = sevenseg.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
sevenseg: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)