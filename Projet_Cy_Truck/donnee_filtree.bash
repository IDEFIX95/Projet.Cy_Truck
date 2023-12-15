#!/bin/bash
#cd progc
#make all > /dev/null 2> $
#cd ..


# Variables des Options

conducteur_plus=0

fichier_d_entrer="data/data.csv"
fichier_d_aide="progc/help.txt"
dossier_temp="temp"
dossier_images="images"
option_oblig=0





##Gestion des Options (Parcour de la la ligne de Commande pour reperer les Options)

for i in $* ;do                             # La condition qui me permet de lancer l'option aide et donc de faire apparaitre le fichier help.
    if [ "$i" == $fichier_d_entrer ] ;then
        option_oblig=$(("$option_oblig"+1))
    fi
    if [ "$i" == "-h" ];then
        echo -e "Le fichier help est apparue dans le dossier progc\n"
        gedit "$fichier_d_aide"
        exit 1  
    fi
    if [ "$i" == "-d1" ];then
        sort -t";" -n -k1 data/data.csv > demo/test.csv
        awk -F";" '{print $1 ";" $2 ";" $6}' demo/test.csv > demo/test_final.csv
    fi
    if [ "$i" == "-d2" ];then
        echo "hello world"
    fi
done


   
# Enregistrez le temps de début
start_time=$(date +%s)




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



 



#if (( "$option_oblig" < 2 )); then
#    echo "pas assez d'arguments dans la ligne de commande"
#    exit 1
#fi



#if [ "$conducteur_plus" -eq 1 ];
#       then

       #echo "bien joué"

       #tail -n+2 "$fichierdentree" | cut -d';' -f"$numero_station","$numero_temperature","$numero_temp_min","$numero_temp_max" | sort -t, -k1 > temp1.csv
       #if [ "$option_geo" -eq 1 ];then
       #     rm "$fichierdentree"
       #fi
       #if [ "$option_date" -eq 1 ];then
       #     rm datefiltrer.csv
       #fi 
       
       #./tri -f temp1.csv -o temp1_sortie.csv  -t1 #-n "$tri" -t1 #"$numero"    
#fi



end_time=$(date +%s)

# Calculez la durée totale en secondes
duration=$((end_time - start_time))

# Affichez la durée
echo -e "Le traitement a pris $duration secondes.\n"



echo "Analyse des options terminée"

exit 0
