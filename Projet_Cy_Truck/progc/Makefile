EXEC_filtre_s = filtre_s
SRC_filtre_s = filtre_s.c
OBJ_filtre_s = $(SRC_filtre_s:.c=.o)

EXEC_etape1_filtre_t = etape1_filtre_t
SRC_etape1_filtre_t = etape1_filtre_t.c
OBJ_etape1_filtre_t = $(SRC_etape1_filtre_t:.c=.o)

EXEC_etape2_IsoCol2_3 = etape2_IsoCol2_3
SRC_etape2_IsoCol2_3 = etape2_IsoCol2_3.c
OBJ_etape2_IsoCol2_3 = $(SRC_etape2_IsoCol2_3:.c=.o)

EXEC_etape3_comptage = etape3_comptage
SRC_etape3_comptage = etape3_comptage.c
OBJ_etape3_comptage = $(SRC_etape3_comptage:.c=.o)

EXEC_etape4_triersomme = etape4_triersomme
SRC_etape4_triersomme = etape4_triersomme.c
OBJ_etape4_triersomme = $(SRC_etape4_triersomme:.c=.o)

EXEC_etape5_traitement_finale = etape5_traitement_finale
SRC_etape5_traitement_finale = etape5_traitement_finale.c
OBJ_etape5_traitement_finale = $(SRC_etape5_traitement_finale:.c=.o)


CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(EXEC_filtre_s) $(EXEC_etape1_filtre_t) $(EXEC_etape2_IsoCol2_3) $(EXEC_etape3_comptage) $(EXEC_etape4_triersomme) $(EXEC_etape5_traitement_finale)


$(EXEC_filtre_s): $(OBJ_filtre_s)
		$(CC) -o $(EXEC_filtre_s) $(OBJ_filtre_s)

$(EXEC_etape1_filtre_t): $(OBJ_etape1_filtre_t)
		$(CC) -o $(EXEC_etape1_filtre_t) $(OBJ_etape1_filtre_t)

$(EXEC_etape2_IsoCol2_3): $(OBJ_etape2_IsoCol2_3)
		$(CC) -o $(EXEC_etape2_IsoCol2_3) $(OBJ_etape2_IsoCol2_3)

$(EXEC_etape3_comptage): $(OBJ_etape3_comptage)
		$(CC) -o $(EXEC_etape3_comptage) $(OBJ_etape3_comptage)

$(EXEC_etape4_triersomme): $(OBJ_etape4_triersomme)
		$(CC) -o $(EXEC_etape4_triersomme) $(OBJ_etape4_triersomme)

$(EXEC_etape5_traitement_finale): $(OBJ_etape5_traitement_finale)
		$(CC) -o $(EXEC_etape5_traitement_finale) $(OBJ_etape5_traitement_finale)

%.o: %.c
		$(CC) $(CFLAGS) -c $<


clean:
	@echo "Suppression des fichiers objets et exécutables"
	rm -f progc/$(OBJ_filtre_s) progc/$(EXEC_filtre_s)
	rm -f progc/$(OBJ_etape1_filtre_t) progc/$(EXEC_etape1_filtre_t)
	rm -f progc/$(OBJ_etape2_IsoCol2_3) progc/$(EXEC_etape2_IsoCol2_3)
	rm -f progc/$(OBJ_etape3_comptage) progc/$(EXEC_etape4_triersomme)
	rm -f progc/$(OBJ_etape4_triersomme) progc/$(EXEC_etape4_triersomme)
	rm -f progc/$(OBJ_etape5_traitement_finale) prog/$(EXEC_etape5_traitement_finale)

.PHONY: all clean
