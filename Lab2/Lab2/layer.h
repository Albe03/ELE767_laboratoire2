#pragma once

#ifndef LAYER_H
#define LAYER_H


class layer {

public:

	layer* prochain_layer;
	layer* precedent_layer;

	layer(int _neuron_count);

private:
	int neuron_count;
	int stage;

};


#endif