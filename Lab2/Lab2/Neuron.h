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


	double i;        //valeur activation
	double a;        //valeur sortie activation
	double delta;    //valeur sortie activation
	double seuil;    //b ou theta dans les equations
	double d;		 //sortie desirer

private:
	Weight* main_source;
	
	int etage;

	int link_count;  //nbr d'entree sur ce neurone
	int main_count;  //nbr de sortie sur ce neurone
};

#endif