
#include "Network.h"


Network::Network(int _input_count, int _layer_count, double _desire_reponse) {

	input_count = _input_count;
	layer_count = _layer_count;
	desire_reponse = _desire_reponse;

	input_array = (int*)malloc(sizeof(int)*input_count);

	if (!input_array) {
		perror("No more memory for the input array");
		exit(0);
	}

	//creation layer avec insertion


	for (int i = 0; i < input_count; i++) {
		input_array[i] = NULL;
	}
}


Network::~Network() {
	
	input_count = NULL;
	layer_count = NULL;
	desire_reponse = NULL;

	//delete premier layer

	free(input_array);
}

