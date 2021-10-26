#include "jeu.h"
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
void vieillir_cel(int l,int c,grille* g){

		    if(g->cellules[l][c]>0){
                g->cellules[l][c]++;
		    }if(g->cellules[l][c]==10){
                g->cellules[l][c]=0;
		    }

}
void vieillir_cel_null(int l,int c,grille* g){
}
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


void evolue (grille *g, grille *gc){

	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{

		    (*fage)(i,j,g);
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
	return;
}
