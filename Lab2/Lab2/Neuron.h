#pragma once

#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "weight.h"


class Weight;
class Weight_source;

class Neuron{

public:
	Neuron(int _etage, int _i, int _link_count, int _main_count);
	~Neuron();

	int get_i();

	void set_link_source(int _j, Neuron* _source);
	void set_link_weight(int _j, double _weight);

	void set_main_source(int _j, Neuron* _source);
	void set_main_weight(int _j, double* _weight);

	Neuron* get_main_source(int _j);
	double get_main_weight(int _j);

	int get_link_count();
	int get_main_count();

	void set_output(int _output);

	Neuron* prochain_neuron;
	Neuron* precedent_neuron;

	Weight_source* link_source;
	
private:
	Weight* main_source;

	int i;
	int seuil;
	int etage;
	int d;
	int link_count;
	int main_count;
};

#endif