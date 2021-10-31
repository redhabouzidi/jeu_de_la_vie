/**
 * \file io.c
 * code pour l'affichage et les choix
 *\author Redha Bouzidi
 */
#include "io.h"
/**
*\param c int nombre de colonnes
return \c void affiche les traits du tableau
*/
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/**
*\param l int nombre de lignes
*\param ligne* int tableau d'entiers
*\return \c void affiche les cellules vivantes ainsi que les lignes du tableau*/
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i){
		if (ligne[i] == 0 ){
            printf ("|   ");
        } else {

            printf ("| O ");
        }
	}
	printf("|\n");
	if(fage!=NULL){
	for (i=0; i<c; ++i){
		if (ligne[i] == 0 ){
            printf ("|   ");
        } else {

            printf ("| %d ",ligne[i]-1);
        }
	}
	printf("|\n");
	}

	return;
}
/**
*\relatesalso grille
*\param g grille
*\return \c void affiche la grille*/
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\nAge grille:%d",ageevo);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

/** effacement d'une grille*/
void efface_grille (grille g){
    system("clear ");
}
/**
*\relatesalso grille
*\param *gc grille copie
*\param *g grille
*/
void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				ageevo++;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'c':{
                if(voisin==&compte_voisins_vivants){
                    voisin=&compte_voisins_vivants_nc;
                }else{
                voisin=&compte_voisins_vivants;
                }
                fflush(stdin);
                break;
			}
			case 'v':{
                if(fage==NULL){
                    fage=&vieillir_cel;
                }else{
                fage=NULL;
                }
                fflush(stdin);
                break;
			}
			case 'n':{
			    ageevo=0;
			    libere_grille(g);
			    libere_grille(gc);

            char string[15];
            scanf("%s",string);
			init_grille_from_file(string,g);
			alloue_grille(g->nbl,g->nbc,gc);
			system("cls");
			affiche_grille(*g);
			fflush(stdin);
			break;

			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
