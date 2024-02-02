// Etape 2 : trie final

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETAPE2_TRIE_FINAL_H
#define ETAPE2_TRIE_FINAL_H

#define TAILLE_BUFFER 4096

// Définition de la structure d'un arbre AVL
typedef struct AVL {
    int id;
    float dist_min;
    float dist_max;
    float dist_moy;
    float diff;
    struct AVL *fg;  // Fil gauche
    struct AVL *fd;  // Fil droit
    int h;           // Hauteur
} Arbre, *pArbre;

// Fonction utilitaire pour obtenir le maximum de deux entiers
int max(int a, int b);

// Fonction utilitaire pour obtenir le minimum de deux entiers
int min(int a, int b);

// Rotation simple à gauche pour rééquilibrer l'arbre AVL
pArbre rotationGauche(pArbre a);

// Rotation simple à droite pour rééquilibrer l'arbre AVL
pArbre rotationDroite(pArbre a);

// Rotation double à gauche (gauche-droite) pour rééquilibrer l'arbre AVL
pArbre doubleRotationGauche(pArbre a);

// Rotation double à droite (droite-gauche) pour rééquilibrer l'arbre AVL
pArbre doubleRotationDroite(pArbre a);

// Fonction pour rééquilibrer l'arbre AVL en fonction de la hauteur des sous-arbres
pArbre equilibrerAVL(pArbre a);

// Fonction pour créer un nouveau nœud avec allocation dynamique de mémoire
pArbre creerNoeud(int id, float diff, float max, float min, float moy);

// Fonction pour effectuer l'insertion d'un nœud dans l'arbre AVL
pArbre insertionAVL(pArbre x, int id, float diff, float max, float min, float moy, int *h);

// Fonction pour extraire la 5ème colonne d'un fichier CSV et l'insérer dans l'arbre AVL
void extrairecol5(pArbre *a, FILE *fichier);

// Fonction pour parcourir l'arbre AVL de manière décroissante et écrire les résultats dans un fichier
void parcoursDecroissant(pArbre a, FILE *fichierSortie, int *i, const int lim);

// Fonction pour libérer la mémoire allouée pour l'arbre AVL
void libererAVL(pArbre a);

// Fonction principale pour le tri final
int trierEtEcrire();

#endif
