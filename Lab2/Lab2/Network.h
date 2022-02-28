#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "layer.h"
#include "Source.h"


//using namespace std;



class Network {


public:

	Network(int _input_count, double _desire_reponse, Input** _donnees, int _neuron_count);
	~Network();

	void add_layer(int _stage, int _neuron_count);
	//void delete_layer();
	void display();

	void set_weight_input(int _i, int _j, int _i_neuron, double _weight);
	void set_source_input(int _i, int _j, int _i_neuron, Neuron* _source);


	Input** donnees_entre;

	Layer* premier_layer;
	Layer* dernier_layer;

private:
	double desire_reponse;
	int input_count;
	int* input_array;
};





#endif