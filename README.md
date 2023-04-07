<p align="center">
  <img src="https://github.com/byaliego/42-project-badges/blob/main/badges/minishell-bonus_alt.png?raw=true">
</p>


# Nom du projet : minishell

Minishell est un projet de l'école 42 qui consiste à créer une interface de commande shell, programmée en C. Le but du projet est de permettre aux utilisateurs d'interagir avec leur système d'exploitation à travers des commandes.

## Installation

Pour installer le projet, vous pouvez utiliser la commande `make`. Cela compilera le programme et générera un exécutable appelé `minishell`.

## Utilisation

Pour lancer le programme, exécutez la commande `./minishell` dans votre terminal. Vous verrez alors un prompt qui vous invitera à entrer des commandes.

## Fonctionnalités implémentées

Minishell implémente les fonctionnalités suivantes :

- Affichage d'un prompt dans l'attente d'une nouvelle commande
- Historique de commande fonctionnel
- Utilisations des fonctions avec un chemin relatif, absolu ou en se basant sur la variable d'environnement PATH
- Gestion des simples et doubles guillemets
- Gestion des variables d'environnement (`$` suivi d'une séquence de caractères)
- Gestion des redirections :
    - `<` redirige l'entrée standard
    - `>` redirige la sortie standard
    - `>>` redirige la sortie en mode append
    - `<<` utilisation d'un heredoc
- Gestion des pipes
- Gestion des status de sortie avec `$?`
- Gestion des signaux avec `ctrl-C`, `ctrl-D` et `ctrl-\`

## Exemples d'utilisation

```
ls -la | grep minishell
echo "Hello World"
export MY_VAR=hello
echo $MY_VAR
ls -la > output.txt
cat << eof
```


## Collaboration

Ce projet a été réalisé en collaboration avec [OSS-42](https://github.com/OSS-42). Nous avons travaillé ensemble pour implémenter les différentes fonctionnalités.

Nous espérons que vous apprécierez ce projet autant que nous avons aimé le réaliser.

## Auteur

[Mbertin44](https://github.com/Mbertin44)

## Remerciement
Merci à [byaliego](https://github.com/byaliego) pour le badge de projet.
