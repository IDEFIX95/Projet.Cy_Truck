// ETAPE 1 : Le Filtrage

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETAPE1_FILTRAGE_H
#define ETAPE1_FILTRAGE_H

#define BUFFER_SIZE 4096  // Augmenter la taille du tampon

// Initialisation de la strcuture pour pouvoir 
struct Statistique {
    int id;
    float min;
    float max;
    float somme;
    int compteur;
    float moyenne;
    float difference;
};

// Fonction de filtrage et écriture dans un fichier de sortie
int filtrageEtEcriture();

#endif
