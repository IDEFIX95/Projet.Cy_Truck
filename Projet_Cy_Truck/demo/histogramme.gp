# Paramètres de sortie
set terminal pngcairo enhanced font 'Arial,10'
set output 'histogramme.png'

# Paramètres du graphique
set bmargin 12    # Ajuster la marge inférieure (en unités par défaut)
set title 'Histogramme'
set xlabel 'Nombre de trajets'
set ylabel 'Conducteurs'
set xtic rotate by 90 offset 0,-9
set xlabel rotate by 180 offset 0,-8
set ylabel offset 87,0
unset ytics
set yrange [0:250]
set y2tics mirror  # Utiliser l'autre côté de l'axe des y
set y2range [0:250]
set ytic rotate by 90
set style histogram rowstacked
set style fill solid border -1
set boxwidth 0.5

# Tracé du graphique
set datafile separator ';'
plot 'demo/test_final.csv' using 2:xtic(1) with boxes lc rgb 'blue'
