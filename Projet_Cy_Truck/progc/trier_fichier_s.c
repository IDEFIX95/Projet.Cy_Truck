// Etape 2 : trie final

// On va trié le fichier s_filtre.csv et renvoyé un le fichier final trié qui va s'appeler fichier_traite_opt_s.csv

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 4096

// Définition de la structure d'un arbre AVL
typedef struct AVL {
    int id;
    float dist_min;
    float dist_max;
    float dist_moy;
    float diff;
    struct AVL *fg;  // Fil gauche
    struct AVL *fd;  // Fil droit
    int h;           // Hauteur
} Arbre, *pArbre;

// Fonction utilitaire pour obtenir le maximum de deux entiers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction utilitaire pour obtenir le minimum de deux entiers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Rotation simple à gauche pour rééquilibrer l'arbre AVL
pArbre rotationGauche(pArbre a) {
    if (a == NULL || a->fd == NULL) {
        return a;
    }

    pArbre pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    int eq_a = a->h;
    int eq_p = pivot->h;
    a->h = eq_a - max(eq_p, 0) - 1;
    pivot->h = min(eq_a - 2, min(eq_a + eq_p - 2, eq_p - 1));
    a = pivot;
    return a;
}

// Rotation simple à droite pour rééquilibrer l'arbre AVL
pArbre rotationDroite(pArbre a) {
    if (a == NULL || a->fg == NULL) {
        return a;
    }

    pArbre pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    int eq_a = a->h;
    int eq_p = pivot->h;
    a->h = eq_a - min(eq_p, 0) + 1;
    pivot->h = max(eq_a + 2, max(eq_a + eq_p + 2, eq_p + 1));
    a = pivot;
    return a;
}

// Rotation double à gauche (gauche-droite) pour rééquilibrer l'arbre AVL
pArbre doubleRotationGauche(pArbre a) {
    if (a == NULL) {
        return a;
    }

    a->fd = rotationDroite(a->fd);
    a = rotationGauche(a);
    return a;
}

// Rotation double à droite (droite-gauche) pour rééquilibrer l'arbre AVL
pArbre doubleRotationDroite(pArbre a) {
    if (a == NULL) {
        return a;
    }

    a->fg = rotationGauche(a->fg);
    a = rotationDroite(a);
    return a;
}

// Fonction pour rééquilibrer l'arbre AVL en fonction de la hauteur des sous-arbres
pArbre equilibrerAVL(pArbre a) {
    if (a == NULL) {
        return a;
    }

    // Cas où la hauteur du sous-arbre droit est trop élevée
    if (a->h >= 2) {
        // Cas d'une simple rotation à gauche si le sous-arbre droit est équilibré ou incliné vers la gauche
        if (a->fd != NULL && a->fd->h >= 0) {
            return rotationGauche(a);
        } 
        // Cas d'une double rotation à gauche-droite si le sous-arbre droit est incliné vers la droite
        else {
            return doubleRotationGauche(a);
        }
    } 
    // Cas où la hauteur du sous-arbre gauche est trop élevée
    else if (a->h <= -2) {
        // Cas d'une simple rotation à droite si le sous-arbre gauche est équilibré ou incliné vers la droite
        if (a->fg != NULL && a->fg->h <= 0) {
            return rotationDroite(a);
        } 
        // Cas d'une double rotation à droite-gauche si le sous-arbre gauche est incliné vers la gauche
        else {
            return doubleRotationDroite(a);
        }
    }
    return a;
}

// Fonction pour créer un nouveau nœud avec allocation dynamique de mémoire
pArbre creerNoeud(int id, float diff, float max, float min, float moy) {
    Arbre *new = malloc(sizeof(*new));
    if (new != NULL) {
        // Initialisation des valeurs du nouveau nœud
        new->id = id;
        new->dist_max = max;
        new->dist_min = min;
        new->dist_moy = moy;
        new->diff = diff;
        new->h = 0; 
        new->fg = NULL;
        new->fd = NULL;
    } 
    else {
        fprintf(stderr, "Erreur d'allocation dynamique pour le nouveau nœud.\n");
    }
    return new;
}

