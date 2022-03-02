
#include "layer.h"


Layer::Layer(int _etage,int _neuron_count) {
	etage = _etage;
	neuron_count = _neuron_count;
	prochain_layer = NULL;
	precedent_layer = NULL;
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

int Layer::get_neuron_count() {
	return neuron_count;
}

void Layer::add_neuron(int _etage,int _i, int _link_count, int _main_count)
{
	Neuron* tmp = new Neuron(_etage, _i, _link_count, _main_count);

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