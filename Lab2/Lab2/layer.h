#pragma once

#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include "neuron.h"

class Layer {

public:
	Layer(int _etage, int _neuron_count);
	~Layer();

	int get_etage();
	void add_neuron(int _i, int _j);
	void delete_neuron();

	Layer* prochain_layer;
	Layer* precedent_layer;

	Neuron* premier_neuron;
	Neuron* dernier_neuron;

private:
	int neuron_count;
	int etage;
};


#endif