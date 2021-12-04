CC = gcc
OPATH=obj/
HPATH = include/
CPATH = src/
CFLAGS = -g -W -Wall
EXEC=main
OBJECTS =  $(MAIN) $(IO) libjeu.a
vpath %.c src
vpath %.o obj
vpath %.h include

ifeq ($(MODE),TEXTE)

MAIN=main.o
IO=io.o
else
CPPFLAGS = -lcairo -lm -Iinclude -I/usr/include/cairo -lX11
MAIN=cairo.o
IO=io_cairo.o
endif

$(EXEC) :$(MAIN) $(IO) libjeu.a
	mkdir $(OPATH)
	mkdir bin
	mv *.o $(OPATH)
	$(CC) $(CFLAGS) -o  bin/$@  obj/$(MAIN) obj/grille.o obj/$(IO) obj/jeu.o $(CPPFLAGS)
	
libjeu.a:grille.o jeu.o
	ar -crv libjeu.a grille.o jeu.o
	ranlib libjeu.a
	mkdir lib
	mv libjeu.a lib/
grille.o: grille.h
io.o:io.h
jeu.o:jeu.h
%.o : %.c
	gcc  $(CFLAGS) -Iinclude -c  -o $@ $<
clean :
	rm -f -r bin obj lib
dist:
	tar -jcvf RedhaBouzidi-TP3-2.0.tar.xz $(CPATH)grille.c $(HPATH)grille.h $(CPATH)main.c $(CPATH)io.c $(HPATH)io.h $(CPATH)jeu.c $(HPATH)jeu.h
docs:
	doxygen Doxyfile
