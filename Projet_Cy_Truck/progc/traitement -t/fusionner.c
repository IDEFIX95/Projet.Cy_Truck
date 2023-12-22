#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024
#define FICHIER_SORTIE "fichier_sortie.csv"
#define FICHIER_TRAITAGE "fichier_traitage.csv"


void fusionner(FILE *fichierEntree, FILE *fichierSortie) {
    char buffer[TAILLE_BUFFER];
    int isFirstLine = 1; 

    // Écrire d'abord toutes les données de la colonne 2
    rewind(fichierEntree); // Retourner au début du fichier d'entrée
    
    while (fgets(buffer, sizeof(buffer), fichierEntree) != NULL) {
        if (isFirstLine) {
            isFirstLine = 0; 
            continue; 
        }
        char *token = strtok(buffer, ";");
        int colonne = 1;

        while (token != NULL) {
            if (colonne == 1){
                fprintf(fichierSortie, "%s;", token);
            }
            if (colonne == 2) {
                fprintf(fichierSortie, "%s\n", token);
                break; // Sortir de la boucle une fois la colonne 2 traitée
            }
            token = strtok(NULL, ";");
            colonne++;
        }
    }

    // Écrire ensuite toutes les données de la colonne 3 juste en dessous
    rewind(fichierEntree); // Retourner au début du fichier d'entrée
    isFirstLine = 1; 
    while (fgets(buffer, sizeof(buffer), fichierEntree) != NULL) {
        if (isFirstLine) {
            isFirstLine = 0;  
            continue;  
        }
        char *token = strtok(buffer, ";");
        int colonne = 1;

        while (token != NULL) {
            if (colonne == 1){
                fprintf(fichierSortie, "%s;", token);
            }
            if (colonne == 3) {
                fprintf(fichierSortie, "%s", token);
                break; // Sortir de la boucle une fois la colonne 3 traitée
            }
            token = strtok(NULL, ";");
            colonne++;
        }
    }
}

int main() {
    FILE *fichier2, *fichier3;



    // Ouvrir le fichier de sortie en mode écriture
    fichier2 = fopen(FICHIER_SORTIE, "r");
    if (fichier2 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie '%s'\n", FICHIER_SORTIE);
        return 1;
    }

    fichier3 = fopen(FICHIER_TRAITAGE, "w");
    if (fichier3 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de traitage '%s'\n", FICHIER_TRAITAGE);
        fclose(fichier2);
        return 1;
    }

    fusionner(fichier2, fichier3);


    if (fclose(fichier2) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier de sortie '%s'\n", FICHIER_SORTIE);
    }
    if (fclose(fichier3) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier de traitage '%s'\n", FICHIER_TRAITAGE);
    }

    printf("Traitement terminé avec succès.\n");

    return 0;
}