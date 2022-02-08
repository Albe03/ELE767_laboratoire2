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
	Neuron(int _etage, int _i);
	~Neuron();

	int get_i();

	Neuron* prochain_neuron;
	Neuron* precedent_neuron;

	Weight_source* link_source;
	Weight* main_source;
	
private:
	int i;
	int etage;
};

#endif