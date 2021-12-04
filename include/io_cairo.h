/**
 * \file
 * header pour les fonctions d'affichage et de choix
 *\author Redha Bouzidi
 */
#ifndef __IO_CAIRO_H
#define __IO_CAIRO_H
#include </usr/include/cairo/cairo.h>
#include </usr/include/cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include "grille.h"
#include "jeu.h"

void affiche_trait (int c,int j,cairo_t *cr);


void affiche_ligne (int c,int j, int* ligne,cairo_t *cr);


void affiche_grille (grille g);

void efface_grille (grille g);


void debut_jeu(grille *g, grille *gc);

#endif
