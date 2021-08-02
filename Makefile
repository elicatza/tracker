PROGRAMNAME=tracker
CC=gcc
CFLAGS=-std=c89 -Wall -Wshadow
# use -Wextra and -fmudflap flag for evaluation

# Locations
SRCDIR=src
OUTDIR=bin

PROGRAM=$(addprefix $(OUTDIR)/, $(PROGRAMNAME))


all: $(PROGRAM)


$(PROGRAM): $(OUTDIR)/main.o
	$(CC) -o $@ $(OUTDIR)/main.o

 
$(OUTDIR)/main.o: $(SRCDIR)/main.c
	$(CC) -c $(CFLAGS) -o $@ $(SRCDIR)/main.c


clean:
	rm -f $(OUTDIR)/*.o $(PROGRAM)

