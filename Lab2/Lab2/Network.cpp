
#include "Network.h"


Network::Network(int _input_count, double _desire_reponse) {

	input_count = _input_count;
	desire_reponse = _desire_reponse;
	premier_layer = NULL;
	dernier_layer = NULL;

	input_array = (int*)malloc(sizeof(int)*input_count);

	if (!input_array) {
		perror("No more memory for the input array");
		exit(0);
	}

	for (int i = 0; i < input_count; i++) {
		input_array[i] = NULL;
	}
}


Network::~Network() {
	input_count = NULL;
	desire_reponse = NULL;

	free(input_array);
}


void Network::add_layer(int _etage, int _neuron_count)
{
	Layer* tmp = new Layer(_etage, _neuron_count);

	if (premier_layer == NULL)
	{
		premier_layer = tmp;
	}
	else
	{	
		tmp->precedent_layer = dernier_layer;
		dernier_layer->prochain_layer = tmp;
	}

	dernier_layer = tmp;
}

/*
void Network::delete_layer()
{
	Layer* tmp = dernier_layer;

	if (dernier_layer->precedent_layer != NULL) {
		dernier_layer->precedent_layer->prochain_layer = NULL;
		dernier_layer = dernier_layer->precedent_layer;
		delete tmp;
	}
	else {
		delete tmp;
		premier_layer = NULL;
		dernier_layer = NULL;
	}
}
*/

void Network::display() {


	int neuron_count;

	if (premier_layer == NULL) {
		cout << "Network is empty!" << endl;
	}
	else {
		Layer* temp = premier_layer;
		neuron_count = temp->get_neuron_count();
		while (temp != NULL) {
			cout << "Layer " << temp->get_etage() << "\t\t";
				
			Neuron* neuron = temp->premier_neuron;
	

			cout << "Neuron ";

			while (neuron != NULL) {
				for (int i = 0; i != neuron_count; i++) {
					cout << " " << neuron->get_i() << "," << i << "\t";
				}
				neuron = neuron->prochain_neuron;
			}
			cout << endl;

			cout << "Main(weight) " << "\t\t"; 

			neuron = temp->premier_neuron;
			while (neuron != NULL) {
				for (int i = 0; i < neuron_count; i++) {
					if (neuron->get_main_source(i) != NULL) {
						cout << neuron->get_main_weight(i) << "\t";
					}
				}
				neuron = neuron->prochain_neuron;
			}

			cout << endl;
			cout << "Link(weight) " << "\t\t";

			neuron = temp->premier_neuron;
			while (neuron != NULL) {
				for (int i = 0; i < neuron_count; i++) {
					if (neuron->link_source[i].source != NULL) {
						cout << neuron->link_source[i].weight << "\t";
					}
				}
				neuron = neuron->prochain_neuron;
			}
			cout << endl << endl;
			temp = temp->prochain_layer;
		}
	}
}