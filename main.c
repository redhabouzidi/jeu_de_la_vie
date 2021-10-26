#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"



int main (int argc, char ** argv) {
    argc=2;
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}
    voisin=&compte_voisins_vivants;
    fage=vieillir_cel_null;
	grille g, gc;
	init_grille_from_file("grille1.txt",&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	affiche_grille(g);

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
