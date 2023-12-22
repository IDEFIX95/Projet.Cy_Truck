#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024

/*typedef struct elem {
    char ID[TAILLE_BUFFER];
    char ville[TAILLE_BUFFER];
} elem;*/

typedef struct Ligne {
    char *element;
} Ligne;

typedef struct AVL {
    Ligne ligne;
    struct AVL *fg;
    struct AVL *fd;
    int h;
} AVL, *pAVL;


// Fonction pour calculer la hauteur d'un nœud
int hauteur(pAVL noeud) {
    if (noeud == NULL) {
        return -1;
    }
    return noeud->h;
}

// Fonction pour calculer le maximum entre deux nombres
int max(int a, int b) {
    return (a > b) ? a : b;
}


// Fonction pour calculer l'équilibre d'un nœud
int equilibre(pAVL noeud) {
    if (noeud == NULL) {
        return 0;
    }
    return hauteur(noeud->fg) - hauteur(noeud->fd);
}


pAVL creerArbre(char *ligne) {
    AVL *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }

    new->ligne.element = strdup(ligne);  // Utilise strdup pour allouer et copier la chaîne
    if (new->ligne.element == NULL) {
        fprintf(stderr, "Erreur d'allocation dynamique.\n");
        exit(EXIT_FAILURE);
    }

    new->fd = new->fg = NULL;
    new->h = 0;

    return new;
}



// Fonction pour insérer un élément dans l'arbre AVL
pAVL insertionAVL(pAVL a, char *e, int *h) {
    if (a == NULL) {
        *h = 1;
        return creerArbre(e);
    }

    int comparaisonVille = strcmp(e, a->ligne.element);

    if (comparaisonVille < 0) {
        a->fg = insertionAVL(a->fg, e, h);
    } else if (comparaisonVille > 0) {
        a->fd = insertionAVL(a->fd, e, h);
    } else {
        return a;
    }

    a->h = 1 + max(hauteur(a->fg), hauteur(a->fd));
    int equilibreValue = equilibre(a);

    if (*h == 0 || equilibreValue != 0) {
        *h = 1;
    } else {
        *h = 0;
    }

    return a;
}




// Fonction pour faire un parcours en ordre (inorder traversal)
void parcoursEnOrdre(pAVL racine, FILE *fichierSortie) {
    if (racine != NULL) {
        parcoursEnOrdre(racine->fg, fichierSortie);
        parcoursEnOrdre(racine->fd, fichierSortie);
        fprintf(fichierSortie, "ligne : %s\n", racine->ligne.element);
    }
}

void libererNoeud(pAVL noeud) {
    if (noeud != NULL) {
        libererNoeud(noeud->fg);
        libererNoeud(noeud->fd);
        free(noeud->ligne.element);  // Libérer la mémoire allouée pour la ligne
        free(noeud);
    }
}

void libererArbre(pAVL racine) {
    libererNoeud(racine);
}

    // Fonction pour écrire une ville dans le fichier de sortie
    void ecrireVilleDansFichier(FILE *fichier, char *e){
        fprintf(fichier, "ligne enregistré : %s\n", e);
    }



int main() {
    FILE *fichierEntree = fopen("fichier_traitage.csv", "r");
    if (fichierEntree == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    // Ouverture du fichier de sortie
    FILE *fichierSortie = fopen("arbre_sortie.csv", "w");
    if (fichierSortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    FILE *fichierEntree2 = fopen("fichier_sortie2.csv", "r");
    if (fichierEntree2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }


    FILE *fichierSortie2 = fopen("kill_occ(villedepart).csv", "w");
    if (fichierSortie2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }


    int h = 0;
    int h2 = 0;
    pAVL arbre = NULL;
    pAVL arbre2 = NULL;
    char element[TAILLE_BUFFER];
    char buffer[TAILLE_BUFFER];
    char buffer2[TAILLE_BUFFER];
    char element2[TAILLE_BUFFER];
    
    FILE *fichiersortie = fopen("villes_sortie.csv", "w");
    if (fichiersortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");

        return EXIT_FAILURE;
    }
    
   // Lecture du fichier d'entrée et insertion dans l'arbre AVL
    while (fgets(buffer, sizeof(buffer), fichierEntree) != NULL) {
            char *champ = strtok(buffer, "\n");

            while (champ != NULL) {
                strncpy(element, champ, sizeof(element));
                champ = strtok(NULL, "\n");

                // Insérer l'élément dans l'arbre AVL
                arbre = insertionAVL(arbre, element, &h);

                // Écrire l'élément dans le fichier de sortie
                ecrireVilleDansFichier(fichiersortie, element);
            }
    }

    while (fgets(buffer2, sizeof(buffer2), fichierEntree2) != NULL) {
            char *champ2 = strtok(buffer2, "\n");

            while (champ2 != NULL) {
                strncpy(element2, champ2, sizeof(element2));
                champ2 = strtok(NULL, "\n");

                // Insérer l'élément dans l'arbre AVL
                arbre2 = insertionAVL(arbre2, element2, &h2);

            }
    }
    // Vérifier la fin du fichier d'entrée
    if (feof(fichierEntree)) {
        printf("Fin du fichier d'entrée 1 atteinte.\n");
        fclose(fichierEntree);
    } else {
        perror("Erreur lors de la lecture du fichier d'entrée");
    }

    if (feof(fichierEntree2)) {
        printf("Fin du fichier d'entrée atteinte.\n");
        fclose(fichierEntree2);
    } else {
        perror("Erreur lors de la lecture du fichier d'entrée");
    }

    // Parcours en ordre et écriture dans le fichier de sortie
    parcoursEnOrdre(arbre, fichierSortie);
    parcoursEnOrdre(arbre2, fichierSortie2);

    // Fermer le fichier de sortie
    fclose(fichierSortie);
    fclose(fichierSortie2);
    fclose(fichiersortie);

    // ... (Effectuez d'autres opérations avec l'arbre si nécessaire)
    libererArbre(arbre);
    libererArbre(arbre2);
    return 0;
}
