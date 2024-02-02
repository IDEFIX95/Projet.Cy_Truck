// ÉTAPE 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETAPE6_PARCOURS_DECROISSANT_ALPHABETIQUE_H
#define ETAPE6_PARCOURS_DECROISSANT_ALPHABETIQUE_H

// Structure pour stocker les enregistrements du fichier CSV
struct Record {
    char nom[100];
    int col1;
    int col2;
};

// Fonction de comparaison pour qsort, triant les enregistrements par ordre alphabétique du champ 'nom'
int compare(const void *a, const void *b);

#endif
