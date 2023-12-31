//ETAPE 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024

typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;


pABR creerchainon(char *c) {
    ABR *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new->ville, c, TAILLE_BUFFER);
    new->somme = 1;
    new->fd = new->fg = NULL;
    return new;
}


pABR insertionABR(pABR a, char *c) {
    if (a == NULL) {
        a = creerchainon(c);
    } else {
        int comparaisonVille = strcmp(c, a->ville);     // On compare la ville actuel dans le noeud de l'arbre avec la nouvelle ville à inserer
        if (comparaisonVille < 0) {
            a->fg = insertionABR(a->fg, c);
        } else if (comparaisonVille > 0) {
            a->fd = insertionABR(a->fd, c);
        } else {
            a->somme++;                // On somme les villes deja rencontrées. De toute maniere si elles sont nouvelles leur somme prend 1 directement à l'aide de creerchainon.
        }
    }
    return a;
}

void parcoursdecroissant(pABR a, FILE *fichier) {
    if (a != NULL) {
        parcoursdecroissant(a->fd, fichier);
        fprintf(fichier, "%s;%d\n", a->ville, a->somme);
        parcoursdecroissant(a->fg, fichier);
    } 
}

void ExtraireLignesDuCol2(pABR *a, FILE *fichier1) {
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
                    token3 = strtok(NULL, ";");  // Passer à la colonne suivante
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


int main() {
    FILE *fichier1 = fopen("temp/fichier_col4.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }
    
    FILE *fichier2 = fopen("temp/additionville.csv", "w");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    FILE *fichier3 = fopen("temp/addition_ville_villedepart.csv", "w");
    if (fichier3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    FILE *fichier4 = fopen("temp/fichier_col2_3.csv", "r");
    if (fichier4 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    pABR arbre = NULL;
    pABR arbre2 = NULL;


    /* Cette partie du filtrage va recuperer toutes les villes d'arrivées et le nombre d'apparition de cette meme ville.
       Tous d'abord dans ExtraireLignesDuCol2 on va extraire la colonne des villes d'arrivées du fichier fichier_col4.csv
       la somme à la rencontre de nouvelles villes ou de villes deja presente dans l'arbre va s'effectuer à l'aide de insertAVL.
       Ensuite on va utiliser un avl ou on va stocker toutes les villes et on va parcourir cette avl à l'aide de parcoursdecroissant */
    ExtraireLignesDuCol2(&arbre, fichier1);
    printf("Fin de l'extraction des lignes du fichier.\n");  // Message de débogage
    parcoursdecroissant(arbre, fichier2);
    printf("Fin du parcours décroissant de l'arbre.\n");  // Message de débogage


    ExtraireLignesDuCol2et3(&arbre2, fichier4);
    printf("Fin de l'extraction des lignes du fichier.\n");  // Message de débogage
    parcoursdecroissant(arbre2, fichier3);
    printf("Fin du parcours décroissant de l'arbre.\n");  // Message de débogage

    // Vérifier la fin du fichier d'entrée
    if (feof(fichier1)) {
        printf("Fin du fichier d'entrée atteinte.\n");
        fclose(fichier1);
    } else {
        perror("Erreur lors de la lecture du fichier d'entrée");
    }

    fclose(fichier2);
    fclose(fichier3);
    fclose(fichier4);
 
    return 0;
}
