#include "Affichage.h"
#include <stdio.h>

void Afficher(Affichage MonAffichage)
{
	printf("====== Laboratoire 2 ELE767 ======\n");
	printf("Reconnaissance de la parole avec reseau de neuronnes\n\n");
	printf("Entrer le nombre de couches d'entree : ");
	scanf_s("%d", &MonAffichage.NbEntree);
	printf("\nEntrer le nombre de couches cachées : ");
	scanf_s("%d", &MonAffichage.NbCache);
	printf("Entrer le nombre de couches de sortie : ");
	scanf_s("%d", &MonAffichage.NbSortie);
}