#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les enregistrements du fichier CSV
struct Record {
    char nom[100];
    int col1;
    int col2;
};

// Fonction de comparaison pour qsort, triant les enregistrements par ordre alphabétique du champ 'nom'
int compare(const void *a, const void *b) {
    return strcmp(((struct Record *)a)->nom, ((struct Record *)b)->nom);
}

int main() {
    // Ouverture du fichier d'entrée en lecture
    FILE *fichier1 = fopen("temp/fichier_avant_parcours.csv", "r");
    if (fichier1 == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrée.\n");
        return 1;
    }

    // Déclaration des variables
    char ligne[256];
    struct Record records[100];
    int compteur = 0;

    // Lecture du fichier d'entrée et stockage des enregistrements dans un tableau
    while (fgets(ligne, sizeof(ligne), fichier1)) {
        sscanf(ligne, "%[^;];%d;%d", records[compteur].nom, &records[compteur].col1, &records[compteur].col2);
        compteur++;
    }

    // Fermeture du fichier d'entrée
    fclose(fichier1);

    // Tri du tableau d'enregistrements en utilisant la fonction qsort
    qsort(records, compteur, sizeof(struct Record), compare);

    // Ouverture du fichier de sortie en écriture
    FILE *fichier2 = fopen("demo/fichier_final.csv", "w");
    if (fichier2 == NULL) {
        fprintf(stderr, "Impossible de créer le fichier trié.\n");
        return 1;
    }

    // Écriture des enregistrements triés dans le fichier de sortie
    for (int i = 0; i < compteur; i++) {
        fprintf(fichier2, "%s;%d;%d\n", records[i].nom, records[i].col1, records[i].col2);
    }

    // Fermeture du fichier de sortie
    fclose(fichier2);

    
    // Affichage d'un message de succès
    printf("Traitement de l'étape 6 terminé avec succès.\n");
    printf("Le fichier a été trié avec succès. Les résultats sont dans fichier_final.csv se situant dans le dossier demo.\n");

    // Fin du programme
    return 0;
}
