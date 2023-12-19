#!/bin/bash
cd progc
make all > /dev/null 2> $
cd ..


# Variables des Options



fichier_d_entrer="data/data.csv"
fichier_d_aide="progc/help.txt"

dossier_temp="temp"
dossier_images="images"

option_t="-t"

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
        
        awk -F";" '/;1;/ {compteur[$6] += 1} END {for (nom in compteur) print nom ";" compteur[nom]}' data/data.csv |sort -t";" -k2nr > demo/d1_final.csv
        
        fin_timer_d1=$(date +%s)

        # Calculez la durée totale en secondes
        duree_option_d1=$((fin_timer_d1 - debut_timer_d1))

        option_oblig=$(("$option_oblig"+1))

        # Affichez la durée
        echo -e "\nLe traitement de l'option -d1 a pris $duree_option_d1 secondes.\n"
    fi

    if [ "$i" == "-d2" ];then
        # Enregistrez le temps de début
        debut_timer_d2=$(date +%s)
    
        #awk -F";" ' NR > 1 {print $5 ";" $6}' data/data.csv > progc/d2_final1.csv
        #touch progc/d2_vraifinal.csv
        #./progc/tri_d2
        #awk -F";" '/;1;/ {compteur[$6] += $5} END {for (nom in compteur) print nom ";" compteur[nom]}' data/data.csv |sort -t";" -k2nr | head -10 > demo/d2_final.csv
        awk -F";" '{compteur[$6] += $5} END {for (nom in compteur) print nom ";" compteur[nom]}' data/data.csv |sort -t";" -k2nr | head -10 > demo/d2_final.csv
        fin_timer_d2=$(date +%s)

        # Calculez la durée totale en secondes
        duree_option_d2=$((fin_timer_d2 - debut_timer_d2))

        option_oblig=$(("$option_oblig"+1))

        # Affichez la durée
        echo -e "\nLe traitement de l'option -d2 a pris $duree_option_d2 secondes.\n"
    fi

    if [ "$i" == "-l" ];then
        # Enregistrez le temps de début
        debut_timer_l=$(date +%s)
        awk -F";"  '{compteur[$1] += $5} END {for (id_trajet in compteur) print id_trajet ";" compteur[id_trajet]}' data/data.csv |sort -t";" -k2nr | head -10 | sort -t";" -k1n > demo/l_final.csv
        fin_timer_l=$(date +%s)

        # Calculez la durée totale en secondes
        duree_option_l=$((fin_timer_l - debut_timer_l))

        option_oblig=$(("$option_oblig"+1))

        # Affichez la durée
        echo -e "\nLe traitement de l'option -l a pris $duree_option_l secondes.\n"
    fi

    if [ "$i" == $option_t ];then
        # Enregistrez le temps de début
        debut_timer_t=$(date +%s)
        awk -F";" '{print $1 ";" $3 ";" $4 ";" $6}' data/data.csv > demo/t_intermediaire.csv
        touch temp/t_filtre.csv
        ./progc/filtre_t
        #filtrage en .c
        #On peut faire un head -10 sur le fichier de tri a la fin
        fin_timer_t=$(date +%s)

        # Calculez la durée totale en secondes
        duree_option_t=$((fin_timer_t - debut_timer_t))

        
        option_oblig=$(("$option_oblig"+1))

        # Affichez la durée
        echo -e "\nLe traitement de l'option -t a pris $duree_option_t secondes.\n" 
    fi

    if [ "$i" == "-supps_fichiers_demo" ];then
        rm -f demo/*.csv
        option_oblig=$(("$option_oblig"+1))
    fi

    if [ "$i" == "-fichier_reference" ];then
        sort -t";" -n -k1 data/data.csv > demo/ref.csv
        awk -F";" '{print $1 ";" $5 ";" $6}' demo/ref.csv > demo/reference_offi.csv
        option_oblig=$(("$option_oblig"+1))
    fi

done

if (( "$option_oblig" < 2 )); then
   echo "pas assez d'arguments dans la ligne de commande"
    exit 1
fi

echo "Analyse des options terminées"

exit 0
