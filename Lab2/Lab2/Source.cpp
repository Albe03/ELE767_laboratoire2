#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Affichage.h"
#include "Network.h"
/*
int main()
{
	Affichage MonAffichage;
	MonAffichage.NbCache = 0;
	MonAffichage.NbEntree = 0;
	MonAffichage.NbSortie = 0;
	Afficher(MonAffichage);
}
*/



int main(void) {

	int x;

	Network Net(3,4,10);

	Net.add_layer(1, 2);
	Net.add_layer(2, 2);
	Net.add_layer(3, 2);

	Net.display();

	Net.delete_layer();
	Net.delete_layer();
	Net.delete_layer();


	Net.display();
	scanf_s("%d", &x);
	return 0;
}