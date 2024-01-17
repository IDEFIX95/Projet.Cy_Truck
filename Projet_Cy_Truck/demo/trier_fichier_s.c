#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024

typedef struct AVL {
    int id;
    float dist_min;
    float dist_max;
    float dist_moy;
    float diff;
    struct AVL *fg;
    struct AVL *fd;
    int h;
} Arbre, *pArbre;

int max(int a, int b) {         //retourne le maximum entre deux entiers
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int min(int a, int b) {         //retourne le minimum entre deux entiers
  if (a < b) {
    return a;
  } else {
    return b;
  }
}


pArbre rotationGauche(pArbre a) {
    //printf("Rotation Gauche:\n");
    //printf("Nœud avant rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    pArbre pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    int eq_a = a->h;
    int eq_p = pivot->h;

    a->h = eq_a - max(eq_p, 0) - 1;
    pivot->h = min(eq_a - 2, min(eq_a + eq_p - 2, eq_p - 1));
    a = pivot;

    //printf("Nœud après rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);
    
    return a;
}



pArbre rotationDroite(pArbre a) {
    //printf("Rotation Droite:\n");
    //printf("Nœud avant rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    pArbre pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    int eq_a = a->h;
    int eq_p = pivot->h;
    a->h = eq_a - min(eq_p, 0) + 1;
    pivot->h = max(eq_a + 2, max(eq_a + eq_p + 2, eq_p + 1));
    a = pivot;

    //printf("Nœud après rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    return a;
}



pArbre doubleRotationGauche(pArbre a) {
    //printf("Double Rotation Gauche:\n");
    //printf("Nœud avant double rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    a->fd = rotationDroite(a->fd); // Rotation droite du fils droit de a
    a = rotationGauche(a); // Rotation gauche de a

    //printf("Nœud après double rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    return a;
}



pArbre doubleRotationDroite(pArbre a) {
    //printf("Double Rotation Droite:\n");
    //printf("Nœud avant double rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    a->fg = rotationGauche(a->fg); // Rotation gauche du fils gauche de a
    a = rotationDroite(a); // Rotation droite de a

    //printf("Nœud après double rotation : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    return a;
}


pArbre equilibrerAVL(pArbre a) {
    //printf("Équilibrage AVL :\n");
    //printf("Nœud avant équilibrage : (id: %d, diff: %f, h: %d)\n", a->id, a->diff, a->h);

    if (a->h >= 2) {
        // sous-arbre droit plus profond
        if (a->fd->h >= 0) {
            //printf("Rotation Gauche choisie.\n");
            return rotationGauche(a);
        } else {
            //printf("Double Rotation Gauche choisie.\n");
            return doubleRotationGauche(a);
        }
    } else if (a->h <= -2) {
        // sous-arbre gauche plus profond
        if (a->fg->h <= 0) {
            //printf("Rotation Droite choisie.\n");
            return rotationDroite(a);
        } else {
            //printf("Double Rotation Droite choisie.\n");
            return doubleRotationDroite(a);
        }
    }

    //printf("Pas de rotation nécessaire.\n");

    return a;
}



pArbre creerNoeud(int id, float diff, float max, float min, float moy) {
    Arbre *new = malloc(sizeof(*new));
    if (new != NULL) {
        new->id = id;
        new->dist_max = max;
        new->dist_min = min;
        new->dist_moy = moy;
        new->diff = diff;
        new->h = 0; 
        new->fg = NULL;
        new->fd = NULL;
        //printf("Nouveau nœud créé : (id: %d, diff: %f, h: %d)\n", new->id, new->diff, new->h);
    } else {
        printf("Erreur d'allocation dynamique pour le nouveau nœud.\n");
    }
    return new;
}


pArbre insertionAVL(pArbre x, int id, float diff, float max, float min, float moy, int *h) {
    if (x == NULL) {
        *h = 1;
        return creerNoeud(id, diff, max, min, moy);
    } else if (diff < x->diff) {
        //printf("Insertion dans le sous-arbre gauche.\n");
        x->fg = insertionAVL(x->fg, id, diff, max, min, moy, h);
        *h = -*h;
    } else if (diff > x->diff) {
        //printf("Insertion dans le sous-arbre droit.\n");
        x->fd = insertionAVL(x->fd, id, diff, max, min, moy, h);
    } else if (diff == 0) {
        //printf("Le nœud avec la même différence existe déjà.\n");
        return x;
    }
    
    if (*h != 0) {
        x->h = x->h + *h;
        x = equilibrerAVL(x);

        if (x->h == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
        //printf("Équilibrage effectué. Nouvelle hauteur : %d\n", x->h);
    }

    return x;
}


void extrairecol5(pArbre *a, FILE *fichier) {
    char ligne[TAILLE_BUFFER];
    int h;
    int id;
    float mini, moy, maxi;
    int i = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, "\n");
        int colonne = 1;

        while (token != NULL) {
            char *token2 = strtok(token, ";");

            while (token2 != NULL) {
                if (colonne == 1) {
                    id = atoi(token2);
                } else if (colonne == 2) {
                    mini = atof(token2);
                } else if (colonne == 3) {
                    moy = atof(token2);
                } else if (colonne == 4) {
                    maxi = atof(token2);
                } else if (colonne == 5) {
                    // Limiter la précision à 3 chiffres après la virgule
                    float diff;
                    sscanf(token2, "%f", &diff);
                    char diffStr[TAILLE_BUFFER];
                    snprintf(diffStr, sizeof(diffStr), "%.3f", diff);
                    diff = atof(diffStr);

                    //printf("diff : %f\n", diff);
                    //printf("ligne : %d\n", i);
                    *a = insertionAVL(*a, id, diff, maxi, mini, moy, &h);
                    i++;
                    //printf("------------------------------------------------\n");
                }

                token2 = strtok(NULL, ";");
                colonne++;
            }

            token = strtok(NULL, "\n");
        }
    }
}


void parcoursDecroissant(pArbre a, FILE *fichierSortie, int *i, const int lim) {
    if (a != NULL && *i <= lim) {
        parcoursDecroissant(a->fd, fichierSortie, i, lim);

        fprintf(fichierSortie, "%d;%d;%f;%f;%f;%f\n", *i, a->id, a->dist_min, a->dist_moy, a->dist_max, a->diff);

        (*i)++;
        parcoursDecroissant(a->fg, fichierSortie, i, lim);
    }
}

void libererAVL(pArbre a) {
    if (a != NULL) {
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a);
    }
}

int main(){

    FILE *fichier1, *fichier2;
    pArbre a;

    fichier1 = fopen("s_filtre.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    fichier2 = fopen("fichier_traite_opt-s.csv", "w");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        fclose(fichier1); // Fermez le fichier déjà ouvert
        return 1;
    }

    extrairecol5(&a, fichier1);

    int compteur = 1;
    parcoursDecroissant(a, fichier2, &compteur, 50);

    fclose(fichier1);
    fclose(fichier2);

    libererAVL(a);

    return 0;
}
