#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>  // Pour les fichiers en arguments
#include <string.h>     // Pour strcmp (--abr et tout en argument)
#include <unistd.h>     // Pour acces (verifie si on a le droit de lecture sur un fichier en argument)
#include <math.h>
#define BUFFER_SIZE 512
#include "tris_fonctions.h"



int main(int argc, char * argv[]){
    printf("hello world");
    return 0;
}