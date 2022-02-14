#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Affichage.h"
#include "Network.h"
#include <time.h> 
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

	int j_link = 0;
	int j_main = 0;
	double* weight_ptr;

	int nombre_couche = 4;
	//int nombre_neuron = 2;

	int* nombre_neuron = (int*)malloc(sizeof(int)*nombre_couche+2);

	nombre_neuron[0] = NULL;
	nombre_neuron[1] = 3;
	nombre_neuron[2] = 3;
	nombre_neuron[3] = 3;
	nombre_neuron[4] = 3;
	nombre_neuron[5] = NULL;

	int nombre_entrer = 3;
	int valeur_desirer = 2;

	int min_poid = 1;
	int max_poid = 100;

	double valeur_poid;

	srand(time(NULL));

	Neuron* neuron_prochaine_couche;
	Layer* current_layer;
	Neuron* current_neuron;

	Network Net(nombre_entrer,valeur_desirer);


	//Creation des layers et neurons
	Net.add_layer(1, nombre_neuron[1]);
	current_layer = Net.premier_layer;

	for (int i = 1; i <= nombre_couche; i++) {
		for (int j = 0; j < current_layer->get_neuron_count(); j++)
		{
			current_layer->add_neuron(current_layer->get_etage(), j, nombre_neuron[i+1], nombre_neuron[i-1]);
		}
		if (i != nombre_couche) {
			Net.add_layer(i + 1, nombre_neuron[i + 1]);
			current_layer = current_layer->prochain_layer;
		}
	}

	//Creation des liens entre link et main
	current_layer = Net.premier_layer;
	current_neuron = current_layer->premier_neuron;

	while (current_layer != Net.dernier_layer) {

		neuron_prochaine_couche = current_layer->prochain_layer->premier_neuron;

		while (current_neuron != NULL) {
			while (neuron_prochaine_couche != NULL) {

				valeur_poid = rand() % max_poid + min_poid;
			
				current_neuron->set_link_weight(j_link, valeur_poid);
				current_neuron->set_link_source(j_link, neuron_prochaine_couche);

				weight_ptr = &(current_neuron->link_source[j_link].weight);

				neuron_prochaine_couche->set_main_weight(j_main, weight_ptr);
				neuron_prochaine_couche->set_main_source(j_main, current_neuron);

				neuron_prochaine_couche = neuron_prochaine_couche->prochain_neuron;
				j_link++;
			}
			current_neuron = current_neuron->prochain_neuron;
			neuron_prochaine_couche = current_layer->prochain_layer->premier_neuron;
			j_link = 0;
			j_main++;
		}
		j_main = 0;
		current_layer = current_layer->prochain_layer;
		current_neuron = current_layer->premier_neuron;
	}
	//Net.display();

/* Pas sure si les destructeur dans chaque class font la meme chose
	for (int i = 0; i < nombre_couche; i++) {
		Net.delete_layer();
	}
*/
	Net.display();
	//Net.display();
	scanf_s("%d", &x);
	free(nombre_neuron);
	return 0;
}