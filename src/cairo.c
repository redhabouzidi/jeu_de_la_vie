/**
 * \file main.c
 * code principale
 *\author Redha Bouzidi
 */
#include <stdio.h>

#include "../include/grille.h"
#include "../include/io_cairo.h"
#include "../include/jeu.h"
	pas_oc=0;
	delai_oc=0;
	ageevo=0;
int main (int argc, char ** argv) {
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}
	
    	
    	
	fage = NULL;
	voisin = &compte_voisins_vivants;
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
