/**
 * \file main.c
 * code principale
 *\author Redha Bouzidi
 */
#include <stdio.h>

#include "../include/grille.h"
#include "../include/io.h"
#include "../include/jeu.h"



int main (int argc, char ** argv) {
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}
    voisin=&compte_voisins_vivants;
    	fage=NULL;
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
