#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Affichage.h"
#include "Network.h"

int main()
{
	Affichage MonAffichage;
	MonAffichage.NbCache = 0;
	MonAffichage.NbEntree = 0;
	MonAffichage.NbSortie = 0;
	Afficher(MonAffichage);
}




