// ETAPE 1 : Le Filtrage

// Cette étape va permettre de filtrer dans un 1er temps de recuperer les données et de faire le min/moyenne/max/difference entre le max et le min pour chaque route Id

// Par la suite une fois ces données faient le programme les ecrient dans un fichier de sortie nommé s_filtre.csv 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filtre_s.h"

#define BUFFER_SIZE 4096  // Augmenter la taille du tampon

// Initialisation de la strcuture pour pouvoir 


int main() {
    // Ouverture du fichier d'entrée en mode lecture
    FILE *fichier_d_entrer = fopen("temp/s_intermediaire_calcul.csv", "r");
    if (fichier_d_entrer == NULL) { 
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrée s_intermediaire_calcul.csv.\n");
        return 1;
    }
    
    // Ouverture du fichier de sortie en mode écriture ou création s'il n'existe pas
    FILE *fichier_de_sortie = fopen("temp/s_filtre.csv", "w+");
    if (fichier_de_sortie == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de sortie s_filtre.csv.\n");
        fclose(fichier_d_entrer);
        return 1;
    }

    // Variables pour gérer dynamiquement la mémoire
    int max_id = -1;
    struct Statistique *stats = NULL;

    char line[BUFFER_SIZE];
    // Parcours du fichier d'entrée ligne par ligne
    while (fgets(line, sizeof(line),fichier_d_entrer)) {
        int id; 
        float valeur;
        // Lecture de l'identifiant et de la valeur depuis la ligne
        if (sscanf(line, "%d;%f", &id, &valeur) != 2) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne : %s", line);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        // Vérification si l'identifiant est dans la plage attendue
        if (id >= 0) {
            // Mettre à jour le plus grand identifiant rencontré
            if (id > max_id) {
                max_id = id;
            }

            // Réallouer dynamiquement la mémoire si nécessaire
            stats = realloc(stats, (max_id + 1) * sizeof(struct Statistique));

            // Initialisation à zéro si l'élément est nouvellement alloué
            if (stats[id].compteur == 0) {
                stats[id].id = id;
                stats[id].min = valeur;
                stats[id].max = valeur;
                stats[id].somme = valeur;
                stats[id].compteur = 1;
            } 
            else {
                // Mettre à jour les statistiques
                if (valeur < stats[id].min) {
                    stats[id].min = valeur;
                }
                if (valeur > stats[id].max) {
                    stats[id].max = valeur;
                }
                stats[id].somme += valeur;
                stats[id].compteur++;
            }
        }
    }

    // Parcours des statistiques calculées et écriture dans le fichier de sortie
    for (int i = 0; i <= max_id; i++) {
        if (stats[i].compteur > 0) {
            stats[i].moyenne = (float)stats[i].somme / stats[i].compteur;
            stats[i].difference = (float)stats[i].max - (float)stats[i].min;
            fprintf(fichier_de_sortie, "%d;%.3f;%.2f;%.3f;%.3f\n", stats[i].id, stats[i].min, stats[i].moyenne, stats[i].max, stats[i].difference);
        }
    }

    // Libération de la mémoire allouée dynamiquement
    free(stats);

    // Fermeture des fichiers
    fclose(fichier_d_entrer);
    fclose(fichier_de_sortie);

    // Suppression du fichier d'entrée
    if (remove("temp/s_intermediaire_calcul.csv") != 0) {
        printf("Erreur lors de la suppression du fichier %s.\n", "temp/s_intermediaire_calcul.csv");
        return 1;
    }
    printf("\nLe fichier %s a été supprimé avec succès.\n", "temp/s_intermediaire_calcul.csv");
   
    return 0;
}
