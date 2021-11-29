/**
 * \file jeu.c
 * code pour la fonctionalité de jeu
 *\author Redha Bouzidi
 */
#include "../include/jeu.h"
/**
*\fn int compte_voisins_vivants (int i, int j, grille g)
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return int compte le nombre de voisins vivants de la cellule (i,j)
* les bords sont cycliques.
*/

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v;
}
/**
*\fn void vieillir_cel(grille* g)
*\relatesalso grille
*\param *g grille
\return \c void incremente les cellules vivantes et les remets a 0 quand elles dépassent l'age 8
*/
int grille_vide(grille g){
	int i,j;
	for(i=0;i<g.nbl;i++){
		for(j=0;j<g.nbl;j++){
		if(est_vivante(i,j,g))
		return 0;
		}
	}
	return 1;
}
int test_oc(grille g){
	int i,j;
	grille gc;
	alloue_grille (g.nbl, g.nbc, &gc);
	grille gc1;
	alloue_grille (g.nbl, g.nbc, &gc1);
	grille gi;
	alloue_grille (g.nbl, g.nbc, &gi);
	copie_grille (g,gc);
	for(i=0;i<100;i++){
		copie_grille (gc,gc1);
		for(j=0;j<100;j++){
		evolue(&gc1,&gi);
		if(grille_vide(gc1))
			break;
		
		if(test_eg(gc,gc1)){
			pas_oc=j;
			delai_oc=i;
		return 1;
		}
		
	
		}
	evolue(&gc,&gi);
	if(grille_vide(gc))
			break;
	
	}
	delai_oc=-1;
	pas_oc=-1;
	return 0;
}

void vieillir_cel(grille* g){
int l,c;
    for(l=0;l<g->nbl;l++){
            for(c=0;c<g->nbc;c++){
		    if(g->cellules[l][c]>0){
                g->cellules[l][c]++;
		    }if(g->cellules[l][c]==10){
                g->cellules[l][c]=0;
		    }
		    }
        }
}

/**
*\fn int compte_voisins_vivants_nc (int i, int j, grille g)
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return int compte le nombre de voisins vivants de la cellule (i,j)
* les bords ne sont pas cycliques.
*/
int compte_voisins_vivants_nc (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	if(i+1==l){
    if(j+1==c){
    v+= est_vivante(i-1,j-1,g);
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i,j-1,g);
    }else if(j==0){
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i-1,j+1,g);
	v+= est_vivante(i,j+1,g);
    }else{
    v+= est_vivante(i-1,j-1,g);
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i-1,j+1,g);
	v+= est_vivante(i,j-1,g);
	v+= est_vivante(i,j+1,g);
    }
    }else if(i==0){
	if(j+1==c){
    v+= est_vivante(i,j-1,g);
	v+= est_vivante(i+1,j-1,g);
	v+= est_vivante(i+1,j,g);
	}else if(j==0){
	v+= est_vivante(i,j+1,g);
	v+= est_vivante(i+1,j,g);
	v+= est_vivante(i+1,j+1,g);
	}else{
	v+= est_vivante(i,j-1,g);
	v+= est_vivante(i,j+1,g);
	v+= est_vivante(i+1,j-1,g);
	v+= est_vivante(i+1,j,g);
	v+= est_vivante(i+1,j+1,g);
	}
    }else if(j+1==c){
    v+= est_vivante(i-1,j-1,g);
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i,j-1,g);
	v+= est_vivante(i+1,j-1,g);
	v+= est_vivante(i+1,j,g);
    }else if(j==0){
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i-1,j+1,g);
	v+= est_vivante(i,j+1,g);
	v+= est_vivante(i+1,j,g);
	v+= est_vivante(i+1,j+1,g);
    }else{
	v+= est_vivante(i-1,j-1,g);
	v+= est_vivante(i-1,j,g);
	v+= est_vivante(i-1,j+1,g);
	v+= est_vivante(i,j-1,g);
	v+= est_vivante(i,j+1,g);
	v+= est_vivante(i+1,j-1,g);
	v+= est_vivante(i+1,j,g);
	v+= est_vivante(i+1,j+1,g);

	}
	return v;
}

int test_eg(grille g,grille gc){
	int i,j,r=0;
	for(i=0;i<g.nbl;i++){
		for(j=0;j<g.nbc;j++){
		if(est_vivante(i,j,g)){
			if(est_vivante(i,j,gc)){
				r=1;
			}else{
			return 0;
			}
		}
		if(est_vivante(i,j,gc)){
			if(!est_vivante(i,j,g)){
			return 0;
			}
		}
		}
	}
	return r;
}


/**
*\fn void evolue (grille *g, grille *gc)
*\relatesalso grille
*\param *gc grille copie
*\param *g grille
*\return \c void avance dans l'age de la grille
*/

void evolue (grille *g, grille *gc){

	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;

	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{


			v = (*voisin)(i, j, *gc);
			if (est_vivante(i,j,*g))
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	if(fage!=NULL){
	(*fage)(g);}
	return;
}
