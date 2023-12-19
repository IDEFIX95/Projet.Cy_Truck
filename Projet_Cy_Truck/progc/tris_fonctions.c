#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>  // Pour les fichiers en arguments
#include <string.h>     
#include <unistd.h>     // Pour acces (verifie si on a le droit de lecture sur un fichier en argument)
#include <math.h>
#define BUFFER_SIZE 512
#include "tris_fonctions.h"



void debug(char* msg){
	printf("%s\ n", msg);
	fflush(stdout);
}

void equilibre(AVL *pArbre, int *h){
	if(pArbre->equilibre == 2){
		*h = 2;
	}
}

AVL *creationAVL(int elt){
	AVL *pAVL = NULL;
	pAVL = malloc(sizeof(AVL));
	pAVL->valeur = elt;
	pAVL->fg = NULL;
	pAVL->fd = NULL;
	return pAVL;
}

int max2(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}

int min2(int a, int b){
	int r = 0;
	if(a < b){
		r = a;
	}
	else{
		r = b;
	}
	return r;
}

int min3(int a, int b, int c){
	if(a < b && a < c){
		return a;
	}
	else if(b < a && b < c){
		return b;
	}
	else if(c < a && c < b){
		return c;
	}
}

int max3(int a, int b, int c){
	if(a > b && a > c){
		return a;
	}
	else if(b > a && b > c){
		return b;
	}
	else if(c > a && c > b){
		return c;
	}
}

int equilibre(AVL *pAVL){
	if(pAVL == NULL){
		return 0;
	}
	return pAVL->equilibre;
}

int equilibrage(AVL *pAVL){
	if(pAVL == NULL){
		return 0;
	}
	return equilibre(pAVL->fg) - equilibre(pAVL->fd);
}

AVL *rotationG(AVL *pArbre){
	AVL *pivot;
	int eq_a;
	int eq_p;
	pivot = pArbre->fd:
	pArbre->fd = pivot->fg;
	pivot->fg = pArbre;
	eq_a = pArbre->equilibre;
	eq_p = pivot->equilibre;
	pArbre->equilibre = eq_a - max2(eq_p, 0) - 1;
	pivot->equilibre = min3(eq_a - 2, eq_a + eq_ - 2, eq_p - 1);
	pArbre = pivot;
	return pArbre;
}

AVL *rotationD(AVL *pArbre){
	AVL *pivot;
	int eq_a;
	int eq_p;
	pivot = pArbre->fg;
	pArbre->fg = pivot->fd;
	pivot->fd = pArbre;
	eq_a = pArbre->equilibre;
	eq_p = pivot->equilibre;
	pArbre->equilibre = eq_a -min 2(eq_p, 0) + 1;
	pivot->equilibre = max3(eq_a + 2; eq_a + eq_p + 2, eq_p + 1);
	pArbre->pivot;
	return pArbre;
}

AVL *doublerotationG(AVL *pArbre){
	pArbre->fd = rotationD(pArbre->fd);
	return rotatioG(pArbre);
}

AVL *doublerotationD(AVL *pArbre){
	pArbre->fg = rotationG(pArbre->fg);
	return rotationD(pArbre);
}

AVL *equilibreAVL(AVL *pArbre){
	if(pArbre->equilibre >= 2){
		if(pArbre->fd->equilibre >= 0){
			debug("g");
			return rotationG(pArbre);
		}
		else{
			debug("dg");
			return doublerotationG(pArbre);
		}
	}
	else if(pArbre->equilibre <= -2){
		if(pArbre->fg->equilibre <= 0){
			debug("d");
			return rotationD(pArbre);
		}
		else{
			debug("dd");
			return doublerotationD(pArbre);
		}
	}
	return pArbre;
}

