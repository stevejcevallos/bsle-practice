#*- MakeFile -*-
CC=gcc
CFLAGS= -Wall -pthread -g

_OBJ = server_network.o threadpool.o 
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))
ODIR = SRC

IDIR = include

_DEPS = threadpool.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

PORT = 2000
IP = 127.0.0.1

$(ODIR)/%.o: SRC/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
all: $(OBJ)
	mkdir -p BIN
	$(CC) $(CFLAGS) -o BIN/capstone $^

$(OBJ): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

execute: all 
	BIN/capstone

client: 
	python3 SRC/client/client_network.py $(IP) $(PORT)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all -s BIN/capstone

test: $(OBJ)
	$(CC) $(CFLAGS) -lcunit -o Test $^ Tests/main_tests.c Tests/general_tests.c
	Tests

clean:
	rm -f BIN/capstone
	rm -f $(ODIR)/*.o
	rm -f BIN/test
	rm -f BIN/test-Results.xml
	rm -f BIN/test-Listing.xml
	rmdir BIN
	rm -f SRC/client/users.txt
