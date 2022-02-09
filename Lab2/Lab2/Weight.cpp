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
		//Todo: savoir comment gerer source et weight (random)
		data_table[i].source = NULL;
		data_table[i].weight_ptr = NULL;
	}
}


Weight::~Weight() {
	free(data_table);
}

void Weight::set_weight(int _j, double* _weight) {
	data_table[_j].weight_ptr = _weight;
}

void Weight::set_source(int _j, Neuron* _source) {
	data_table[_j].source = _source;
}