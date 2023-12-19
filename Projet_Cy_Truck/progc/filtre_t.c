#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_VILLE_LENGTH 50

struct VilleData {
    char nomVille[MAX_VILLE_LENGTH];
    int nbTrajets;
    int nbConducteurs;
};

void processLine(char *line, struct VilleData *villeData, FILE *outputFile) {
    char *token = strtok(line, ";");
    int column = 1;

    while (token != NULL) {
        if (column == 3) {
            strncpy(villeData->nomVille, token, sizeof(villeData->nomVille));
        } else if (column == 4 || column == 6) {
            // Assuming column 4 contains the driver's name and column 6 contains route ID
            if (*token == villeData->nomVille){
                return;
            } else {
                villeData->nbTrajets++;
            }
            villeData->nbConducteurs++;
            
        }

        token = strtok(NULL, ";");
        column++;
    }

    // Write results to the output file
    fprintf(outputFile, "%s;%d;%d\n", villeData->nomVille, villeData->nbTrajets, villeData->nbConducteurs);
}

int main() {
    FILE *inputFile = fopen("demo/t_intermediaire.csv", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen("temp/t_filtre.csv", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    struct VilleData villeData = {0}; // Initialize counts to zero

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        processLine(line, &villeData, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
