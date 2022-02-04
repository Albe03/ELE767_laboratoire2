#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "layer.h"

using namespace std;

class Network {


public:

	Network(int _input_count, int _layer_count, double _desire_reponse);
	~Network();

	void add_layer(int _stage, int _neuron_count);
	void delete_layer();
	void display();

	Layer* premier_layer;
	Layer* dernier_layer;

private:

	int layer_count;
	double desire_reponse;
	int input_count;
	int* input_array;
};


#endif