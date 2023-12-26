//ETAPE 4.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BUFFER 1024

typedef struct AVL {
    char ville[TAILLE_BUFFER];
    int somme;
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

int min(int a, int b) {         //retourne le minimum entre deux tniers
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

pArbre rotationGauche(pArbre a) {       //rotation gauche du noeud
    pArbre pivot=a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    int eq_a=a->h;
    int eq_p=pivot->h;

   a->h = eq_a - max(eq_p,0) - 1;
   pivot->h = min(eq_a - 2, min(eq_a + eq_p - 2, eq_p - 1));     
   a = pivot;

   return a;
}

pArbre rotationDroite(pArbre a) {       //rotation droite du noeud
   pArbre pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    int eq_a=a->h;
    int eq_p=pivot->h;
   a->h = eq_a - min(eq_p, 0) + 1;
   pivot->h = max(eq_a + 2, max(eq_a + eq_p + 2, eq_p + 1));
   a = pivot;

   return a;
}

pArbre doubleRotationGauche(pArbre a) {     //double rotation gauche du noeud
   a->fd = rotationDroite(a->fd);           //rotation droite du fils droit de a
   return rotationGauche(a);                //rotation gauche de a
}

pArbre doubleRotationDroite(pArbre a) {     //double rotation droite du noeud
   a->fg = rotationGauche(a->fg);           //rotation gauche du fils droit de a
   return rotationDroite(a);                //rotation droite de a
}

pArbre equilibrerAVL(pArbre a) {            //equilibrage d'un AVL
   if (a->h >= 2) {
      // sous-arbre droit plus profond
      if (a->fd->h >= 0) {
         return rotationGauche(a);
      } else {
         return doubleRotationGauche(a);
      }
   } else if (a->h <= -2) {
      // sous-arbre gauche plus profond
      if (a->fg->h <= 0) {
         return rotationDroite(a);
      } else {
         return doubleRotationDroite(a);
      }
   }

   return a;
}


pArbre creerNoeud(int somme, char *ville) {
    Arbre *new = malloc(sizeof(*new));
    if (new != NULL) {
        new->somme = somme;
        new->h = 0; 
        strncpy(new->ville, ville, TAILLE_BUFFER - 1);
        new->ville[TAILLE_BUFFER - 1] = '\0';
        new->fg = NULL;
        new->fd = NULL;
    }
    return new;
}

pArbre insertionAVL(pArbre x, int e, char *c, int *h) {
    int comparaisonVille;
    if (x == NULL) {
        *h = 1;

        return creerNoeud(e, c);
    } else if (e < x->somme) {

        x->fg = insertionAVL(x->fg, e, c, h);
        *h = -*h;
    } else if (e > x->somme) {
 
        x->fd = insertionAVL(x->fd, e, c, h);
    } else {
        comparaisonVille = strcmp(c, x->ville);
        if (comparaisonVille < 0) {

            x->fg = insertionAVL(x->fg, e, c, h);
            *h = -*h;
        } else if (comparaisonVille > 0) {

            x->fd = insertionAVL(x->fd, e, c, h);
        } else {
            *h = 0;
            return x;
        }
    }

    if (*h != 0){
        x->h = x->h + *h;
        x = equilibrerAVL(x);

        if (x->h == 0){
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return x;
}



void ResultatSomme(pArbre *a, FILE *fichier) {
    char buffer[TAILLE_BUFFER];
    char ville[TAILLE_BUFFER];
    int somme;
    int h = 0;
    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        char *token = strtok(buffer, "\n");
        int colonne = 1;

        while (token != NULL) {
            char *token2 = strtok(token, ";");
            while (token2 != NULL) {
                if (colonne == 1) {
                    strncpy(ville, token2, sizeof(ville));
                } else if (colonne == 2) {
                    somme = atoi(token2);
                    *a = insertionAVL(*a, somme, ville, &h);
                }
                token2 = strtok(NULL, ";");
                colonne++;
            }
            token = strtok(NULL, "\n");
        }
    }
}



void parcoursDecroissant(pArbre a, FILE *fichierSortie) {
    if (a != NULL) {
        parcoursDecroissant(a->fd, fichierSortie);
        fprintf(fichierSortie, "%s;%d\n", a->ville, a->somme);
        parcoursDecroissant(a->fg, fichierSortie);
    }
}


int main(){
    FILE *fichier1 = fopen("additionville.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    FILE *fichier2 = fopen("additionville(villedepart).csv", "r");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    FILE *fichier3 = fopen("total_trajets_decroissant.csv", "w");
    if (fichier3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    FILE *fichier4 = fopen("total_trajet_decroissant(villededepart).csv", "w");
    if (fichier4 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }

    pArbre arbre1 = NULL;
    pArbre arbre2 = NULL;

    ResultatSomme(&arbre1, fichier1);
    printf("Fin de l'extraction des lignes du fichier.\n");
    parcoursDecroissant(arbre1, fichier3);
    printf("Fin du parcours décroissant de l'arbre.\n");

    ResultatSomme(&arbre2, fichier2);
    printf("Fin de l'extraction des lignes du fichier.\n");
    parcoursDecroissant(arbre2, fichier4);
    printf("Fin du parcours décroissant de l'arbre.\n");



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

