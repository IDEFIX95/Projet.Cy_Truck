EXEC_tri_d2 = tri_d2
SRC_tri_d2 = tri_d2.c
OBJ_tri_d2 = $(SRC_tri_d2:.c=.o)

EXEC_filtre_t = filtre_t
SRC_filtre_t = filtre_t.c
OBJ_filtre_t = $(SRC_filtre_t:.c=.o)

EXEC_filtre_s = filtre_s
SRC_filtre_s = filtre_s.c
OBJ_filtre_s = $(SRC_filtre_s:.c=.o)

EXEC_main = main
SRC_main = main.c
OBJ_main = $(SRC_main:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(EXEC_main) $(EXEC_tri_d2) $(EXEC_filtre_t) $(EXEC_filtre_s)

$(EXEC_tri_d2): $(OBJ_tri_d2)
		$(CC) -o $(EXEC_tri_d2) $(OBJ_tri_d2)

$(EXEC_main): $(OBJ_main)
		$(CC) -o $(EXEC_main) $(OBJ_main)

$(EXEC_filtre_t): $(OBJ_filtre_t)
		$(CC) -o $(EXEC_filtre_t) $(OBJ_filtre_t)

$(EXEC_filtre_s): $(OBJ_filtre_s)
		$(CC) -o $(EXEC_filtre_s) $(OBJ_filtre_s)

%.o: %.c
		$(CC) $(CFLAGS) -c $<


clean:
	@echo "Suppression des fichiers objets et exécutables"
	rm -f progc/$(OBJ_main) progc/$(EXEC_main)
	rm -f progc/$(OBJ_tri_d2) progc/$(EXEC_tri_d2)
	rm -f progc/$(OBJ_filtre_t) progc/$(EXEC_filtre_t)
	rm -f progc/$(OBJ_filtre_s) progc/$(EXEC_filtre_s)

.PHONY: all clean
