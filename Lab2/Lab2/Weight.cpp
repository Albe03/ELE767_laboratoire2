//#include "neuron.h"
#include "Weight.h"

Weight::Weight(int _link_count) {

	link_count = _link_count;
	
	data_table = (Main_weight_source*)malloc(sizeof(Main_weight_source)*link_count);

	if (!data_table) {
		perror("No more memory for the data_table array");
		exit(0);
	}
	

	for (int i = 0; i < link_count; i++) {
		data_table[i].data = NULL;
		data_table[i].source = NULL;
		data_table[i].weight_ptr = NULL;
	}
}


Weight::~Weight() {
	free(data_table);
}

void Weight::set_weight_ptr(int _j, double* _weight) {
	data_table[_j].weight_ptr = _weight;
}

void Weight::set_weight(int _j, double _weight) {
	*(data_table[_j].weight_ptr) = _weight;
}

void Weight::set_source(int _j, Neuron* _source) {
	data_table[_j].source = _source;
}

void Weight::set_data(int _j, double _data) {
	data_table[_j].data = _data;
}

double Weight::get_data(int _j) {
	return data_table[_j].data;
}

double Weight::get_weight(int _j) {
	double* weight = data_table[_j].weight_ptr;

	return *weight;
}

Neuron* Weight::get_source(int _j) {
	return data_table[_j].source;
}


