/**
 * \file
 * header pour les fonctions d'affichage et de choix
 *\author Redha Bouzidi
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"



void affiche_trait (int c);


void affiche_ligne (int c, int* ligne);


void affiche_grille (grille g);

void efface_grille (grille g);


void debut_jeu(grille *g, grille *gc);

#endif
