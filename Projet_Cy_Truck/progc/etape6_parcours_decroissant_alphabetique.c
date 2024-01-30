#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    char nom[100];
    int col1;
    int col2;
};

int compare(const void *a, const void *b) {
    return strcmp(((struct Record *)a)->nom, ((struct Record *)b)->nom);
}

int main() {
    FILE *fichier1 = fopen("temp/fichier_avant_parcours.csv", "r");
    if (fichier1 == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrée.\n");
        return 1;
    }

    char ligne[256];
    struct Record records[100];
    int compteur = 0;

    while (fgets(ligne, sizeof(ligne), fichier1)) {
        sscanf(ligne, "%[^;];%d;%d", records[compteur].nom, &records[compteur].col1, &records[compteur].col2);
        compteur++;
    }

    fclose(fichier1);

    qsort(records, compteur, sizeof(struct Record), compare);

    FILE *fichier2 = fopen("demo/fichier_final.csv", "w");
    if (fichier2 == NULL) {
        fprintf(stderr, "Impossible de créer le fichier trié.\n");
        return 1;
    }

    for (int i = 0; i < compteur; i++) {
        fprintf(fichier2, "%s;%d;%d\n", records[i].nom, records[i].col1, records[i].col2);
    }

    fclose(fichier2);

    printf("Le fichier a été trié avec succès. Les résultats sont dans fichier_final.csv se situant dans le dossier demo.\n");

    return 0;
}
