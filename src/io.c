/**
 * \file io.c
 * code pour l'affichage et les choix
 *\author Redha Bouzidi
 */
#include "../include/io.h"
#define SIZEX 1000
#define SIZEY 1000
cairo_surface_t *cs;
/**
*\fn void affiche_trait (int c)
*\param c int nombre de colonnes
return \c void affiche les traits du tableau
*/
void affiche_trait (int c,int j,cairo_t *cr){
	int i;
	for (i=0; i<c; ++i) {
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr,(60*j),(60*i),70,70);
	cairo_set_line_width (cr, 10);
	}
	
	return;
}
/**
*\fn void affiche_ligne (int c, int* ligne)
*\param l int nombre de lignes
*\param ligne* int tableau d'entiers
*\return \c void affiche les cellules vivantes ainsi que les lignes du tableau*/
void affiche_ligne (int c,int j, int* ligne,cairo_t *cr){
	int i;
	for (i=0; i<c; ++i){
		if(ligne [i]== -1){
	cairo_rectangle(cr,(10+60*j),(10+60*i),50,50);
	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_fill(cr);
        }else if(ligne[i]>=1){
	cairo_rectangle(cr,(10+60*j),(10+60*i),50,50);
	cairo_set_source_rgb (cr, 1.0, 1.0, 0.0);
	cairo_fill(cr);
        }
	}
	printf("|\n");
	if(fage!=NULL){
	for (i=0; i<c; ++i){
		if (ligne[i] <= 0 ){
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
int i,j;
	cairo_t *cr;
	cr=cairo_create(cs);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	for(i=0;i<g.nbl;i++){
		affiche_trait(g.nbc,i,cr);
		affiche_ligne(g.nbc,i,g.cellules[i],cr);
		
	}
	return ;
}

/** effacement d'une grille*/
void efface_grille (grille g){

}
/**
*\fn void debut_jeu(grille *g, grille *gc)
*\relatesalso grille
*\param *gc grille copie
*\param *g grille
*/
void debut_jeu(grille *g, grille *gc){
	char c;
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
	XSelectInput(dpy, win, KeyPressMask|ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);
	affiche_grille(*g);
	while(1){	
	affiche_grille(*g);
		XNextEvent(dpy, &e);
		if(e.xkey.keycode==36){
		c='\n';
		}else if(e.xkey.keycode==54){
		c='c';
		}else if(e.xkey.keycode==55){
		c='v';
		}
		else if(e.xkey.keycode==38){
		break;
		}else if(e.xkey.keycode==57){
		c='n';
		}else{
		c='\0';
		}
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				ageevo++;
				e.xkey.keycode=0;
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
            		char string[20];
            		scanf("%s",string);
			init_grille_from_file(string,g);
			alloue_grille(g->nbl,g->nbc,gc);
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
		cairo_surface_destroy(cs);

	}
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return;
}
