#!/bin/bash
#cd progc
#make all > /dev/null 2> $
#cd ..

fichier_d_entrer="data/data.csv"
fichier_d_aide="help.txt"
dossier_temp="temp"
dossier_images="images"
option_oblig=0

# Enregistrez le temps de début
start_time=$(date +%s)

for i in $* ;do                             # La condition qui me permet de lancer l'option aide et donc de faire apparaitre le fichier help.
    if [ "$i" == $fichier_d_entrer ] ;then
       option_oblig=$(("$option_oblig"+1))
    fi
    if [ "$i" == "-h" ];then
        echo "un fichier help est apparue dans le dossier progc"
        cat progc/help.txt
        exit 1
    fi
done


if [ "$1" == $fichier_d_entrer ]; then     # Regarde si le 1er argument de la ligne de commande est bien le chemin vers le fichier de donnée d'entrer.
    echo "Le chemin vers le fichier $fichier_d_entrer est bien le premier argument de la ligne de commande."
else
    echo "Le chemin vers le fichier $fichier_d_entrer n'est pas mit comme premier argument"
    exit 1
fi


if (( "$option_oblig" < 2 )); then
    echo "pas assez d'arguments dans la ligne de commande"
    exit 1
fi

if [[ ! -d "$dossier_images" && ! -d "$dossier_temp" ]];then
    mkdir images
    mkdir temp
else
    rm -f temp/*
fi

end_time=$(date +%s)

# Calculez la durée totale en secondes
duration=$((end_time - start_time))

# Affichez la durée
echo -e "Le traitement a pris $duration secondes.\n"



echo "Analyse des options terminée"

exit 0
