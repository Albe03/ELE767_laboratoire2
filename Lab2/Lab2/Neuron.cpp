
#include "Neuron.h"


Neuron::Neuron(int _poids, int _i, int _j) {
	poids = _poids;
	i = _i;
	j = _j;
}

Neuron::~Neuron() {
	poids = NULL;
	i = NULL;
	j = NULL;
}

int Neuron::get_i() {
	return i;
}

int Neuron::get_j() {
	return j;
}


//Todo: set and get le poid