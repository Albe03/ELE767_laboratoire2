
#include "Network.h"
#include "Source.h"

Network::Network(int _input_count, Input** _donnees, int _neuron_count, int _nombre_vecteur, int _nombre_sortie) {

	input_count = _input_count;
	donnees_entre = _donnees;
	nombre_vecteur = _nombre_vecteur;
	nombre_sortie = _nombre_sortie;

	for (int i = 0; i < (input_count / NBR_VECTORS_COMPONENT); i++) {
		for (int j = 0; j < NBR_VECTORS_COMPONENT; j++) {
			donnees_entre[i][j].link_source = (Weight_source*)malloc(sizeof(Weight_source)*_neuron_count);
		}
	}

	tableau_sortie = (int**)malloc(sizeof(int)*nombre_sortie);

	for (int i = 0; i < nombre_sortie; i++) {
		tableau_sortie[i] = (int*)malloc(sizeof(int)*nombre_sortie);
	}

	premier_layer = NULL;
	dernier_layer = NULL;
}


Network::~Network() {
	input_count = NULL;

	for (int i = 0; i < (input_count/ VALEUR_TEST); i++) {
		for (int j = 0; j < VALEUR_TEST; j++) {
			free(donnees_entre[i][j].link_source);
		}
		free(donnees_entre[i]);
	}

	for (int i = 0; i < nombre_sortie; i++) {
		tableau_sortie[i];
	}

	free(tableau_sortie);

	free(donnees_entre);
}


void Network::add_layer(int _etage, int _neuron_count)
{
	Layer* tmp = new Layer(_etage, _neuron_count);

	if (premier_layer == NULL)
	{
		premier_layer = tmp;
	}
	else
	{	
		tmp->precedent_layer = dernier_layer;
		dernier_layer->prochain_layer = tmp;
	}

	dernier_layer = tmp;
}

/*
void Network::delete_layer()
{
	Layer* tmp = dernier_layer;

	if (dernier_layer->precedent_layer != NULL) {
		dernier_layer->precedent_layer->prochain_layer = NULL;
		dernier_layer = dernier_layer->precedent_layer;
		delete tmp;
	}
	else {
		delete tmp;
		premier_layer = NULL;
		dernier_layer = NULL;
	}
}
*/

void Network::display() {


	int neuron_count;

	

	if (premier_layer == NULL) {
		std::cout << "Network is empty!" << std::endl;
	}
	else {
		Layer* temp = premier_layer;
		//neuron_count = temp->get_neuron_count();
		while (temp != NULL) {
			std::cout << "Layer " << temp->get_etage() << "\t\t";

			neuron_count = temp->get_neuron_count();
			Neuron* neuron = temp->premier_neuron;
	

			std::cout << "Neuron ";

			while (neuron != NULL) {
				for (int i = 0; i != neuron_count; i++) {
					std::cout << " " << neuron->get_i() << "," << i << "\t";
				}
				neuron = neuron->prochain_neuron;
			}
			std::cout << std::endl;

			std::cout << "Main(weight) " << "\t\t"; 

			neuron = temp->premier_neuron;
			while (neuron != NULL) {
				for (int i = 0; i < neuron->get_main_count(); i++) {
					if (neuron->get_main_source(i) != NULL) {
						std::cout << neuron->get_main_weight(i) << "\t";
					}
				}
				neuron = neuron->prochain_neuron;
			}

			std::cout << std::endl;
			std::cout << "Link(weight) " << "\t\t";

			neuron = temp->premier_neuron;
			while (neuron != NULL) {
				for (int i = 0; i < neuron->get_link_count(); i++) {
					if (neuron->link_source[i].source != NULL) {
						std::cout << neuron->link_source[i].weight << "\t";
					}
				}
				neuron = neuron->prochain_neuron;
			}
			std::cout << std::endl << std::endl;
			temp = temp->prochain_layer;
		}
	}
}


void Network::set_weight_input(int _i, int _j, int _i_neuron,double _weight) {
	donnees_entre[_i][_j].link_source[_i_neuron].weight = _weight;
}

void Network::set_source_input(int _i, int _j, int _i_neuron, Neuron* _source) {
	donnees_entre[_i][_j].link_source[_i_neuron].source = _source;
}

int Network::get_nombre_vecteur() {
	return nombre_vecteur;
}