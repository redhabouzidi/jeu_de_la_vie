/**
 * \file
 * header pour la grille
 *\author Redha Bouzidi
 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/**
*\struct grille
*Declaration de la structure de grille
*/
typedef struct {int nbl; int nbc; int** cellules;} grille;


void alloue_grille (int l, int c, grille* g);

void libere_grille (grille* g);

void init_grille_from_file (char * filename, grille* g);

/**
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return \c void met la case [i][j] a 1
*/
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
/**
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return \c void met la case [i][j] a 0
*/
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
/**
*\relatesalso grille
*\param l int nombre de lignes
*\param c int nombre de colonnes
*\param *g grille
*\return \c void teste si la cellule (i,j) de la grille g est vivante */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] != 0;}


void copie_grille (grille gs, grille gd);
/** Variable globale permetant d'activer ou de désactiver le voisinage cyclique */
int (*voisin) (int, int, grille);
/** Variable globale permetant d'activer ou de désactiver le vieillissement */
void (*fage)(grille*);
/** Variable globale permetant d'incrementer le temps d'évolution */
int ageevo;
#endif
