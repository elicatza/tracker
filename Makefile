PROGRAMNAME=tracker
CC=gcc
CFLAGS=-std=c89 -Wall -Wshadow
# use -Wextra and -fmudflap flag for evaluation

# Locations
SRCDIR=src
OUTDIR=/usr/local/bin

PROGRAM=$(addprefix $(OUTDIR)/, $(PROGRAMNAME))


all: $(PROGRAM)


$(PROGRAM): $(SRCDIR)/main.o
	$(CC) -o $@ $(SRCDIR)/main.c

