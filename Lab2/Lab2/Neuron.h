#pragma once
#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Neuron{

public:
	Neuron(int _poids, int _i, int _j);
	~Neuron();

	int get_i();
	int get_j();

	Neuron* prochain_neuron;
	Neuron* precedent_neuron;

private:
	int poids;
	int i;
	int j;
};

#endif