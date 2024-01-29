// CE PROGRAMME PERMET D'EXTRAIRE DES COLONNES 2 ET 3 DU FICHIER "DATA.CSV" VERS UN AUTRE FICHIER AFIN DE TRAIVAILLER SUR LE NOMBRE DE TRAJETS DES VILLES DE DÉPART.
// ÉTAPE 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024
#define FICHIER_ENTREE "data/data.csv"
#define FICHIER_SORTIE "temp/fichier_col2_3.csv"

void copierdonnee(FILE *fichierEntree, FILE *fichierSortie) {
    char buffer[TAILLE_BUFFER];

    while (fgets(buffer, sizeof(buffer), fichierEntree) != NULL) {
        char *token = strtok(buffer, ";");
        int colonne = 1;

        while (token != NULL) {
            if (colonne == 2 || colonne == 3) {
                fprintf(fichierSortie, "%s", token);

                if (colonne < 3) {
                    fprintf(fichierSortie, ";");
                }
            }
            token = strtok(NULL, ";");
            colonne++;
        }
        fprintf(fichierSortie, "\n");
    }
}


int main() {
    FILE *fichier1, *fichier2;

    // Ouvrir le fichier d'entrée en mode lecture
    fichier1 = fopen(FICHIER_ENTREE, "r");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier d'entrée '%s'\n", FICHIER_ENTREE);
        return 1;
    }

    // Ouvrir le fichier de sortie en mode écriture
    fichier2 = fopen(FICHIER_SORTIE, "w");
    if (fichier2 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie '%s'\n", FICHIER_SORTIE);
        fclose(fichier1);
        return 1;
    }


    copierdonnee(fichier1, fichier2);
    

    // Fermer les fichiers
    if (fclose(fichier1) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier d'entrée '%s'\n", FICHIER_ENTREE);
    }
    if (fclose(fichier2) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier de sortie '%s'\n", FICHIER_SORTIE);
    }


    printf("Traitement terminé avec succès.\n");

    return 0;
}
