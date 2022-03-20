# ELE767_laboratoire2

## Execution du programme

- Il faut executer Lab2.exe

Vous aller voir une fenetre apparaitre, vous avez le choix d'utiliser des nouvelles donnees d'apprentissage
ou utiliser des anciennes donnees d'apprentissage.

- Clicker sur configuration

Une autre fenetre apparaitra, ou vous pouvez rentrer la configuration de votre apprentissage.

Precision
------------------------------------------------
Temps limite en seconde, c'est le temp maximal pour votre apprentissage.

Performance voulue en %, c'est la performance voulue pour la validation croisser, l'apprentissage
s'arretera une fois cette performance atteinte.

Emplacement, Vous devez inscrire le chemin complet ou se trouve vos fichiers

Pour l'emplacement du fichier de sortie, il sera dans le project nommée donnees_sorties.txt

- Une fois la configuration choissie, clicker sur Ok

Un écran noir va afficher les résultats, ça pourrait prendre quelques secondes. 
Afficher a l'ecran sera la performance d'apprentissage, VC et test pour chaque epoque. 

## Donnee ayant permis d'obtenir la meilleur performance

On reussi avoir une performance de 77% sur les test

Config.txt : Contient les configuration de cette apprentissage

Voici la configuration pour ce test

Nombre d'unite dans couche d'entrees: 480
Nombre de couches cachees: 2
Neuronnes dans la couche sortie: 10

Sigmoide
40 sets

taux d'apprentissage: 0.01
Performance voulue en %: 85

Neuron dans couches cachee 1: 50
Neuron dans couches cachee 2: 30
 
Base_de_donnees.txt : Contient tout les poids utiliser dans l'apprentissage

Pour le rouller, il suffit de cocher utiliser des anciennes donnees d'apprentissage dans le GUI. 





