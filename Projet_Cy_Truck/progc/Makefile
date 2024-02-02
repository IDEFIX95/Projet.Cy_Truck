EXEC_filtre_s = filtre_s
SRC_filtre_s = filtre_s.c
OBJ_filtre_s = $(SRC_filtre_s:.c=.o)

EXEC_trier_fichier_s = trier_fichier_s
SRC_trier_fichier_s = trier_fichier_s.c
OBJ_trier_fichier_s = $(SRC_trier_fichier_s:.c=.o)

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

EXEC_etape5_traitement_final = etape5_traitement_final
SRC_etape5_traitement_final = etape5_traitement_final.c
OBJ_etape5_traitement_final = $(SRC_etape5_traitement_final:.c=.o)

EXEC_etape6_parcours_decroissant_alphabetique = etape6_parcours_decroissant_alphabetique
SRC_etape6_parcours_decroissant_alphabetique = etape6_parcours_decroissant_alphabetique.c
OBJ_etape6_parcours_decroissant_alphabetique = $(SRC_etape6_parcours_decroissant_alphabetique:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

PROGRAMS = $(EXEC_filtre_s) $(EXEC_trier_fichier_s) $(EXEC_etape1_filtre_t) $(EXEC_etape2_IsoCol2_3) $(EXEC_etape3_comptage) $(EXEC_etape4_triersomme) $(EXEC_etape5_traitement_final) $(EXEC_etape6_parcours_decroissant_alphabetique)

all: check_sources $(PROGRAMS)

check_sources:
	@for file in $(SRC_filtre_s) $(SRC_trier_fichier_s) $(SRC_etape1_filtre_t) $(SRC_etape2_IsoCol2_3) $(SRC_etape3_comptage) $(SRC_etape4_triersomme) $(SRC_etape5_traitement_final) $(SRC_etape6_parcours_decroissant_alphabetique); do \
		if [ ! -e $$file ]; then \
			echo "Erreur: Le fichier $$file n'existe pas."; \
			exit 1; \
		fi; \
	done
	@echo "Tous les fichiers sources existent."

$(EXEC_filtre_s): $(OBJ_filtre_s)
	$(CC) -o $(EXEC_filtre_s) $(OBJ_filtre_s)

$(EXEC_trier_fichier_s): $(OBJ_trier_fichier_s)
	$(CC) -o $(EXEC_trier_fichier_s) $(OBJ_trier_fichier_s)

$(EXEC_etape1_filtre_t): $(OBJ_etape1_filtre_t)
	$(CC) -o $(EXEC_etape1_filtre_t) $(OBJ_etape1_filtre_t)

$(EXEC_etape2_IsoCol2_3): $(OBJ_etape2_IsoCol2_3)
	$(CC) -o $(EXEC_etape2_IsoCol2_3) $(OBJ_etape2_IsoCol2_3)

$(EXEC_etape3_comptage): $(OBJ_etape3_comptage)
	$(CC) -o $(EXEC_etape3_comptage) $(OBJ_etape3_comptage)

$(EXEC_etape4_triersomme): $(OBJ_etape4_triersomme)
	$(CC) -o $(EXEC_etape4_triersomme) $(OBJ_etape4_triersomme)

$(EXEC_etape5_traitement_final): $(OBJ_etape5_traitement_final)
	$(CC) -o $(EXEC_etape5_traitement_final) $(OBJ_etape5_traitement_final)

$(EXEC_etape6_parcours_decroissant_alphabetique): $(OBJ_etape6_parcours_decroissant_alphabetique)
	$(CC) -o $(EXEC_etape6_parcours_decroissant_alphabetique) $(OBJ_etape6_parcours_decroissant_alphabetique)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@echo "Suppression des fichiers objets et exécutables"
	rm -f progc/$(OBJ_filtre_s) progc/$(EXEC_filtre_s)
	rm -f progc/$(OBJ_trier_fichier_s) progc/$(EXEC_trier_fichier_s)
	rm -f progc/$(OBJ_etape1_filtre_t) progc/$(EXEC_etape1_filtre_t)
	rm -f progc/$(OBJ_etape2_IsoCol2_3) progc/$(EXEC_etape2_IsoCol2_3)
	rm -f progc/$(OBJ_etape3_comptage) progc/$(EXEC_etape3_comptage)
	rm -f progc/$(OBJ_etape4_triersomme) progc/$(EXEC_etape4_triersomme)
	rm -f progc/$(OBJ_etape5_traitement_final) progc/$(EXEC_etape5_traitement_final)
	rm -f progc/$(OBJ_etape6_parcours_decroissant_alphabetique) progc/$(EXEC_etape6_parcours_decroissant_alphabetique)
	rm -f progc/terminal

.PHONY: all clean check_sources
