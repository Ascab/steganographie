CC=gcc
CFLAGS= -Wall
all: stegano

stegano: Sources/binary_operation.o Sources/codage.o Sources/fonction_affichage.o Sources/stegano_main.o
	$(CC) -o stegano $^ $(CFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
clean: 
	rm -f Sources/*.o
mrproper: clean
	rm -f stegano
