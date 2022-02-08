#pragma once


#ifndef WEIGHT_H
#define WEIGHT_H

#include "neuron.h"

class Neuron;

class Weight_source{

public:
	double weight;
	Neuron* source;
};


class Weight {

public:
	Weight(int _link_count);
	~Weight();

private:
	int link_count;
	Weight_source* data_table;
};

#endif