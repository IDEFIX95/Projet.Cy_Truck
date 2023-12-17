#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les statistiques
struct Statistique {
    char nom[256];
    float distance_total;
};

// Fonction de comparaison pour le tri qsort
int comparer_statistiques(const void *a, const void *b) {
    return ((struct Statistique *)b)->distance_total - ((struct Statistique *)a)->distance_total;
}

int main() {
    FILE *input = fopen("progc/d2_final1.csv", "r");
    FILE *output = fopen("progc/d2_vraifinal.csv", "w");

    if (input == NULL || output == NULL) {
        printf("Impossible d'ouvrir les fichiers d'entrée/sortie\n");
        return 1; // Quitte le programme avec un code d'erreur
    }

    // Tableau pour stocker les statistiques pour chaque nom
    struct Statistique stats[7000];
    int currentIndex = 0;

    // Lire les lignes du fichier d'entrée
    char line[1024];
    while (fgets(line, sizeof(line), input)) {
        float distance;
        char nom[256];
        int result = sscanf(line, "%f;%*[^;];%*[^;];%*[^;];%*[^;];%255[^;]", &distance, nom);

        if (result == 1) {
            // Recherche du nom dans le tableau
            int found = 0;
            for (int i = 0; i < currentIndex; i++) {
                if (strcmp(stats[i].nom, nom) == 0) {
                    // Si le nom existe déjà, mise à jour des statistiques
                    stats[i].distance_total += distance;
                    found = 1;
                    break;
                }
            }

            // Si le nom n'a pas été trouvé, ajoutez-le au tableau
            if (!found) {
                strncpy(stats[currentIndex].nom, nom, sizeof(stats[currentIndex].nom));
                stats[currentIndex].distance_total = distance;
                currentIndex++;
            }
        } else {
            printf("Erreur de lecture de la ligne : %s\n", line);
        }
    }

    // Tri du tableau des statistiques en utilisant qsort
    qsort(stats, currentIndex, sizeof(struct Statistique), comparer_statistiques);

    // Écrire les dix premières entrées dans le fichier de sortie
    for (int i = 0; i < 10 && i < currentIndex; i++) {
        fprintf(output, "%s %.3f\n", stats[i].nom, stats[i].distance_total);
    }

    fclose(input);
    fclose(output);

    return 0;
}