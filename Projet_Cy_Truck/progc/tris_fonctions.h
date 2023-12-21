#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>  // Pour les fichiers en arguments
#include <string.h>     // Pour strcmp (--abr et tout en argument)
#include <unistd.h>     // Pour acces (verifie si on a le droit de lecture sur un fichier en argument)
#include <math.h>
#define BUFFER_SIZE 512


/* typedef struct arbre{
	int valeur;
	struct arbre *fg;
	struct arbre *fd;
}Arbre;*/

typedef struct avl{
	int c1;
    char * c2;
	struct AVL *fg;
	struct AVL *fd;
	int equilibre;
    int hauteur;
}AVL;


void debug(char* msg);
void equilibre(AVL *pArbre, int *h);
AVL *creationAVL(int a1, char * a2);
int max2(int a, int b);
int min2(int a, int b);
int min3(int a, int b, int c);
int max3(int a, int b, int c);
int equilibre(AVL *pAVL);
int equilibrage(AVL *pAVL);
AVL *rotationG(AVL *pArbre);
AVL *rotationD(AVL *pArbre);
AVL *doublerotationG(AVL *pArbre);
AVL *doublerotationD(AVL *pArbre);
AVL *equilibreAVL(AVL *pArbre);
AVL *insertionAVL(AVL *pArbre, int elt, int *h);
int existeFilsDroitAVL(AVL *pArbre);
int existeFilsGaucheAVL(AVL * pArbre);
AVL *suppMinAVL(AVL *pArbre, int *h, int *pelt);
AVL *suppressionAVL(AVL *pAVL, int elt, int *h);
void displayArbreAVL(AVL *pArbre);
void parcoursPrefixeAVL(AVL *pArbre);
void parcoursInfixeAVL(AVL *pArbre);
int rechercheAVL(AVL *pArbre, int elmt);
int checkAVL(AVL *pArbre);
