#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096  // Augmenté la taille du tampon

struct Statistique {
    int id;
    float min;
    float max;
    int somme;
    int count;
    float moyenne;
    float difference;
};

int main() {
    FILE *input = fopen("temp/s_intermediaire_calcul.csv", "r");
    if (input == NULL) { 
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrée s_intermediaire_calcul.csv\n");
        return 1;
    }

    FILE *output = fopen("temp/s_filtre.csv", "w+");
    if (output == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier de sortie s_filtre.csv\n");
        fclose(input);
        return 1;
    }

    // Variables pour gérer dynamiquement la mémoire
    int max_id = -1;
    struct Statistique *stats = NULL;

    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), input)) {
        int id, value;
        if (sscanf(line, "%d;%d", &id, &value) != 2) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne : %s", line);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        // Vérifier si l'identifiant est dans la plage attendue
        if (id >= 0) {
            // Mettre à jour le plus grand identifiant rencontré
            if (id > max_id) {
                max_id = id;
            }

            // Réallouer dynamiquement la mémoire si nécessaire
            stats = realloc(stats, (max_id + 1) * sizeof(struct Statistique));

            // Initialiser à zéro si l'élément est nouvellement alloué
            if (stats[id].count == 0) {
                stats[id].id = id;
                stats[id].min = value;
                stats[id].max = value;
                stats[id].somme = value;
                stats[id].count = 1;
            } else {
                // Mettre à jour les statistiques
                if (value < stats[id].min) {
                    stats[id].min = value;
                }
                if (value > stats[id].max) {
                    stats[id].max = value;
                }
                stats[id].somme += value;
                stats[id].count++;
            }
        }
    }

    for (int i = 0; i <= max_id; i++) {
        if (stats[i].count > 0) {
            stats[i].moyenne = (float)stats[i].somme / stats[i].count;
            stats[i].difference = (float)stats[i].max - (float)stats[i].min;
            fprintf(output, "%d;%.2f;%.2f;%.2f;%.2f\n", stats[i].id, stats[i].min, stats[i].moyenne, stats[i].max, stats[i].difference);
        }
    }

    // Libérer la mémoire allouée dynamiquement
    free(stats);



    fclose(input);
    fclose(output);

    if (remove("temp/s_intermediaire_calcul.csv") != 0) {
        printf("Erreur lors de la suppression du fichier %s\n", "temp/s_intermediaire_calcul.csv");
        return 1;
    }
    printf("\nLe fichier %s a été supprimé avec succès.\n", "temp/s_intermediaire_calcul.csv");
   

    return 0;
}