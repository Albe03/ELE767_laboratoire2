
#include "Neuron.h"


Neuron::Neuron(int _etage,int _i) {
	etage = _etage;
	i = _i;
	//Todo: gerer et modifier le link_count
	main_source = new Weight(2);

	//Todo: gerer j_MAX
	link_source = NULL;
	
	/*
	link_source = (Weight_source*)malloc(sizeof(Weight_source)*j_MAX);

	if (!link_source) {
		perror("No more memory for the link_source array");
		exit(0);
	}
	*/
}

Neuron::~Neuron() {
	i = NULL;

	delete main_source;
	delete link_source;
}

int Neuron::get_i() {
	return i;
}

