/**
 * \file io.c
 * code pour l'affichage et les choix
 *\author Redha Bouzidi
 */
#include "../include/io_cairo.h"
#include "string.h"
cairo_surface_t *cs;
/**
*\fn void affiche_trait (int c)
*\param c int nombre de colonnes
return \c void affiche les traits du tableau
*/
void affiche_trait (int c,int j,cairo_t *cr){
	int i;
	for (i=0; i<c; ++i) {
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
	cairo_rectangle(cr,(10+60*i),(100+60*j),50,50);
	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_fill(cr);
        }else if(ligne[i]>=1){
	cairo_rectangle(cr,(10+60*i),(100+60*j),50,50);
	cairo_set_source_rgb (cr, 1.0, 1.0, 0.0);
	cairo_fill(cr);
        }else if(ligne[i]==0){
        cairo_rectangle(cr,(10+60*i),(100+60*j),50,50);
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
	cairo_fill(cr);
        }
	}


	return;
}
/**
*\fn void affiche_grille (grille g)
*\relatesalso grille
*\param g grille
*\return \c void affiche la grille*/
void affiche_grille (grille g){
int i,j,test;
	cairo_t *cr;
	cr=cairo_create(cs);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0,0.0);
	cairo_paint(cr);

	for(i=0;i<g.nbl;i++){
		affiche_trait(g.nbc,i,cr);
		affiche_ligne(g.nbc,i,g.cellules[i],cr);

	}
	cairo_rectangle(cr,0,0,300,50);
	cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
	cairo_fill(cr);

	cairo_rectangle(cr,(30+60*g.nbc),170,250,50);
	cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
	cairo_fill(cr);

	cairo_rectangle(cr,(30+60*g.nbc),270,200,50);
	cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
	cairo_fill(cr);
	cairo_set_source_rgb(cr,0.0, .0, 0.0 );

	cairo_select_font_face(cr, "Cairo Regular",
	CAIRO_FONT_SLANT_NORMAL,
	CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 18);
	cairo_move_to(cr, 20, 30);
	char c[128];
	char d[128]="Temps d'evolution : ";
	sprintf(c,"%d",ageevo);
    	strcat(d,c);
	cairo_show_text(cr, d);
	cairo_move_to(cr, 40+60*g.nbc, 200);
	if(fage==NULL)
		cairo_show_text(cr, "vieillissement: off");
	else
		cairo_show_text(cr, "vieillissement: on");
	cairo_move_to(cr, 40+60*g.nbc, 300);
	if(voisin==&compte_voisins_vivants)
		cairo_show_text(cr, "Cyclique: on");
	else
		cairo_show_text(cr, "Cyclique: off");

	if(foc!=NULL){
	if((*foc)(g)){
	cairo_rectangle(cr,(350),0,450,50);
	cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
	cairo_fill(cr);
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_select_font_face(cr, "Cairo Regular",
	CAIRO_FONT_SLANT_NORMAL,
	CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 18);
	cairo_move_to(cr, 370, 30);
	strcpy(d,"Le pas est de : ");
	sprintf(c,"%d",pas_oc);
    	strcat(d,c);
    	strcat(d," Et le délais est de : ");
    	sprintf(c,"%d",delai_oc);
    	strcat(d,c);
	cairo_show_text(cr, d);

	}
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
	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, g->nbc*60+600, g->nbl*60+120, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));
	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, KeyPressMask|ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);

	// create cairo surface
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0),g->nbc*60+600 , g->nbl*60+120);
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
		}else if(e.xkey.keycode==32){
		c='o';
		}else{
		c='\0';
		}
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
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

		char buffer[8];
            KeySym key;
            char string[255]="";
            cairo_surface_destroy(cs);
            int i=0;

            XSelectInput(dpy, win, KeyPressMask|ExposureMask|ButtonPressMask);
            cairo_t *cr;
            cr=cairo_create(cs);
            cairo_set_source_rgb (cr, 1.0, 1.0,1.0);
            cairo_paint(cr);
            cairo_rectangle(cr,20,20,g->nbl*60+260,50);
            cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
            cairo_fill(cr);
            	while(e.xkey.keycode!=36){
            	XNextEvent(dpy, &e);
            	XLookupString(&e.xkey, buffer, sizeof(buffer), &key, NULL);


		// background





        if(key==65288){
        if(i!=0){
        i--;
        string[i]='\0';
        }
        }else if(key<150){
        string[i]=key;
        i++;
        }
        cairo_set_source_rgb (cr, 1.0, 1.0,1.0);
		cairo_paint(cr);
		cairo_rectangle(cr,20,20,g->nbl*60+260,50);
		cairo_set_source_rgb (cr, 0.5, 0.0, 0.5);
		cairo_fill(cr);
        cairo_select_font_face(cr, "Cairo Regular",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
		cairo_set_font_size(cr, 18);
        cairo_move_to(cr, 40, 50);
        cairo_show_text(cr, string);
            }
            		ageevo=0;
			libere_grille(g);
			libere_grille(gc);
			init_grille_from_file(string,g);
			alloue_grille(g->nbl,g->nbc,gc);
			XCloseDisplay(dpy);
			if(!(dpy=XOpenDisplay(NULL))) {
            fprintf(stderr, "ERROR: Could not open display\n");
            exit(1);
            }
            scr=DefaultScreen(dpy);
            rootwin=RootWindow(dpy, scr);
            win=XCreateSimpleWindow(dpy, rootwin, 1, 1, g->nbc*60+600, g->nbl*60+120, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));
            XStoreName(dpy, win, "jeu de la vie");
            XSelectInput(dpy, win, KeyPressMask|ExposureMask|ButtonPressMask);
            XMapWindow(dpy, win);

            // create cairo surface
            cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0),g->nbc*60+600 , g->nbl*60+120);

			affiche_grille(*g);
			fflush(stdin);
			break;

			}
			case 'o':{
				if(foc==NULL)
				foc=&test_oc;
			else
				foc=NULL;
			}
			default :
			{ // touche non traitée
			break;
			}
		}
		cairo_surface_destroy(cs);

	}
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return;
}
