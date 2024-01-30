#!/bin/bash
cd progc
make all > /dev/null 2> $
cd ..


# Variables des options.


fichier_d_entrer="$1"
fichier_d_aide="progc/help.txt"

dossier_data="data"
dossier_temp="temp"
dossier_images="images"

option_t="-t"

option_oblig=0

#--------------------------------------------------------------------------------------------------------------#

# Vérification de l'existance des logiciels pour la partie graphique (Gnuplot).

logiciels=("gnuplot" "convert")

for logiciel in "${logiciels[@]}"
do
    if command -v "$logiciel" &> /dev/null 
    then
        echo "Les logiciels nécessaires sont installés sur votre système."
    else
        echo "les logiciels nécessaires ne sont pas installés sur votre système. Installation en cours..."
        # Installation.
        sudo apt-get update
        sudo apt-get install gnuplot imagemagick

        # Vérification de l'installation.
        if [ $? -eq 0 ]; then
            echo "Les logiciels ont été installés avec succès."
        else
            echo "Erreur lors de l'installation des logiciels."
        fi
    fi
done

#--------------------------------------------------------------------------------------------------------------#

if [ "$#" -lt 1 ];then
    echo "Erreur : Le chemin vers le dossier data est obligatoire en tant que 1er argument."
    exit 1
fi

# Verifier si au moins un fichier .csv existe dans le dossier "data"
fichier_csv=$(find "$fichier_d_entrer" -maxdepth 1 -type f -name "*.csv")

# Vérifie si au moins un fichier .csv existe dans le dossier "data"
if [ -z "$fichier_csv" ];then
    echo "Erreur : Aucun fichier CSV n'a été trouvé dans le dossier $fichier_d_entrer."
    exit 1
fi

# Vérifie si le chemin commence par "data/" et se termine par ".csv"
if [[ "$fichier_d_entrer" =~ ^data/.*\.csv$ ]];then
    echo "Le chemin $fichier_d_entrer correspond à un au chemin vers le fichier CSV dans le dossier data."
else 
    echo "Erreur : Le chemin $fichier_d_entrer ne correspond pas à un fichier dit data CSV dans le dossier data."
    exit 1
fi

echo "Toutes les vérifications sont réussies. Au moins un fichier CSV a été trouvé dans le dossier $fichier_d_entrer"

#--------------------------------------------------------------------------------------------------------------#

# Vérifier si les fichiers source C sont présents.
if [ -e "progc/filtre_s.c" ] && [ -e "progc/trier_fichier_s" ] && [ -e "progc/etape1_filtre_t.c" ] && [ -e "progc/etape2_IsoCol2_3.c" ] && [ -e "progc/etape3_comptage.c" ] && [ -e "progc/etape4_triersomme.c" ] && [ -e "progc/etape5_traitement_final.c" ]; then
    echo "Les fichiers source C sont présents."

    # Vérifier si les exécutables pour tous les fichiers source sont présents.
    if [ -x "progc/filtre_s" ] && [ -x "progc/trier_fichier_s" ] && [ -x "progc/etape1_filtre_t" ] && [ -x "progc/etape2_IsoCol2_3" ] && [ -x "progc/etape3_comptage" ] && [ -x "progc/etape4_triersomme" ] && [ -x "progc/etape5_traitement_final" ]; then
        echo "Les exécutables sont présents sur le disque dur."
    else
        # Se déplacer dans le répertoire progc.
        cd progc

        # Compilation de tous les fichiers C.
        make all

        # Vérification du statut de la compilation.
        if [ $? -eq 0 ]; then
            echo "La compilation s'est bien déroulée. Les exécutables ont été créés."
        else
            echo "Erreur lors de la compilation."
        fi

        # Revenir au répertoire initial.
        cd ..
    fi
else
    echo "Certains fichiers source C ne sont pas trouvés. Lancement de la compilation."
fi

#--------------------------------------------------------------------------------------------------------------#

if [[ ! -d "$dossier_images" && ! -d "$dossier_temp" ]];then
    mkdir images
    mkdir temp
