
#include "layer.h"


Layer::Layer(int _etage,int _neuron_count) {
	etage = _etage;
	neuron_count = _neuron_count;
	prochain_layer = NULL;
	precedent_layer = NULL;

	for (int i = 0; i < neuron_count; i++) {
	//Todo : add random value pour le poid
	//Todo : Reglade de la valeur j
		add_neuron(1, etage, i+1);
	}
}

Layer::~Layer() {

	for (int i = 0; i < neuron_count; i++) {
		delete_neuron();
	}

	etage = NULL;
	neuron_count = NULL;
	prochain_layer = NULL;
	precedent_layer = NULL;
}

int Layer::get_etage() {
	return etage;
}

void Layer::add_neuron(int _poids, int _i, int _j)
{
	Neuron* tmp = new Neuron(_poids, _i, _j);

	if (premier_neuron == NULL)
	{
		premier_neuron = tmp;
	}
	else
	{
		tmp->precedent_neuron = dernier_neuron;
		dernier_neuron->prochain_neuron = tmp;
	}

	dernier_neuron = tmp;
}

void Layer::delete_neuron()
{
	Neuron* tmp = dernier_neuron;

	if (dernier_neuron->precedent_neuron != NULL) {
		dernier_neuron->precedent_neuron->prochain_neuron = NULL;
		dernier_neuron = dernier_neuron->precedent_neuron;
		delete tmp;
	}
	else {
		delete tmp;
		premier_neuron = NULL;
		dernier_neuron = NULL;
	}
}