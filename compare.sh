#!/bin/bash

# Liste des commandes à tester
commandes=("ls" "ls -l" "ls -a" "ls -lh" "ls -R" "ls -t" "ls -S" "ls -r" "ls -i" "ls dossier"\
"echo Hello, world!" "echo 'Bonjour à tous!'" "echo -n 'Hello, ' && echo 'world!'" \
"echo -e 'Line 1\nLine 2\nLine 3'" "echo $USER" "echo $HOME" "echo $PATH" "echo $(date)"\
 "echo $((10 + 5))" "echo $((2 * 3))""cd dossier1" "cd dossier2" "cd .." "cd ~" "cd /"\
  "cd chemin/inexistant" "cd -" "cd" "cd $HOME" "cd /chemin/absolu""grep mot fichier.txt" \
  "grep -i mot fichier.txt" "grep -v mot fichier.txt" "grep -r mot dossier" \
  "grep -l mot fichier1.txt fichier2.txt" "grep -n mot fichier.txt"\
   "grep -E 'pattern1|pattern2' fichier.txt" "grep -o pattern fichier.txt" \
   "grep -c mot fichier.txt" "grep -i -r pattern dossier" "ls -l | grep 'fichier'"\
    "cat fichier.txt | head -n 5" "ps aux | grep 'chrome'"\
     "echo 'Hello, world!' | wc -w" "ls | sort" "cat fichier.txt | grep -v 'mot'")


# Variable pour indiquer si les résultats sont différents
resultats_differents=0

# Fonction pour afficher une section colorée
afficher_section() {
  echo "-------------------------------------"
  echo -e "\033[1;36m$1\033[0m"
  echo "-------------------------------------"
  echo
}

# Exécution des commandes dans le minishell
for commande in "${commandes[@]}"; do
  # Exécution de la commande dans le répertoire courant
  output1=$(eval $commande)

  afficher_section "Commande : $commande"

  # Lancement de l'exécutable de minishell
  ./minishell <<EOF
$commande
exit
EOF

  # Récupération du résultat de la deuxième commande
  output2=$(eval $commande)

  # Comparaison des résultats
  if [ "$output1" != "$output2" ]; then
    echo -e "\033[1;31mLes sorties sont différentes pour la commande : $commande\033[0m"
    resultats_differents=1
  fi
done

# Vérification finale si les résultats sont identiques pour toutes les commandes
if [ $resultats_differents -eq 0 ]; then
  echo -e "\033[1;32mLes sorties sont identiques pour toutes les commandes.\033[0m"
fi
