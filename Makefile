CC = cc
RM = rm -f
COPTIONS=-O3
CINCLUDES=-I../rpi_ws281x/
CLIBS = -L../rpi_ws281x/ -lws2811 -lm

PROG=brotest

COBJS= main.o

all: $(PROG)

$(PROG): $(COBJS) ../rpi_ws281x/libws2811.a
	$(RM) $@
	$(CC) -o $@ $(COBJS) $(COPTIONS) $(CLIBS)

%.o: %.c
	$(RM) $@
	$(CC) -c $*.c $(COPTIONS) $(CINCLUDES)
