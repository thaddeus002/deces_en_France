
CC = gcc
CFLAGS = -Wall -O2
CFLAGSPLPLOT = $(shell pkg-config --cflags plplot)
SVG = deces_par_jour.svg deces_par_age.svg

all: $(SVG)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

trace.o: trace.c trace.h
	$(CC) $(CFLAGS) $(CFLAGSPLPLOT) -c $<

plotYearsData: plotYearsData.o trace.o deces.o dates.o
	$(CC) -o $@ plotYearsData.o trace.o deces.o dates.o -lplplot

$(SVG): plotYearsData
	./plotYearsData

clean:
	rm -f *.o 

mrproper: clean
	rm -f plotYearsData

.PHONY: clean mrproper