// Fonction pour effectuer l'insertion d'un nœud dans l'arbre AVL
pArbre insertionAVL(pArbre x, int id, float diff, float max, float min, float moy, int *h) {
    if (x == NULL) {
        // Cas de l'insertion d'un nouveau nœud
        *h = 1;
        return creerNoeud(id, diff, max, min, moy);
    } 
    else if (diff < x->diff) {
        // Cas d'insertion dans le sous-arbre gauche et ajustement de la hauteur
        x->fg = insertionAVL(x->fg, id, diff, max, min, moy, h);
        *h = -*h;
    } 
    else if (diff > x->diff) {
        // Cas d'insertion dans le sous-arbre droit
        x->fd = insertionAVL(x->fd, id, diff, max, min, moy, h);
    } 
    else if (diff == 0) {
        // Cas d'ignorer les valeurs égales (non autorisées dans cet exemple)
        return x;
    }

    // Ajustement de la hauteur actuelle et rééquilibrage de l'arbre
    if (*h != 0) {
        x->h = x->h + *h;
        x = equilibrerAVL(x);

        // Mise à jour de la hauteur après rééquilibrage
        if (x->h == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }

    return x;
}

// Fonction pour extraire la 5ème colonne d'un fichier CSV et l'insérer dans l'arbre AVL
void extrairecol5(pArbre *a, FILE *fichier) {
    if (a == NULL || fichier == NULL) {
        fprintf(stderr, "Erreur : Pointeur NULL passé à la fonction extrairecol5().\n");
        return;
    }

    char ligne[TAILLE_BUFFER];
    int h;
    int id;
    float mini, moy, maxi;
    int i = 0;

    // Parcours du fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, "\n");
        int colonne = 1;

        // Traitement des valeurs de chaque ligne séparées par des points-virgules
        while (token != NULL) {
            char *token2 = strtok(token, ";");

            while (token2 != NULL) {
                // Récupération des valeurs en fonction de la colonne
                if (colonne == 1) {
                    id = atoi(token2);
                } 
                else if (colonne == 2) {
                    mini = atof(token2);
                } 
                else if (colonne == 3) {
                    moy = atof(token2);
                } 
                else if (colonne == 4) {
                    maxi = atof(token2);
                } 
                else if (colonne == 5) {
                    // Insertion des valeurs dans l'arbre AVL avec ajustement de la hauteur
                    float diff = atof(token2);
                    i++;
                    *a = insertionAVL(*a, id, diff, maxi, mini, moy, &h);
                }

                // Passage à la prochaine valeur dans la ligne
                token2 = strtok(NULL, ";");
                colonne++;
            }

            // Passage à la prochaine ligne
            token = strtok(NULL, "\n");
        }
    }
}


// Fonction pour parcourir l'arbre AVL de manière décroissante et écrire les résultats dans un fichier
void parcoursDecroissant(pArbre a, FILE *fichierSortie, int *i, const int lim) {
    if (a == NULL || fichierSortie == NULL || i == NULL) {
        return;
    }

    if (*i <= lim) {
        parcoursDecroissant(a->fd, fichierSortie, i, lim);
        if (*i <= lim) {
            fprintf(fichierSortie, "%d;%d;%f;%f;%f;%f\n", *i, a->id, a->dist_min, a->dist_moy, a->dist_max, a->diff);
            (*i)++;
        }
        parcoursDecroissant(a->fg, fichierSortie, i, lim);
    }
}

// Fonction pour libérer la mémoire allouée pour l'arbre AVL
void libererAVL(pArbre a) {
    if (a != NULL) {
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a);
    }
}

int main() {
    // Déclaration des pointeurs de fichiers et de l'arbre AVL
    FILE *fichier1, *fichier2;
    pArbre a = NULL;

    // Ouverture du fichier d'entrée en lecture
    fichier1 = fopen("temp/s_filtre.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture.");
        return 1;
    }

    // Ouverture du fichier de sortie en écriture
    fichier2 = fopen("demo/fichier_traite_opt_s.csv", "w");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en écriture.");
        fclose(fichier1);
        return 1;
    }

    // Extraction de la 5ème colonne du fichier CSV et insertion dans l'arbre AVL
    extrairecol5(&a, fichier1);

    // Initialisation du compteur pour le parcours décroissant limité à 50 éléments
    int compteur = 1;

    // Parcours décroissant de l'arbre AVL et écriture des résultats dans le fichier de sortie
    parcoursDecroissant(a, fichier2, &compteur, 50);

    // Fermeture des fichiers
    fclose(fichier1);
    fclose(fichier2);

    // Libération de la mémoire allouée pour l'arbre AVL
    libererAVL(a);

    // Fin du programme
    return 0;
}