else
    rm -f temp/*
fi

#--------------------------------------------------------------------------------------------------------------#

# Gestion des options : parcours de la ligne de commande pour repérer les options.

for i in "$@" ;do                             # La condition qui permet de lancer l'option aide et donc de faire apparaître le fichier help.
    if [ "$i" == $fichier_d_entrer ] ;then
        option_oblig=$(("$option_oblig"+1))
    fi
    if [ "$i" == "-h" ];then
        echo -e "Le fichier help est apparue dans le dossier progc.\n"
        gedit "$fichier_d_aide"
        exit 1  
    fi
    if [ "$i" == "-d1" ];then
        # Enregistrer le temps de début.
        debut_timer_d1=$(date +%s)
        
        awk -F";" '/;1;/ {compteur[$6] += 1} END {for (nom in compteur) print nom ";" compteur[nom]}' "$fichier_d_entrer" |sort -t";" -k2nr | head -10 > demo/d1_final.csv
        
        fin_timer_d1=$(date +%s)

        # Calculer la durée totale (en secondes).
        duree_option_d1=$((fin_timer_d1 - debut_timer_d1))

        option_oblig=$(("$option_oblig"+1))

        # Afficher la durée.
        echo -e "\nLe traitement de l'option -d1 a pris $duree_option_d1 secondes.\n"

        # Partie graphique (Gnuplot).
        gnuplot << EOF

        # Paramètres de sortie
        set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
        set output 'images/histogramme_d1.png'

        # Paramètres du graphique
        set bmargin 13    # Ajuster la marge inférieure (en unités par défaut)
        set rmargin 10
        set lmargin 2
        set title 'HISTOGRAMME DE TRAITEMENT -d1'
        set xlabel 'CONDUCTEURS'
        set ylabel 'NOMBRE DE TRAJETS'
        set xtic rotate by 90 offset 0,-9
        set xlabel rotate by 180 offset 0,-9
        set ylabel offset 92,0
        set ytic offset 83,0
        set yrange [0:250]
        set ytic rotate by 90
        set style histogram rowstacked
        set style fill solid border -1
        set boxwidth 0.5
        unset key

        # Tracé du graphique
        set datafile separator ';'
        plot 'demo/d1_final.csv' using 2:xtic(1) with boxes lc rgb 'blue'

EOF
        convert -rotate 90 images/histogramme_d1.png images/histogramme_d1.png  # Commande pour pivoter l'image afin de la transformer en un histogramme horizontal.
        xdg-open images/histogramme_d1.png
    fi

    if [ "$i" == "-d2" ];then
        # Enregistrer le temps de début.
        debut_timer_d2=$(date +%s)
        awk -F";" '{compteur[$6] += $5} END {for (nom in compteur) print nom ";" compteur[nom]}' "$fichier_d_entrer" |sort -t";" -k2nr | head -10 > demo/d2_final.csv
        fin_timer_d2=$(date +%s)

        # Calculer la durée totale (en secondes).
        duree_option_d2=$((fin_timer_d2 - debut_timer_d2))

        option_oblig=$(("$option_oblig"+1))

        # Afficher la durée.
        echo -e "\nLe traitement de l'option -d2 a pris $duree_option_d2 secondes.\n"

        # Partie graphique (Gnuplot).
        gnuplot << EOF

        # Paramètres de sortie
        set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
        set output 'images/histogramme_d2.png'

        # Paramètres du graphique
        set bmargin 13
        set rmargin 10
        set lmargin 2
        set title 'HISTOGRAMME DE TRAITEMENT -d2'
        set xlabel 'CONDUCTEURS'
        set ylabel 'DISTANCE TOTALE (en km)'
        set xtic rotate by 90 offset 0,-9
        set xlabel rotate by 180 offset 0,-9
        set ylabel offset 92,0
        set ytic offset 83,0
        set yrange [0:200000]
        set ytic rotate by 90
        set style histogram rowstacked
        set style fill solid border -1
        set boxwidth 0.5
        unset key

        # Tracé du graphique
        set datafile separator ';'
        plot 'demo/d2_final.csv' using 2:xtic(1) with boxes lc rgb 'blue'

EOF
        convert -rotate 90 images/histogramme_d2.png images/histogramme_d2.png  # Commande pour pivoter l'image afin de la transformer en un histogramme horizontal.
        xdg-open images/histogramme_d2.png
    fi

    if [ "$i" == "-l" ];then
        # Enregistrer le temps de début.
        debut_timer_l=$(date +%s)
        awk -F";"  '{compteur[$1] += $5} END {for (id_trajet in compteur) print id_trajet ";" compteur[id_trajet]}' "$fichier_d_entrer" |sort -t";" -k2nr | head -10 | sort -t";" -k1n > demo/l_final.csv
        fin_timer_l=$(date +%s)

        # Calculer la durée totale (en secondes).
        duree_option_l=$((fin_timer_l - debut_timer_l))

        option_oblig=$(("$option_oblig"+1))
        # Afficher la durée.
        echo -e "\nLe traitement de l'option -l a pris $duree_option_l secondes.\n"

        # Partie graphique (Gnuplot).
        gnuplot << EOF
        # Paramètres de sortie
        set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
        set output 'images/histogramme_l.png'

        # Paramètres du graphique
        set title 'HISTOGRAMME DE TRAITEMENT -l'
        set xlabel 'IDENTIFIANT DU TRAJET (route ID)'
        set ylabel 'DISTANCE (en km)'
        set yrange [0:3000]
        set style histogram rowstacked
        set style fill solid border -1
        set boxwidth 0.5
        unset key

        # Tracé du graphique
        set datafile separator ';'
        plot 'demo/l_final.csv' using 2:xtic(1) with boxes lc rgb 'blue'
EOF
        xdg-open images/histogramme_l.png

    fi


    if [ "$i" == $option_t ];then
        # Enregistrer le temps de début.
        debut_timer_t=$(date +%s)
        ./progc/etape1_filtre_t "$fichier_d_entrer"
        ./progc/etape2_IsoCol2_3 "$fichier_d_entrer"
        ./progc/etape3_comptage
        ./progc/etape4_triersomme
        ./progc/etape5_traitement_final
        ./progc/etape6_parcours_decroissant_alphabetique
        fin_timer_t=$(date +%s)

        # Calculer la durée totale (en secondes).
        duree_option_t=$((fin_timer_t - debut_timer_t))

        option_oblig=$(("$option_oblig"+1))

        # Afficher la durée.
        echo -e "\nLe traitement de l'option -t a pris $duree_option_t secondes.\n" 
        
        # Partie graphique (Gnuplot).
        gnuplot << EOF
        # Paramètres de sortie
        set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
        set output 'images/histogramme_t.png'

        # Paramètres du graphique
        set title 'HISTOGRAMME DE TRAITEMENT -t'
        set xlabel 'NOM DES VILLES'
        set ylabel 'NOMBRE DE TRAJETS'
        set yrange [0:6000]
        set style data histogram
        set style histogram cluster gap 1
        set style fill solid border -1
        set boxwidth 1.50
        set xtic rotate by -45

        # Tracé du graphique
        set datafile separator ';'
        plot 'demo/fichier_final.csv' using 2:xtic(1) with histogram title "Nombre total de trajets" lc rgb 'blue', \
        'demo/fichier_final.csv' using 3 with histogram title "Ville de départ d'un trajet" lc rgb 'red'
EOF
        xdg-open images/histogramme_t.png
        
    fi

    if [ "$i" == "-s" ];then
        # Enregistrer le temps de début.
        debut_timer_s=$(date +%s)
        awk -F";" ' FNR > 1 {print $1 ";" $5}' "$fichier_d_entrer" > temp/s_intermediaire_calcul.csv
        ./progc/filtre_s
        ./progc/trier_fichier_s
        fin_timer_s=$(date +%s)
        # Calculer la durée totale (en secondes).
        duree_option_s=$((fin_timer_s - debut_timer_s))

        option_oblig=$(("$option_oblig"+1))

        # Afficher la durée.
        echo -e "\nLe traitement de l'option -s a pris $duree_option_s secondes.\n"

        # Partie graphique (Gnuplot).
        gnuplot << EOF
        # Paramètres de sortie
        set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
        set output 'images/histogramme_s.png'

        # Paramètres du graphique
        set title 'HISTOGRAMME DE TRAITEMENT -s
        set xlabel 'IDENTIFIANT DU TRAJET (route ID)'
        set ylabel 'DISTANCE (en km)'
        set yrange [0:1000]
        set xtics rotate by 45 right

        # Tracé du graphique
        set datafile separator ';'
        plot 'demo/fichier_traite_opt_s.csv' using 0:3:5:xticlabel(2) with filledcurves lc rgb 'blue' lt 1 title "Distance Max/Min (en km)", \
        'demo/fichier_traite_opt_s.csv' using 0:4 with lines linecolor 2 title "Distance moyenne (en km)"
EOF
        xdg-open images/histogramme_s.png
    fi


    if [ "$i" == "-supps_fichiers_demo" ];then
        rm -f demo/*.csv
        option_oblig=$(("$option_oblig"+1))
    fi

    if [ "$i" == "-supps_fichiers_temp" ];then
        rm -f temp/*.csv
        option_oblig=$(("$option_oblig"+1))
    fi

    if [ "$i" == "-fichier_reference" ];then
        sort -t";" -n -k1 data/data.csv > demo/ref.csv
        awk -F";" '{print $1 ";" $3 ";" $4}' demo/ref.csv > demo/reference_offi.csv
        option_oblig=$(("$option_oblig"+1))
    fi
    
done

#--------------------------------------------------------------------------------------------------------------#

if (( "$option_oblig" < 2 )); then
   echo "Pas assez d'arguments dans la ligne de commande."
    exit 1
fi

echo "Analyse des options terminée."

exit 0
