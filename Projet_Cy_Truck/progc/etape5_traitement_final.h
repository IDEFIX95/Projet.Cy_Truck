// ÉTAPE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef ETAPE5_TRAITEMENT_FINAL_H
#define ETAPE5_TRAITEMENT_FINAL_H

#define TAILLE_BUFFER 2048

typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    int temp;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;

// Structure pour stocker une ligne de données
typedef struct lignes {
    char col1[TAILLE_BUFFER];
    int col2;
    int col3;
} lignes;

int compareCol2(const void *a, const void *b);
pABR creerchainon(char *c, int e);
pABR insertionABR(pABR a, char *c, int e);
void parcoursdecroissant(pABR a, FILE *fichier);
void traiterfichier(pABR *a, FILE *fichier);
void libererABR(pABR a);

#endif