AVL *insertionAVL(AVL *pArbre, int elt, int *h){
	if(h == NULL){
		exit(1);
	}
	if(pArbre == NULL){
		*h = 1;
		return (creationAVL(elt));
	}
	else if(elt < pArbre->valeur){
		pArbre->fg = insertionAVL(pArbre->fg, elt, h);
		*h = -*h;
	}
	else if(elt > pArbre->valeur){
		pArbre->fd = insertionAVl(pArbre->fd, elt, h);
	}
		*h = 0;
		return pArbre;
	}
	else{
		*h = 0;
		return pArbre;
	}
	if(*h != 0){
		pArbre->equilibre = pArbre->equilibre + *h;
		pArbre = equilibreAVL(pArbre);
			if(pArbre->equilibre == 0){
				*h = 0;
			}
			else{
				*h = 1;
			}
	}
	return pArbre;
}


int existeFilsDroitAVL(AVL *pArbre){
	if(pArbre->fd == NULL){
		return 0;
	}
	else{
		return 1;
	}
}

AVL *suppMinAVL(AVL *pArbre, int *h, int *pelt){
	AVL *tmp;
	if(pArbre->fg == NULL){
		*pelt = pArbre->valeur;
		tmp = pArbre;
		pArbre = pArbre->fd;
		free(tmp);
		*h = -1;
		return pArbre;
	}
	else{
	pArbre->fg = suppMinAVL(pArbre->fg, h, pelt);
	*h = -*h;
	}
	if(*h != 0){
		pArbre->equilibre = pArbre->equilibre + *h;
		if(pArbre->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
		}
	}
	return pArbre;
}
 
AVL *suppressionAVL(AVL *pAVL, int elt, int *h){
 	AVL *tmp;
 	if(pAVL == NULL){
 		*h = 1;
 		return pAVL;
 	}
 	else if(elt > pAVL->valeur){
 		pAVL->fd = suppressionAVL(pAVL->fd, elt, h);
 	}
 	else if(elt < pAVL->valeur){
 		pAVL->fg = suppressionAVL(pAVL->fg, elt, h);
 		*h = -*h;
 	}
 	else if(existeFilsDroitAVL(pAVL)){
 		pAVL->fg = suppMinAVL(pAVL->fd, h, &pAVL->valeur);
 	}
 	else{
 	tmp = pAVl;
 	pAVL = pAVL->fg;
 	free(tmp);
 	*h = -1;
 	}
 	if(*h != 0){
 		pAVL->equilibre = pAVL->equilibre + *h;
 		if(pAVL->equilibre == 0){
 			*h = 0;
 		}
 		else{
 			*h = 1;
 		}
 	}
 	return pAVL;
}
 
void displayArbreAVL(AVL *pArbre){
 	if(pArbre == NULL){
 		exit(1);
 	}
 	printf("[%02d] \n", pArbre->valeur);
}

void parcoursPrefixeAVL(AVL *pArbre){
	if(pArbre != NULL){
		displayArbreAVL(pArbre);
		parcoursPrefixeAVL(pArbre->fg);
		parcoursPrefixeAVL(pArbre->fd);
	}
}

void parcoursInfixeAVL(AVL *pArbre){
	if(pArbre != NULL){
		parcoursInfixeAVL(pArbre->fg);
		displayArbreAVL(pArbre);
		parcoursInfixeAVL(pArbre->fd);
	}
}

int rechercheAVL(AVL *pArbre, int elmt){
	if(pArbre == NULL){
		return 1;
	}
	else if(pArbre->valeur == elmt){
		return 0;
	}
	else if(elmt < pArbre->valeur == elmt){
		return rechercheAVL(pArbre->fg, elmt);
	}
	else{
		return rechercheAVL(pArbre->fd, elmt);
	}
}

int checkAVL(AVL *pArbre){
	int ret = 1;
	if(pArbre != NULL){
		ret = 0;
		if(pArbre->equilibre <= 1 && pArbre->equilibre >= -1){
			if(checkAVL(pArbre->fg)){
				ret = checkAVL(pArbre->fd);
			}
		}
	}
	return ret;
}
