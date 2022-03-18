#pragma once
#include <string.h>

class Affichage {
public:
	unsigned int NbEntree;
	unsigned int NbCache;
	unsigned int NbSortie;
	unsigned int FonctionActivation;
};

void Afficher(Affichage MonAffichage);