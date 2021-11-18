CC = gcc
HPATH = include/
OPATH = obj/
CPATH = src/
CFLAGS = -g -W -Wall
OBJECTS =  obj/main.o obj/grille.o obj/io.o obj/jeu.o
vpath %.o obj/
vpath %.c src/
vpath %.h include/
vpath main bin/

main : $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/main $(OBJECTS) 
main.o :
grille.o : grille.h
jeu.o : jeu.h grille.h
io.o : io.h jeu.h grille.h
obj/%.o : %.c 
	gcc $(DEFINE) $(CFLAGS) -c  -o $@ $<


clean :
	rm bin/* obj/*.o RedhaBouzidi-TP3-2.0.tar.xz
make dist:
	tar -jcvf RedhaBouzidi-TP3-2.0.tar.xz $(CPATH)grille.c $(OPATH)grille.h $(CPATH)main.c $(CPATH)io.c $(OPATH)io.h $(CPATH)jeu.c $(OPATH)jeu.h
make docs:
	doxygen Doxyfile
cairo: obj/cairo.o
	
	gcc -o cairo obj/cairo.o -lcairo -lm -Iinclude -I/usr/include/cairo -lX11
	
src/cairo.o:src/cairo.c
	gcc -c -o obj/cairo.o src/cairo.c
