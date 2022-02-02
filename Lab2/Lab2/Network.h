#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include "layer.h"

class Network {


public:

	Network(int _input_count, int _layer_count, double _desire_reponse);
	~Network();

	layer* premier_layer;

private:

	int layer_count;
	double desire_reponse;
	int input_count;
	int* input_array;
};


#endif