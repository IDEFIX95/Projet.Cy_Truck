// ÉTAPE 5

// Cette étape permet de fusionner les résultats (additionner) et écrire dans un fichier les 10 premières villes qui parcourent le plus de distance.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAILLE_BUFFER 2048

// Structure pour stocker une ligne de données
typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    int temp;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;

// Structure pour l'arbre binaire de recherche (ABR)
typedef struct lignes{
    char col1[TAILLE_BUFFER];
    int col2;
    int col3;
} lignes;

// Fonction de comparaison pour qsort (tri par la deuxième colonne)
int compareCol2(const void *a, const void *b) {
    return ((lignes *)b)->col2 - ((lignes *)a)->col2;
}

// Fonction pour créer un nouveau nœud de l'ABR
pABR creerchainon(char *c, int e) {
    ABR *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new->ville, c, TAILLE_BUFFER);
    new->somme = e;
    new->temp = 0;
    new->fd = new->fg = NULL;
    return new;
}

// Fonction pour l'insertion dans l'ABR
pABR insertionABR(pABR a, char *c, int e) {
    if (a == NULL) {
        a = creerchainon(c, e);
    } 
    else {
        int comparaisonVille = strcmp(c, a->ville);
        if (comparaisonVille < 0) {
            a->fg = insertionABR(a->fg, c, e);
        } 
        else if (comparaisonVille > 0) {
            a->fd = insertionABR(a->fd, c, e);
        } 
        else {
            a->somme = e + a->somme;
            a->temp = e;
        }
    }
    return a;
}

// Parcours décroissant de l'ABR et écriture dans un fichier

void parcoursdecroissant(pABR a, FILE *fichier) {
    if (a != NULL) {
        parcoursdecroissant(a->fd, fichier);
        fprintf(fichier, "%s;%d;%d\n", a->ville, a->somme, a->temp);
        parcoursdecroissant(a->fg, fichier);
    }
}

// Traitement du fichier CSV et construction de l'ABR
void traiterfichier(pABR *a, FILE *fichier) {
    char buffer[TAILLE_BUFFER];
    char elm[TAILLE_BUFFER];
    int e;
    int colonne = 1;

    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        char *token = strtok(buffer, "\n");

        while (token != NULL) {
            char *token2 = strtok(token, ";");

            while (token2 != NULL) {
                if (colonne == 1) {
                    strncpy(elm, token2, sizeof(elm) - 1);
                    elm[sizeof(elm) - 1] = '\0';
                    colonne++;
                } 
                else if (colonne == 2) {
                    e = atoi(token2);
                    *a = insertionABR(*a, elm, e);
                    colonne = 1;  
                    // Réinitialiser pour la prochaine itération
                }

                token2 = strtok(NULL, ";");
            }

            token = strtok(NULL, "\n");
        }
    }
}

// Libération de la mémoire utilisée par l'ABR
void libererABR(pABR a) {
    if (a != NULL) {
        libererABR(a->fg);
        libererABR(a->fd);
        free(a);
    }
}


int main() {
    // Ouverture des fichiers
    FILE *fichier1, *fichier2, *fichier3, *fichier4;
    pABR a = NULL;

    fichier2 = fopen("temp/total_trajet_decroissant_villededepart.csv", "r");
    if (fichier2 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fichier3 = fopen("temp/total_trajets_decroissant.csv", "r");
    if (fichier3 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fichier1 = fopen("temp/fichierfusionnertrajets.csv", "w");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Traitement des fichiers et construction de l'ABR
    traiterfichier(&a,fichier3);
    printf("Passage au traitement du fichier suivant.\n");
    traiterfichier(&a,fichier2);
    parcoursdecroissant(a,fichier1);

    // Fermeture des fichiers
    if (fclose(fichier2) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier2.\n");
    }
    if (fclose(fichier3) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier3.\n");
    }
    if (fclose(fichier1) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier1.\n");
    }

    fichier1 = fopen("temp/fichierfusionnertrajets.csv", "r");  
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char ligne[TAILLE_BUFFER];

    int nombreDeLignes = 0;
    while (fgets(ligne, sizeof(ligne), fichier1) != NULL) {
        nombreDeLignes++;
    }

    fclose(fichier1);
    fichier1 = fopen("temp/fichierfusionnertrajets.csv", "r");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    lignes *donnees = malloc(nombreDeLignes * sizeof(lignes));

    for (int i = 0; i < nombreDeLignes; i++) {
        if (fgets(ligne, sizeof(ligne), fichier1) != NULL) {
            if (sscanf(ligne, "%1023[^;];%d;%d", donnees[i].col1, &donnees[i].col2, &donnees[i].col3) == 3) {
            } 
            else {
                fprintf(stderr, "Erreur lors de la lecture des données du fichier fichier1 avant le tri.\n");
                fprintf(stderr, "Ligne problématique : %s\n", ligne);
                free(donnees);
                libererABR(a);
                fclose(fichier1);
                fclose(fichier2);
                fclose(fichier3);
                return 1;
            }
        }
    }

    fclose(fichier1);
    qsort(donnees, nombreDeLignes, sizeof(lignes), compareCol2);

    fichier4 = fopen("temp/fichier_avant_parcours.csv", "w");  
    if (fichier4 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier fichier4.\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        fprintf(fichier4, "%s;%d;%d", donnees[i].col1, donnees[i].col2, donnees[i].col3);
        if (i < 9){
            fprintf(fichier4, "\n");
        }
    }


    if (fclose(fichier4) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier4.\n");
    }

    // Libération de la mémoire
    free(donnees);
    printf("Traitement terminé avec succès.\n");

    libererABR(a);
    return 0;
}
