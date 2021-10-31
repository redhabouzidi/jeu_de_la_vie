main : grille.o io.o jeu.o main.o
	gcc -o main grille.o io.o jeu.o main.o
grille.o: grille.c grille.h 
	gcc -c grille.c
io.o: io.c io.h grille.h jeu.h 
	gcc -c io.c
jeu.o: jeu.c jeu.h grille.h 
	gcc -c jeu.c
main.o:io.h grille.h jeu.h main.c 
	gcc -c main.c
make clean:
	rm *.o
make dist:
	tar -jcvf RedhaBouzidi-TP3-2.0.tar.xz grille.c grille.h main.c io.c io.h jeu.c jeu.h
