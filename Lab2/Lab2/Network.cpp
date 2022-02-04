
#include "Network.h"


Network::Network(int _input_count, int _layer_count, double _desire_reponse) {

	input_count = _input_count;
	layer_count = _layer_count;
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
	layer_count = NULL;
	desire_reponse = NULL;

	//delete premier layer

	free(input_array);
}


void Network::add_layer(int _stage, int _neuron_count)
{
	layer* tmp = new layer(_stage, _neuron_count);

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

void Network::delete_layer()
{
	layer* tmp = dernier_layer;

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


void Network::display() {
	if (premier_layer == NULL) {
		cout << "List is empty!" << endl;
	}
	else {
		layer* temp = premier_layer;
		while (temp != NULL) {
			cout << temp->stage << " ";
			temp = temp->prochain_layer;
		}
		cout << endl;
	}
}