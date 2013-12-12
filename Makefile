
CFLAGS = `pkg-config --cflags gtk+-2.0` -Wall -g -I/usr/include/gsl 
LIBS =  `pkg-config --libs gtk+-2.0`  -lm  -lgsl -lgslcblas 

CC = gcc
RM = /bin/rm -rf

OBJECTS = oos.o rng_analyse.o rng_model.o \
	lib_error.o lib_file.o lib_string.o \
	pl_misc.o pl_parse.o pl_scan.o pl_operators.o pl_print.o

XOBJECTS = xrng.o x_widgets.o x_diagram.o x_browser.o lib_cairox.o

all:
	make rng
	make xrng
	make monte_carlo
	make rng_fit
#	make rng_client

rng:	$(OBJECTS) rng.o
	$(RM) $@
	$(CC) -g -o $@ $(CFLAGS) $(LDFLAGS) $(OBJECTS) rng.o $(LIBS)

xrng:	$(OBJECTS) $(XOBJECTS)
	$(RM) $@
	$(CC) -g -o $@ $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(XOBJECTS) $(LIBS)

monte_carlo:	$(OBJECTS) monte_carlo.o
	$(RM) $@
	$(CC) -g -o $@ $(CFLAGS) rng_analyse.o monte_carlo.o $(LIBS)

rng_fit:	$(OBJECTS) rng_fit.o
	$(RM) $@
	$(CC) -g -o $@ $(CFLAGS) $(OBJECTS) rng_fit.o $(LIBS)



rng_client:	$(OBJECTS) rng_client.o /usr/local/lib/libexpress.a
	$(RM) $@
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJECTS) rng_client.o $(LIBS) -lexpress

clean:
	$(RM) *.o *~ core tmp.* */*~ NONE none
	$(RM) *.tgz xrng rng rng_client

tar:
	make clean
	tar cvfz ~/Dropbox/Source/rng_20130719_NS.tgz *

oos_test:	$(OBJECTS) oos_test.o
	$(RM) $@
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(OBJECTS) oos_test.o $(LIBS)

