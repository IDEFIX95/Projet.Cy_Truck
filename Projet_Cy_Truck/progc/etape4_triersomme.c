// ÉTAPE 4

// Cette étape permet de calculer le nombre total de trajet des villes à l'aide d'un AVL et trier dans l'ordre décroissant.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "etape4_triersomme.h"

#define TAILLE_BUFFER 1024



int max(int a, int b) {         // Retourne le maximum entre deux entiers
  if (a > b) {
    return a;
  } 
  else {
    return b;
  }
}

int min(int a, int b) {         // Retourne le minimum entre deux entiers
  if (a < b) {
    return a;
  } 
  else {
    return b;
  }
}

pArbre rotationGauche(pArbre a) {        // Rotation gauche du noeud
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




pArbre rotationDroite(pArbre a) {        // Rotation droite du noeud
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





pArbre doubleRotationGauche(pArbre a) {     // Double rotation gauche du noeud
   a->fd = rotationDroite(a->fd);           // Rotation droite du fils droit de a
   return rotationGauche(a);                // Rotation gauche de a

}





pArbre doubleRotationDroite(pArbre a) {     // Double rotation droite du noeud
   a->fg = rotationGauche(a->fg);           // Rotation gauche du fils droit de a
   return rotationDroite(a);                // Rotation droite de a
}





pArbre equilibrerAVL(pArbre a) {            // Équilibrage d'un AVL
   if (a->h >= 2) {
      // Sous-arbre droit plus profond
      if (a->fd->h >= 0) {
         return rotationGauche(a);
      } 
      else {
         return doubleRotationGauche(a);
      }
   } 
   else if (a->h <= -2) {
      // Sous-arbre gauche plus profond
      if (a->fg->h <= 0) {
         return rotationDroite(a);
      } 
      else {
         return doubleRotationDroite(a);
      }
   }
   return a;

}



// Fonction de création d'un nouveau nœud avec une somme et une ville donnée
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
    }
    else if (e < x->somme) {
        x->fg = insertionAVL(x->fg, e, c, h);
        *h = -*h;
    }
    else if (e > x->somme) {
        x->fd = insertionAVL(x->fd, e, c, h);
    } 
    else {
        comparaisonVille = strcmp(c, x->ville);
        if (comparaisonVille < 0) {
            x->fg = insertionAVL(x->fg, e, c, h);
            *h = -*h;
        } 
        else if (comparaisonVille > 0) {
            x->fd = insertionAVL(x->fd, e, c, h);
        } 
        else {
            *h = 0;
            return x;
        }
    }

    if (*h != 0){
        x->h = x->h + *h;
        x = equilibrerAVL(x);
        if (x->h == 0){
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return x;
}



// Fonction pour extraire les résultats des fichier additionville afin de mettre dans l'AVL pour trier
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





// Fonction de parcours décroissant de l'arbre et écriture dans un fichier de sortie
void parcoursDecroissant(pArbre a, FILE *fichierSortie) {
    if (a != NULL) {
        parcoursDecroissant(a->fd, fichierSortie);
        fprintf(fichierSortie, "%s;%d\n", a->ville, a->somme);
        parcoursDecroissant(a->fg, fichierSortie);
    }
}



// Libération de l'arbre AVL
void libererAVL(pArbre a) {
    if (a != NULL) {
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a);
    }
}



int main(){
    FILE *fichier1 = fopen("temp/additionville.csv", "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }

    FILE *fichier2 = fopen("temp/addition_ville_villedepart.csv", "r");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        fclose(fichier1);
        return 1;
    }



    FILE *fichier3 = fopen("temp/total_trajets_decroissant.csv", "w");
    if (fichier3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie.");
        fclose(fichier1);
        fclose(fichier2);
        return 1;
    }



    FILE *fichier4 = fopen("temp/total_trajet_decroissant_villededepart.csv", "w");
    if (fichier4 == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie.");
        fclose(fichier1);
        fclose(fichier2);
        fclose(fichier3);
        return 1;
    }
    

    // Initialisation des arbres
    pArbre arbre1 = NULL;
    pArbre arbre2 = NULL;


    // Traitement du fichier 1
    ResultatSomme(&arbre1, fichier1);
    parcoursDecroissant(arbre1, fichier3);


    // Traitement du fichier 2
    ResultatSomme(&arbre2, fichier2);
    parcoursDecroissant(arbre2, fichier4);


    // Fermeture des fichiers
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichier3);
    fclose(fichier4);


    // Libération des arbres
    libererAVL(arbre1);
    libererAVL(arbre2);

    printf("Traitement de l'étape 4 terminé avec succès.\n");

    return 0;

}
