/**
 * \file grille.c
 * code pour la grille
 *\author Redha Bouzidi
 */
#include "grille.h"
/**
*\relatesalso grille
*\param *filename char le nom du fichier
*\param *g grille
*\return \c void charge les valeur du fichier dans la grille
*/
/** alloue et initalise la grille g à partir d'un fichier */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);

	int i,j,n,l,c,vivantes=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fclose (pfile);
	return;
}

/**
*\relatesalso grille
*\param *gs grille
*\param *gd grille
*\return \c void recopie gs dans gd (sans allocation) */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i)
    {
        for (j=0; j<gs.nbc; ++j){
                gd.cellules[i][j] = gs.cellules[i][j];

        }
    }
	return;
}
/**
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return \c void crée une grille initialisé a 0
*/
void alloue_grille(int l,int c, grille *g){
    int i,j;
    g->nbc=c;
    g->nbl=l;
    g->cellules=malloc(sizeof(int*)*(l));
for ( i=0;i<g->nbl;i++){
    g->cellules[i]=malloc(sizeof(int*)*c);
    for( j=0;j<g->nbc;j++){
    g->cellules[i][j]=0;
    }
}
}
/**
*\relatesalso grille
*\param *g grille
*\return \c void libére la grille
*/
void libere_grille (grille* g){
int i;

    for(i=0;i<g->nbl;i++){
        free(g->cellules[i]);
    }
    g->nbc=0;
    g->nbl=0;
    free(g->cellules);
}


