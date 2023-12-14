#EXEC_ouverture_fichier = ouverture_fichier
#SRC_ouverture_fichier = ouverture_fichier.c
#OBJ_ouverture_fichier = $(SRC_ouverture_fichier:.c=.o)


EXEC_main = main
SRC_main = main.c
OBJ_main = $(SRC_main:.c=.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

all: $(EXEC_main) #$(EXEC_ouverture_fichier) 

#$(EXEC_ouverture_fichier): $(OBJ_ouverture_fichier)
#		$(CC) -o $(EXEC_ouverture_fichier) $(OBJ_ouverture_fichier)

$(EXEC_main): $(OBJ_main)
		$(CC) -o $(EXEC_main) $(OBJ_main)


%.o: %.c
		$(CC) $(CFLAGS) -c $<


clean:
	@echo "Suppression des fichiers objets et exécutables"
	rm -f progc/$(OBJ_main) progc/$(EXEC_main)

.PHONY: all clean
