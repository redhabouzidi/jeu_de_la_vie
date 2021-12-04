/**
 * \file io.c
 * code pour l'affichage et les choix
 *\author Redha Bouzidi
 */
#include "../include/io.h"
/**
*\fn void affiche_trait (int c)
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
*\fn void affiche_ligne (int c, int* ligne)
*\param l int nombre de lignes
*\param ligne* int tableau d'entiers
*\return \c void affiche les cellules vivantes ainsi que les lignes du tableau*/
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i){
		if (ligne[i] == 0 ){
            printf ("|   ");
        } else if(ligne [i]== -1){
		printf ("| X ");
        }else{
		printf ("| O ");
        }
	}
	printf("|\n");
	if(fage!=NULL){
	for (i=0; i<c; ++i){
		if (ligne[i] == 0 || ligne[i]== -1 ){
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
*\fn void affiche_grille (grille g)
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
	if(fage==NULL)
		printf("Vieillissement : OFF\n");
	else
		printf("Vieillissement : ON\n");
	
	if(voisin==compte_voisins_vivants)
		printf("Cyclique : ON\n");
	else
		printf("Cyclique : OFF\n");
	
		if(pas_oc==0){
		printf("Appuyez sur O pour test l'oscillation\n");
		}else if(pas_oc!=-1){
		printf("Le pas est de : %d ",pas_oc);
		if(delai_oc!=0)
			printf("et le delai est de  : %d",delai_oc);
		}else
		printf("La fonction n'ocille pas");
		
	
	return;
}	

/** effacement d'une grille*/
void efface_grille (grille g){
    system("clear ");
}
/**
*\fn void debut_jeu(grille *g, grille *gc)
*\relatesalso grille
*\param *gc grille copie
*\param *g grille
*/
void debut_jeu(grille *g, grille *gc){
	char vide;
	char c = getchar();
	if(c!='\n'){
		do{
		vide=getchar();
		}while(vide!='\n');
		}
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				printf("yo");
				evolue(g,gc);
				ageevo++;
				break;
			}
			case 'c':{
                if(voisin==&compte_voisins_vivants){
                    voisin=&compte_voisins_vivants_nc;
                }else{
                voisin=&compte_voisins_vivants;
                }
                break;
			}
			case 'v':{
                if(fage==NULL){
                    fage=&vieillir_cel;
                }else{
                fage=NULL;
                }
                break;
			}
			case 'n':{
			pas_oc=0;
			delai_oc=0;
			ageevo=0;
			libere_grille(g);
			libere_grille(gc);

			char string[255];
			scanf("%s",string);
			do{
			vide=getchar();
			}while(vide!='\n');
		
			init_grille_from_file(string,g);
			alloue_grille(g->nbl,g->nbc,gc);
			break;

			}
			case 'o':{
			test_oc(*g);
			break;
			
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		efface_grille(*g);
		affiche_grille(*g);
		c = getchar();
		if(c!='\n'){
		do{
		vide=getchar();
		}while(vide!='\n');
		}
		
	}
	return;
}

