/**
 * \file io.c
 * code pour l'affichage et les choix
 *\author Redha Bouzidi
 */
#include "../include/io.h"
#include </usr/include/cairo/cairo.h>
#include </usr/include/cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#define SIZEX 6000
#define SIZEY 10000
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
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
			paint(cs);

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return ;
}
void paint(cairo_surface_t *surface)
{
	int i=0,j=0,l=10,c=10;
	// create cairo mask
	cairo_t *dr[l][c];
	dr[i][j]=cairo_create(surface);
	
	// background
	cairo_set_source_rgb (dr[i][j], 0.0, 0.0, 0.0);
	cairo_paint(dr[i][j]);
	
	// line
	
	
	

	// filled rectangle // destroy cairo mask
	for(i=0;i<l;i++){
	for(j=0;j<c;j++){
	dr[i][j]=cairo_create(surface);
	cairo_rectangle(dr[i][j],(10+60*i),(10+60*j),50,50);
	cairo_set_source_rgb (dr[i][j], 0, 0, 1);
	cairo_fill(dr[i][j]);	
	cairo_destroy(dr[i][j]);
	}
	}
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
