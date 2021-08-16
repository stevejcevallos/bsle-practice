#*- MakeFile -*-
CC = gcc
TARGET = Capstone

SRCDIR = src
BINDIR = bin
INCDIR = include

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst %,$(BINDIR)/%, $(notdir $(SOURCES:.c=.o)))

CFLAGS= -Wall -pthread

$(BINDIR)/$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(TARGET)