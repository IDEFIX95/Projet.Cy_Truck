#ifndef ETAPE1_FILTRE_H
#define ETAPE1_FILTRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024
#define FICHIER_ENTREE "data/data1.csv"
#define FICHIER_SORTIE "temp/fichier_col4.csv"

// Utilisation d'un ABR pour filtrer car il y a des doublons dans le fichier data.csv (comme MARSEILLE;MARSEILLE ou MARSEILLE peut apparaître plusieurs fois dans un même ID)
typedef struct ABR {
    char *ville;
    char *ID;
    struct ABR *fg;
    struct ABR *fd;
} ABR, *pABR;

pABR creerarbre(char *ID, char *ville);
pABR insertABR(pABR a, char *ID, char *ville);
void parcours(pABR a, FILE *fichier);
void copierdonnee(pABR *a, FILE *fichierEntree);
void libererABR(pABR a);

int main(int argc, char *argv[]);

#endif