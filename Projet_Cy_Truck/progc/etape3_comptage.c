// ÉTAPE 3

/* Cette partie du programme va récupérer toutes les villes d'arrivée ainsi que le nombre d'apparitions de ces mêmes villes.
    Tout d'abord, dans la fonction "ExtraireVilleDarrive()", nous extrayons la colonne des villes d'arrivée du fichier "fichier_col4.csv".
    Ensuite, la somme des nouvelles villes rencontrées ou des villes déjà présentes dans l'arbre s'effectue à l'aide de la fonction "insertionABR()".
    Enfin, nous utilisons un ABR pour stocker l'ensemble des villes, puis nous parcourons cet ABR à l'aide de la fonction "parcoursdecroissant()".*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024

// Utilisation d'un ABR pour additionner le nombre de villes
typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;

// Fonction pour créer un nouveau maillon de l'arbre
pABR creerchainon(char *c) {
    // Allouer dynamiquement un nouvel élément de l'arbre
    ABR *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs du nouvel élément
    strncpy(new->ville, c, TAILLE_BUFFER);
    new->somme = 1;
    new->fd = new->fg = NULL;
    return new;
}

// Fonction pour insérer une ville dans l'ABR
pABR insertionABR(pABR a, char *c) {
    if (a == NULL) {
        // Si l'arbre est vide, créer un nouveau maillon
        a = creerchainon(c);
    } else {
        int comparaisonVille = strcmp(c, a->ville);

        if (comparaisonVille < 0) {
            // Si la nouvelle ville est inférieure, descendre à gauche
            a->fg = insertionABR(a->fg, c);
        } else if (comparaisonVille > 0) {
            // Si la nouvelle ville est supérieure, descendre à droite
            a->fd = insertionABR(a->fd, c);
        } else {
            // Si la ville existe déjà, incrémenter le compteur
            a->somme++;
        }
    }
    return a;
}

// Fonction pour parcourir l'ABR en ordre décroissant et écrire dans le fichier
void parcoursdecroissant(pABR a, FILE *fichier) {
    if (a != NULL) {
        parcoursdecroissant(a->fd, fichier);
        fprintf(fichier, "%s;%d\n", a->ville, a->somme);
        parcoursdecroissant(a->fg, fichier);
    }
}

// Fonction pour extraire les villes d'arrivée du fichier "fichier_col4.csv" et les insérer dans l'ABR
void ExtraireVilleDarrive(pABR *a, FILE *fichier1) {
    char buffer[TAILLE_BUFFER];
    char elm[TAILLE_BUFFER];

    while (fgets(buffer, sizeof(buffer), fichier1) != NULL) {
        char *token = strtok(buffer, "\n");
        while (token != NULL) {
            strncpy(elm, token, sizeof(elm));
            *a = insertionABR(*a, elm);
            token = strtok(NULL, "\n");
        }
    }
}

// Fonction pour extraire les colonnes 2 et 3 du fichier "fichier_col2_3.csv" et les insérer dans l'ABR
void ExtraireLignesDuCol2et3(pABR *a, FILE *fichier2) {
    char buffer2[TAILLE_BUFFER];
    char step[TAILLE_BUFFER];

    while (fgets(buffer2, sizeof(buffer2), fichier2) != NULL) {
        char *token3 = strtok(buffer2, ";");
        int colonne = 1;

        while (token3 != NULL) {
            if (colonne == 1) {
                strncpy(step, token3, sizeof(step));
                if (strcmp(step, "1") == 0) {
                    // Colonne 2 contient "1", insérer les éléments de la colonne suivante (colonne 3)
                    token3 = strtok(NULL, ";");
                    while (token3 != NULL) {
                        char *token4 = strtok(token3, "\n");
                        if (token4 != NULL) {
                            *a = insertionABR(*a, token4);
                        }
                        token3 = strtok(NULL, ";");
                    }
                }
            }
            token3 = strtok(NULL, ";");
            colonne++;
        }
    }
}

// Fonction pour libérer la mémoire allouée à l'ABR
void libererABR(pABR a) {
    if (a != NULL) {
        libererABR(a->fg);
        libererABR(a->fd);
        free(a);
    }
}


int main() {
    // Ouverture des fichiers en lecture et écriture

    // Fichier contenant les villes d'arrivée
    FILE *fichier1 = fopen("temp/fichier_col4.csv", "r");
    // Vérifier si l'ouverture du fichier a réussi
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    // Fichier de sortie pour les sommes des villes d'arrivée
    FILE *fichier2 = fopen("temp/additionville.csv", "w");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        // Fermer les fichiers déjà ouverts avant de quitter
        fclose(fichier1);
        return 1;
    }

    // Fichier de sortie pour les sommes des villes et villes de départ
    FILE *fichier3 = fopen("temp/addition_ville_villedepart.csv", "w");
    if (fichier3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        // Fermer les fichiers déjà ouverts avant de quitter
        fclose(fichier1);
        fclose(fichier2);
        return 1;
    }

    // Fichier contenant les colonnes 2 et 3
    FILE *fichier4 = fopen("temp/fichier_col2_3.csv", "r");
    if (fichier4 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        // Fermer les fichiers déjà ouverts avant de quitter
        fclose(fichier1);
        fclose(fichier2);
        fclose(fichier3);
        return 1;
    }

    // Initialisation des arbres pour stocker les données
    pABR arbre = NULL;
    pABR arbre2 = NULL;

    ExtraireVilleDarrive(&arbre, fichier1);
    parcoursdecroissant(arbre, fichier2);

    // ... (Répétez le même processus pour le deuxième fichier)

    ExtraireLignesDuCol2et3(&arbre2, fichier4);
    parcoursdecroissant(arbre2, fichier3);

    // Libérer la mémoire allouée pour les arbres
    libererABR(arbre);
    libererABR(arbre2);

    // Fermeture des fichiers
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichier3);
    fclose(fichier4);
 
    printf("Traitement de l'étape 3 terminé avec succès.\n");

    return 0;
}

