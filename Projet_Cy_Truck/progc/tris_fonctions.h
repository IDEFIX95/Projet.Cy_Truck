#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>  // Pour les fichiers en arguments
#include <string.h>     // Pour strcmp (--abr et tout en argument)
#include <unistd.h>     // Pour acces (verifie si on a le droit de lecture sur un fichier en argument)
#include <math.h>
#define BUFFER_SIZE 512


typedef struct arbre{
	int valeur;
	struct arbre *fg;
	struct arbre *fd;
}Arbre;

typedef struct avl{
	int valeur;
	struct AVL *fg;
	struct AVL *fd;
	int equilibre;
}AVL;
