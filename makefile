bin/main : grille.o io.o jeu.o main.o
	gcc -o bin/main obj/grille.o obj/io.o obj/jeu.o obj/main.o 
grille.o: src/grille.c include/grille.h 
	gcc -c -o obj/grille.o src/grille.c 
io.o: src/io.c include/io.h include/grille.h include/jeu.h 
	cd obj
	gcc -c -o obj/io.o src/io.c 
jeu.o: src/jeu.c include/jeu.h include/grille.h 
	cd obj
	gcc -c -o obj/jeu.o src/jeu.c 
main.o: include/io.h include/grille.h include/jeu.h src/main.c 
	cd obj
	gcc -c -o obj/main.o src/main.c 
make clean:
	rm obj/*.o bin/main
make dist:
	tar -jcvf RedhaBouzidi-TP3-2.0.tar.xz grille.c grille.h main.c io.c io.h jeu.c jeu.h
