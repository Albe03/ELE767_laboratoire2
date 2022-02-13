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

class Main_weight_source {
public:
	double* weight_ptr;
	Neuron* source;
};


class Weight {
public:
	Weight(int _link_count);
	~Weight();
	void set_weight(int _j, double* _weight);
	void set_source(int _j, Neuron* _source);	

	double get_weight(int _j);
	Neuron* get_source(int _j);

private:
	int link_count;
	Main_weight_source* data_table;
};




#endif