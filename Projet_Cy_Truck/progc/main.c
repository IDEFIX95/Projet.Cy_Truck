#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>  // Pour les fichiers en arguments
#include <string.h>     // Pour strcmp (--abr et tout en argument)
#include <unistd.h>     // Pour acces (verifie si on a le droit de lecture sur un fichier en argument)
#include <math.h>
#define BUFFER_SIZE 512




int main(int argc, char * argv[]){

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-s") == 0){
            printf("Ces options font bien partir des options disponible\n");
        }
        else{
            printf("Cette options ne fait pas partis des options disponible pour le tri en C\n");
        }
    }
    return 0;
}
