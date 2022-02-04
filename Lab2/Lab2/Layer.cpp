
#include "layer.h"


layer::layer(int _stage,int _neuron_count) {
	stage = _stage;
	neuron_count = _neuron_count;
	prochain_layer = NULL;
	precedent_layer = NULL;
}

layer::~layer() {
	stage = NULL;
	stage = NULL;
	neuron_count = NULL;
	prochain_layer = NULL;
	precedent_layer = NULL;
}