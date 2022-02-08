//#include "neuron.h"
#include "Weight.h"

Weight::Weight(int _link_count) {

	link_count = _link_count;
	
	data_table = (Weight_source*)malloc(sizeof(Weight_source)*link_count);

	if (!data_table) {
		perror("No more memory for the data_table array");
		exit(0);
	}
	
	for (int i = 0; i < link_count; i++) {
		//Todo: savoir comment gerer source et weight (random)
		data_table[i].source = NULL;
		data_table[i].weight = NULL;
	}
}


Weight::~Weight() {
	free(data_table);
}