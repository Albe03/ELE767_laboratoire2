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

	Network Net(3,10);

	Net.add_layer(1, 3);
	Net.add_layer(2, 3);
	Net.add_layer(3, 3);


	Neuron* prochain_neuron = Net.premier_layer->prochain_layer->premier_neuron;
	//Todo: gerer les link et main
	Net.premier_layer->premier_neuron->set_link_weight(0, 3);
	Net.premier_layer->premier_neuron->set_link_source(0, prochain_neuron);

	double* weight = &(Net.premier_layer->premier_neuron->link_source->weight);

	Net.premier_layer->prochain_layer->premier_neuron->set_main_weight(0,weight);
	Net.premier_layer->prochain_layer->premier_neuron->set_main_source(0, Net.premier_layer->premier_neuron);

	Net.display();

	Net.premier_layer->premier_neuron->set_link_weight(0, 2);
	//Net.delete_layer();
	//Net.delete_layer();
	//Net.delete_layer();


//	Net.display();
	scanf_s("%d", &x);
	return 0;
}