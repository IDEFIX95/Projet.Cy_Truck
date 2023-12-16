#!/bin/bash
#cd progc
#make all > /dev/null 2> $
#cd ..


# Variables des Options



fichier_d_entrer="data/data.csv"
fichier_d_aide="progc/help.txt"
dossier_temp="temp"
dossier_images="images"
option_oblig=0



if [ "$1" == $fichier_d_entrer ]; then     # Regarde si le 1er argument de la ligne de commande est bien le chemin vers le fichier de donnée d'entrer.
    echo "Le chemin vers le fichier $fichier_d_entrer est bien le premier argument de la ligne de commande."
else
    echo "Le chemin vers le fichier $fichier_d_entrer n'est pas mit comme premier argument"
    exit 1
fi


# Vérifier si le fichier source C existe
if [ -e "progc/main.c" ]; then
    echo "Le fichier source C main.c est présent."
    if [ ! -e "progc/main" ]; then
    # Se déplacer dans le répertoire progc
    cd progc

    # Compilation du fichier C
    make all

    # Vérification du statut de la compilation
    if [ $? -eq 0 ]; then
        echo "La compilation s'est bien déroulée. L'exécutable main a été créé."
    else
        echo "Erreur lors de la compilation."
    fi

    # Revenir au répertoire initial
   cd ..
    else 
        echo "L'executable C est present sur le disque dur"
    fi
else
    echo "Le fichier source C main.c n'est pas trouvé. Lancement de la compilation."
fi

if [[ ! -d "$dossier_images" && ! -d "$dossier_temp" ]];then
    mkdir images
    mkdir temp
else
    rm -f temp/*
fi



##Gestion des Options (Parcour de la la ligne de Commande pour reperer les Options)

for i in "$@" ;do                             # La condition qui me permet de lancer l'option aide et donc de faire apparaitre le fichier help.
    if [ "$i" == $fichier_d_entrer ] ;then
        option_oblig=$(("$option_oblig"+1))
    fi
    if [ "$i" == "-h" ];then
        echo -e "Le fichier help est apparue dans le dossier progc\n"
        gedit "$fichier_d_aide"
        exit 1  
    fi
    if [ "$i" == "-d1" ];then
        # Enregistrez le temps de début
        debut_timer_d1=$(date +%s)
        
        awk -F";" '/;1;/ {compteur[$6] += 1} END {for (nom in compteur) print nom " " compteur[nom]}' data/data.csv |sort -t" " -k3nr | head -10 > demo/test_final.csv
        
        fin_timer_d1=$(date +%s)

        # Calculez la durée totale en secondes
        duree_option_d1=$((fin_timer_d1 - debut_timer_d1))

        option_oblig=$(("$option_oblig"+1))

        # Affichez la durée
        echo -e "\nLe traitement de l'option -d1 a pris $duree_option_d1 secondes.\n"
        
        #awk '!seen[$2]++ {print $0}' demo/test_final.csv
        #sort -t";" -n -k1 data/data.csv > demo/test.csv
        #awk -F";" '{print $1 ";" $2 ";" $6}' demo/test.csv > demo/test1.csv
    fi
    if [ "$i" == "-d2" ];then
        echo "hello world"
        option_oblig=$(("$option_oblig"+1))
    fi
done


if (( "$option_oblig" < 2 )); then
   echo "pas assez d'arguments dans la ligne de commande"
    exit 1
fi



echo "Analyse des options terminées"

exit 0
