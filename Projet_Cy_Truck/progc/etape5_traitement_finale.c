//ETAPE 5.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAILLE_BUFFER 2048


typedef struct ABR {
    char ville[TAILLE_BUFFER];
    int somme;
    int temp;
    struct ABR *fd;
    struct ABR *fg;
} ABR, *pABR;

typedef struct lignes{
    char col1[TAILLE_BUFFER];
    int col2;
    int col3;
} lignes;

int compareCol2(const void *a, const void *b) {
    return ((lignes *)b)->col2 - ((lignes *)a)->col2;
}

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


pABR insertionABR(pABR a, char *c, int e) {
    if (a == NULL) {
        //printf("a est null\n");
        a = creerchainon(c, e);
        //printf("Nouveau nœud créé : %s, %d\n", c, e);  // Message de débogage
    } else {
        int comparaisonVille = strcmp(c, a->ville);
        if (comparaisonVille < 0) {
            //printf("Descendre dans le sous-arbre gauche\n");  // Message de débogage
            a->fg = insertionABR(a->fg, c, e);
        } else if (comparaisonVille > 0) {
            //printf("Descendre dans le sous-arbre droit\n");  // Message de débogage
            a->fd = insertionABR(a->fd, c, e);
        } else {
            //printf("Ville déjà présente, mettre à jour les valeurs\n");  // Message de débogage
            a->somme = e + a->somme;
            a->temp = e;
        }
    }
    return a;
}


void parcoursdecroissant(pABR a, FILE *fichier) {
    if (a != NULL) {
        parcoursdecroissant(a->fd, fichier);
        //printf("Ville : %s, Somme : %d, Temp : %d\n", a->ville, a->somme, a->temp);
        fprintf(fichier, "%s;%d;%d\n", a->ville, a->somme, a->temp);
        parcoursdecroissant(a->fg, fichier);
    } else {
        //printf("arbre null.\n");
    }
}


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
                    //printf("Ville : %s\n", elm);  // Message de débogage
                    colonne++;
                } else if (colonne == 2) {
                    e = atoi(token2);
                    //printf("e : %d\n", e);  // Message de débogage
                    *a = insertionABR(*a, elm, e);
                    colonne = 1;  // Réinitialiser pour la prochaine itération
                }

                token2 = strtok(NULL, ";");
            }

            token = strtok(NULL, "\n");
        }
    }
}




void libererABR(pABR a) {
    if (a != NULL) {
        libererABR(a->fg);
        libererABR(a->fd);
        free(a);
    }
}

int main() {
    FILE *fichier1,*fichier2, *fichier3, *fichier4;
    pABR a = NULL;

    fichier2 = fopen("temp/total_trajet_decroissant_villededepart.csv", "r");
    if (fichier2 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    fichier3 = fopen("temp/total_trajets_decroissant.csv", "r");
    if (fichier3 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    fichier1 = fopen("temp/fichierfusionnertrajets.csv", "w");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        return 1;
    }


    traiterfichier(&a,fichier3);
    printf("Passage au traitement du fichier suivant.\n");
    traiterfichier(&a,fichier2);
    parcoursdecroissant(a,fichier1);


    if (fclose(fichier2) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier2\n");
    }
    if (fclose(fichier3) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier3\n");
    }
    if (fclose(fichier1) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier1\n");
    }

    fichier1 = fopen("temp/fichierfusionnertrajets.csv", "r");  
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
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
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        return 1;
    }
    lignes *donnees = malloc(nombreDeLignes * sizeof(lignes));

    for (int i = 0; i < nombreDeLignes; i++) {
        if (fgets(ligne, sizeof(ligne), fichier1) != NULL) {
            if (sscanf(ligne, "%1023[^;];%d;%d", donnees[i].col1, &donnees[i].col2, &donnees[i].col3) == 3) {
            } else {
                fprintf(stderr, "Erreur lors de la lecture des données du fichier fichier1 avant le tri\n");
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

    fichier4 = fopen("demo/fichier_final.csv", "w");  
    if (fichier4 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier fichier4\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        fprintf(fichier4, "%s;%d;%d", donnees[i].col1, donnees[i].col2, donnees[i].col3);
        if (i < 9){
            fprintf(fichier4, "\n");
        }
    }


    if (fclose(fichier4) != 0) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier fichier4\n");
    }

    free(donnees);
    printf("Traitement terminé avec succès.\n");

    libererABR(a);
    return 0;
}
