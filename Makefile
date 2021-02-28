CC     = gcc
CFLAGS = -I $(IDIR) -g -Wall
IDIR   = inc
SOURCE = src
ODIR   = obj
LDIR   = lib
LIBS   = -lm
BUILDDIR = ./
_DEPS  = ssd1306.h
DEPS   = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ   = example.o ssd1306.o ubuntuMono_8pt.o ubuntuMono_16pt.o ubuntuMono_24pt.o ubuntuMono_48pt.o
OBJ    = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SOURCE)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILDDIR)/ssd1306_example: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BUILDDIR)/*~ core $(INCDIR)/*~ 

install:
	cp $(BUILDDIR)/ssd1306_example /usr/local/bin/ssd1306_sysinfo
