// ÉTAPE 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETAPE4_TRIERSOMME_H
#define ETAPE4_TRIERSOMME_H

#define TAILLE_BUFFER 1024

// Utilisation pour trier des sommes des villes

typedef struct AVL {
    char ville[TAILLE_BUFFER];
    int somme;
    struct AVL *fg;
    struct AVL *fd;
    int h;
} Arbre, *pArbre;

int max(int a, int b);
int min(int a, int b);
pArbre rotationGauche(pArbre a);
pArbre rotationDroite(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre doubleRotationDroite(pArbre a);
pArbre equilibrerAVL(pArbre a);
pArbre creerNoeud(int somme, char *ville);
pArbre insertionAVL(pArbre x, int e, char *c, int *h);
void ResultatSomme(pArbre *a, FILE *fichier);
void parcoursDecroissant(pArbre a, FILE *fichierSortie);
void libererAVL(pArbre a);

#endif
