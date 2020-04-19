# Projet IA - HaliteIII

Pour récuperer le bot : `git clone https://github.com/Ssoull/HaliteIII.git` 

Aussi disponible ici : https://github.com/Ssoull/HaliteIII 

## Fonctionnalités du bot

### Les vaisseaux

Les vaisseaux sont capables de faire plusieurs actions :
- Se déplacer en prenant en compte leur environnement pour choisir le meilleur chemin, c'est à dire celui qui leur coutera le moins d'halite
- Utiliser des états qui géreront leur comportement
- Utiliser un état de récolte et choisir la cellule la plus adaptée 
- Utiliser un état de collecte qui se chargera de choisir le meilleur point de collecte ou le cas échéant de choisir le lieu ou créer un point de collecte.
- Se transformer en point de collecte si les conditions requises sont réunies.

### Le shipyard

Le shipyard est l'entité responsable de la création des vaisseaux. Après quelques tests nous avons fixé la condition suivante pour décider s'il faut créer un vaisseau ou non : 
- Pas d'apparition de vaisseau après le tour 200 pour 2 joueurs et 300 pour 4 joueurs.
- Pas d'apparition de vaisseau si le montant total d'halite disponible sur la carte de jeu est inférieur à 33% du montant initial.
- Pas de tentative de création de vaisseau si un vaisseau est déjà présent sur le shipyard ou si le stock d'halite n'est pas assez important.

### Déplacement des vaisseaux

Pour gérer le déplacement des vaisseaux nous avons utilisé une impélentation de l'algorithme D* lite que nous avons modifié pour qu'il réponde à nos besoins. Notamment pour la prise en compte de la possibilité de se déplacer sur un côté de la map pour revenir sur le côté opposé, l'alogrithme permet donc de calculer le chemin optimal en prenant en compte cette particularité.  

Nous avons également ajouté le montant d'halite des cellules dans le calcul du poids pour faire passer les vaisseaux sur les cellules avec le plus faible montant d'halite et ainsi réduire les dépenses d'halite dues aux déplacements.

## Retour sur le projet

### Pablo

Ce projet fut très intéressant en termes de programmation et schéma de pensée.  
Cependant je pense que nous avons fait plusieurs erreurs.
La première est d'avoir voulu développer sur la version C++ de base qui était donnée.
Nous aurions dû faire le choix dès le départ de réécrire la version C++ qui nous était donnée.
Ce qui a pu nous ralentir était principalement l'architecture de base et nous n'avons pas eu le temps de tout réimplémenter.
Nous avons fait le choix de réécrire le projet de base avec plus de consistance de données (sauvegarde des ships et des dropoffs construits) plutôt que tout réécrire.
Notre deuxième erreur fut d'avoir utilisé un code Dstar déjà implémenté, nous avions voulu gagner du temps, mais au final, il s'agissait plutôt d'une boîte noire.
Le code pour le Dstar à malgré tout était grandement modifié pour qu'il puisse correspondre à nos attentes mais malgré tout certains comportements restaient incompréhensible.

Malgré tout cela il a été très intéressant de développer ce genre de projet et de voir son comportement avec d'autres bots.

### Louis

Le kit C++ de base nous a fait perdre beaucoup de temps, le code n'était pas très compréhensible, nous avons par la suite réécrit ce kit en apportant plus de cohérence. Une fois la base construite réfléchir aux fonctionnalités du bot et à la façon de les implémenter a été une très bonne expérience.  
Nous avons créé notre propre stratégie et système d'états et cela a été intéressant de voir notre bot évoluer face à ceux des autres équipes.  
Avec le recul je pense que nous n'aurions pas du nous baser sur la totalité du kit de départ pour ce projet, cela a été assez frustrant au début de comprendre son fonctionnement pour au final le réécrire complètement.  
La modification du pathfinding a été pour moi un élément intéressant, je suis assez satisfait du résultat malgré quelques défauts nous avons réussi à modifier le D* lite pour qu'il convienne à nos besoins.