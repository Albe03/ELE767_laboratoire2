#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include "Affichage.h"
#include "Fichier.h"



void Afficher(Affichage MonAffichage)
{
	char temp;

	printf("====== Laboratoire 2 ELE767 ======\n");
	printf("Reconnaissance de la parole avec reseau de neuronnes\n\n");


	do {
		printf("Voulez-vous utiliser une nouvelle configuration? (Y/N) : ");
		scanf("%c", &temp);
		// Nouvelle config
		if (temp == 'Y' || temp == 'y')
		{
			// TODO : AJOUTER VALEURS DANS FICHIER CONFIG
			CreerFichierConfig();

			printf("Entrer le nombre d'unite dans la couche d'entree : ");
			scanf("%d", &MonAffichage.NbEntree);
			printf("Entrer le nombre de couches cachees : ");
			scanf("%d", &MonAffichage.NbCache);
			printf("Entrer le nombre d'unite dans la couche de sortie : ");
			scanf("%d", &MonAffichage.NbSortie);

			do {
				printf("Entrer la fonction d'activation voulue (1 pour Sigmoide et 2 pour X) : ");
				scanf("%d", &MonAffichage.FonctionActivation);
			} while (MonAffichage.FonctionActivation != 1 && MonAffichage.FonctionActivation != 2);
			FermerFichierConfig();
		}
		else if (temp == 'N' || temp == 'n')
		{
			LireFichierConfig();
			// TODO : PRENDRE VALEURS DANS FICHIER ET METTRE DANS MONAFFICHAGE


			FermerFichierConfig();
		}
	} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n');
	
	
}