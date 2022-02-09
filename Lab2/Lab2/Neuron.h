#pragma once

#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
//#include <iostream>

#include "weight.h"


class Weight;
class Weight_source;

class Neuron{

public:
	Neuron(int _etage, int _i, int _link_count);
	~Neuron();

	int get_i();

	void set_link_source(int _j, Neuron* _source);
	void set_link_weight(int _j, double _weight);

	void set_main_source(int _j, Neuron* _source);
	void set_main_weight(int _j, double* _weight);

	Neuron* prochain_neuron;
	Neuron* precedent_neuron;
	
	Weight_source* link_source;

private:
	Weight* main_source;
	int i;
	int etage;
	int link_count;
};

#endif