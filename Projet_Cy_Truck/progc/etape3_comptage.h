// ÉTAPE 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETAPE3_COMPTAGE_H
#define ETAPE3_COMPTAGE_H

#define TAILLE_BUFFER 1024

// Utilisation d'un ABR pour additionner le nombre de villes

typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;

pABR creerchainon(char *c);
pABR insertionABR(pABR a, char *c);
void parcoursdecroissant(pABR a, FILE *fichier);
void ExtraireVilleDarrive(pABR *a, FILE *fichier1);
void ExtraireLignesDuCol2et3(pABR *a, FILE *fichier2);
void libererABR(pABR a);

#endif
