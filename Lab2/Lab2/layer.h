#pragma once

#ifndef LAYER_H
#define LAYER_H

#include <iostream>

class layer {

public:
	layer(int _stage, int _neuron_count);
	~layer();
	layer* prochain_layer;
	layer* precedent_layer;
	int stage;

private:
	int neuron_count;
};


#endif