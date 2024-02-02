// ÉTAPE 2

// Ce programme permet d'extraire les colonnes 2 et 3 du fichier "data.csv" vers un autre fichier afin de travailler sur le nombre de trajets des villes de départ.

#ifndef ETAPE2_ISO_COL2_3_H
#define ETAPE2_ISO_COL2_3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024
#define FICHIER_ENTREE "data/data.csv"
#define FICHIER_SORTIE "temp/fichier_col2_3.csv"

void copierdonnee(FILE *fichierEntree, FILE *fichierSortie);

#endif
