# Projet.Cy_Truck - Yacine KHELIL, Duc Duy HUYNH, Clément RIMBEUF
Projet CY-Truck fin de semestre 1 Pré-ing 2 MI 4

Ce projet a été développé en utilisant la programmation shell sous Debian. Il comprend un script shell qui peut être utilisé pour effectuer diverses tâches.

Prérequis : 

   Pour utiliser ce projet, vous devez avoir accès à un système Debian avec un shell disponible et une base de données de transport routier en csv.

Installation :

   Pour installer ce projet, vous pouvez télécharger le code source à partir du dépôt GitHub. Une fois téléchargé, vous pouvez exécuter les scripts shell en utilisant la commande ./donnee_filtree.bash 

Pour lancer la commande avec help, veuillez taper la ligne de commande suivante :

      ./donnee_filtree.bash data/data.csv -h

Concenant le Makefile, si vous voulez supprimer tous les fichiers exécutables et .o il faut alors taper la ligne de commande suivante. Dans tous les cas, les fichiers executable et .o sont supprimés de façon automatique ; ici c'est de façon manuelle que vous supprimez : 
      
      make -f progc/Makefile clean

Autres commandes de disponible (en bonus) :
Par exemple, vous pouvez supprimer tous les fichiers .csv du dossier demo à l'aide de cette commande :

      ./donnee_filtree.bash data/data.csv -supps_fichiers_demo

Par ailleurs, vous avez une commande pour pouvoir supprimer les fichiers temporaires .csv se situant dans le dossier temp, même si ces dernières sont supprimées automatiquement à la fin du fichier bash :

      ./donnee_filtree.bash data/data.csv -supps_fichiers_temp

Enfin, on a fait une dernière commande qui permet d'avoir le fichier de référence de toutes les distances en fonction des routes id et qui trient de façon croissant les routes id :

      ./donnee_filtree.bash data/dta.csv -fichier_reference

Utilisation :

  Il suffit de donner au script un fichier .csv et les options demandées et il sortira un graphique correspondant aux options.

Yacine KHELIL, Duc Duy HUYNH et Clément RIMBEUF
