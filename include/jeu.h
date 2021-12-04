/**
 * \file
 * header pour la fonction d'évolution
 *\author Redha Bouzidi
 */
#ifndef __JEU_H
#define __JEU_H
#include "grille.h"

/**
*\fn static inline int modulo(int i, int m)
*\param i int
*\param m int
* \return int la valeure absolu de i modulo m
* modulo modifié pour traiter correctement les bords i=0 et j=0
* dans le calcul des voisins avec bords cycliques
*/
static inline int modulo(int i, int m) {return (i+m)%m;}

int test_oc(grille g);

int test_eg(grille g,grille gc);

void vieillir_cel(grille* g);

int compte_voisins_vivants (int i, int j, grille g);

int compte_voisins_vivants_nc (int i, int j, grille g);

void evolue (grille *g, grille *gc);
/** Variable globale deffinissant le pas de l'oscillation */
extern int pas_oc;
/** Variable globale deffinissant le delai de l'oscillation */
extern int delai_oc;
#endif
