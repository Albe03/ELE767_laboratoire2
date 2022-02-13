
#include "Neuron.h"


Neuron::Neuron(int _etage,int _i, int _link_count) {
	etage = _etage;
	i = _i;
	seuil = NULL;
	link_count = _link_count;

	main_source = new Weight(link_count);

	link_source = NULL;
	
	
	link_source = (Weight_source*)malloc(sizeof(Weight_source)*link_count);

	if (!link_source) {
		perror("No more memory for the link_source array");
		exit(0);
	}
	
	for (int i = 0; i < link_count; i++) {
		link_source[i].source = NULL;
		link_source[i].weight = NULL;
	}

}

Neuron::~Neuron() {
	i = NULL;
	etage = NULL;
	delete main_source;
	delete link_source;
}

int Neuron::get_i() {
	return i;
}

void Neuron::set_link_source(int _j, Neuron* _source) {
	link_source[_j].source = _source;
}

void Neuron::set_link_weight(int _j, double _weight) {
	link_source[_j].weight = _weight;
}

void Neuron::set_main_source(int _j, Neuron* _source) {
	main_source->set_source(_j, _source);
}

void Neuron::set_main_weight(int _j, double* _weight) {
	main_source->set_weight(_j, _weight);
}

Neuron* Neuron::get_main_source(int _j) {
	return main_source->get_source(_j);
}

double Neuron::get_main_weight(int _j) {
	return main_source->get_weight(_j);
}