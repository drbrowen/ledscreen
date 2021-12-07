CC = cc
RM = rm -f
COPTIONS=-O3
CINCLUDES=-I../rpi_ws281x/
CLIBS = -L../rpi_ws281x/ -lws2811 -lm -lgif

PROG=ledtest

COBJS= main.o \
	gifloader.o \
	make_display.o \



all: $(PROG)

testgifloader: gifloader.h gifloader.c testgifloader.c
	$(CC) -o $@ $(COPTIONS) $(CINCLUDES) $(CLIBS) gifloader.c testgifloader.c

$(PROG): $(COBJS) ../rpi_ws281x/libws2811.a
	$(RM) $@
	$(CC) -o $@ $(COBJS) $(COPTIONS) $(CLIBS)

%.o: %.c
	$(RM) $@
	$(CC) -c $*.c $(COPTIONS) $(CINCLUDES)
