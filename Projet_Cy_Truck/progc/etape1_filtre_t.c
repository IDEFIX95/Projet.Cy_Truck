// ÉTAPE 1

// Ce programme permet d'extraire la colonne 4 du fichier "data.csv" vers un autre fichier afin de travailler sur le nombre de trajets des villes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024
#define FICHIER_ENTREE "data/data1.csv"
#define FICHIER_SORTIE "temp/fichier_col4.csv"
#include "etape1_filtre_t.h"

pABR creerarbre(char *ID, char *ville) {
    ABR *new = malloc(sizeof(*new));
    if (new == NULL) {
        printf("Erreur d'allocation dans creerarbre pour ID: %s, ville: %s\n", ID, ville);
        exit(EXIT_FAILURE);
    }

    // Utiliser strdup pour allouer et copier la chaîne
    new->ID = strdup(ID);
    if (new->ID == NULL) {
        printf("Erreur d'allocation pour ID: %s\n", ID);
        free(new);
        exit(EXIT_FAILURE);
    }
    new->ville = strdup(ville);
    if (new->ville == NULL) {
        printf("Erreur d'allocation pour ville: %s\n", ville);
        free(new->ID);
        free(new);
        exit(EXIT_FAILURE);
    }

    new->fd = new->fg = NULL;
    return new;
}



pABR insertABR(pABR a, char *ID, char* ville){
    if (a == NULL){
        a = creerarbre(ID,ville);
    } 
    else { // Condition d'ajoutement en fonction d'ID et de la ville pour enlever les villes qui apparaissent deux fois dans un même trajet
        int compareID = strcmp(ID, a->ID);
        if (compareID < 0){
            a->fg = insertABR(a->fg,ID,ville);
        } 
        else if (compareID > 0){
            a->fd = insertABR(a->fd,ID,ville);
        } 
        else {
            int compareville = strcmp(ville, a->ville);
            if (compareville < 0){
                a->fg = insertABR(a->fg, ID, ville);
            } 
            else if (compareville > 0){
                a->fd = insertABR(a->fd, ID, ville);
            } 
            else {
                // Même ID et même ville, on l'ignore
                return a;
            }
        }
    }
    return a;
}

// Fonction pour écrire la colonne 4 filtrée dans le fichier ficher_col4.csv
void parcours(pABR a, FILE *fichier) {
    if (a != NULL) {
        parcours(a->fd, fichier);
        fprintf(fichier, "%s\n", a->ville);
        parcours(a->fg, fichier);
    } 
}

// Fonction pour filtrer les doublons comme MARSEILLE;MARSEILLE et inserer la colonne 4 dans l'ABR.
void copierdonnee(pABR *a, FILE *fichierEntree) {
    char buffer[TAILLE_BUFFER];
    int isFirstLine = 1; 
    while (fgets(buffer, sizeof(buffer), fichierEntree) != NULL) {
        // Ignore la premiere ligne
        if (isFirstLine) {
            isFirstLine = 0;  
            continue;  
        }

        char *token = strtok(buffer, "\n");

        while (token != NULL){
            char *token2 = strtok(token,";");
            int colonne = 1;
            char tempcol1[TAILLE_BUFFER];
            char tempcol3[TAILLE_BUFFER];
            char tempcol4[TAILLE_BUFFER];
            while (token2 != NULL){
                if (colonne == 1){
                    strcpy(tempcol1,token2);
                } else if (colonne == 3){
                    strcpy(tempcol3,token2);
                } else if (colonne == 4){
                    strcpy(tempcol4,token2);
                    if (strcmp(tempcol4,tempcol3) != 0){
                    *a = insertABR(*a,tempcol1,tempcol4);
                    }
                } 
                token2 = strtok(NULL, ";");
                colonne++;
            }
            token = strtok(NULL, "\n");
        }

    }
}

// Fonction pour libérer l'arbre
void libererABR(pABR a) {
    if (a != NULL) {
        libererABR(a->fg);
        libererABR(a->fd);
        free(a);
    }
}


int main(int argc, char* argv[]) {
    FILE *fichier1, *fichier2;
    pABR a = NULL;
    if(argc==1){
        printf("Il y a le bon nombre d'argument de la ligne de commande est correct donc le chemin vers le fichier data '%s' est present.", argv[1]);
    }
    // Ouvrir le fichier d'entrée en mode lecture
    fichier1 = fopen(argv[1], "r");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier d'entrée '%s'\n", argv[1]);
        return 1;
    }

    // Ouvrir le fichier de sortie en mode écriture
    fichier2 = fopen(FICHIER_SORTIE, "w");
    if (fichier2 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie '%s'\n", FICHIER_SORTIE);
        fclose(fichier1);
        return 1;
    }


    copierdonnee(&a, fichier1); // Extraire et filtrer la colonne 4
    parcours(a,fichier2); // Importer la colonne filtrée dans le fichier_col4.csv
    libererABR(a); // Liberer l'arbre
    

    // Fermer les fichiers
    if (fclose(fichier1) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier d'entrée '%s'\n", FICHIER_ENTREE);
    }
    if (fclose(fichier2) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier de sortie '%s'\n", FICHIER_SORTIE);
    }


    printf("Traitement de l'étape 1 terminé avec succès.\n");

    return 0;
}
