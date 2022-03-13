
#include "DeltaGeneraliser.h"





double calcul_activation_neurone_couche1(Weight_source* link, double theta) {
	
	//possible problème : si link ne foncitonne pas pour la couche 1, il va falloir aller chercher la valeur direct das donnees_entre

	double v = theta;

	for (int i = 0; i < sizeof(link); i++) {
		v = v + link[i].source->d * link[i].weight;
	}

	return v;
}

double calcul_activation_neurone_autre_couche(Neuron* current_neuron) {
	

	double v = 0.0;
	Neuron* neuron_main_source;

	for (int i = 0; i < current_neuron->get_main_count(); i++) {
	
		neuron_main_source = current_neuron->get_main_source(i);

		v += neuron_main_source->a * current_neuron->get_main_weight(i);
	}
	
	return v;
}

double calcul_fonction_sigmoide(double input) {
	return (1 / (1 + exp(-input)));
}

double calcul_fonction_sigmoide_deriver(double input) {
	return ( calcul_fonction_sigmoide(input) * (1 - calcul_fonction_sigmoide(input)) );
}

double calcul_sortie_activation(double v_activation, int option) {
	if (!option) {
		return calcul_fonction_sigmoide(v_activation);
	}
	else {
		return sin(v_activation);
	}
}

double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation, int option) {

	if (!option) {
		return ((sortie_desirer - v_sortie_activation) * (v_sortie_activation)*(1 - v_sortie_activation));
	}
	else {
		return ((sortie_desirer - v_sortie_activation) * cos(v_activation));
	}
}


//Erreur la dedans (comment récupérer le poids relié à la sortie du neurone et cette sortie)
double calcul_signal_erreur_autre_couche(Neuron* current_neuron, int option) {
	
	
	double v = 0.0;

	Neuron* neuron_link_source;

	for (int i = 0; i < current_neuron->get_link_count(); i++) {

		neuron_link_source = current_neuron->get_link_source(i);

		v += current_neuron->get_link_weight(i) * neuron_link_source->delta;
	}

	if (!option) {
		return v *= (current_neuron->i)*(1 - current_neuron->i);
	}
	else {
		return v *= cos(current_neuron->i);
	}
}

double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel) {
	
	double v = taux * entree_ou_a * v_signal_erreur;
	
	v = poids_actuel + v;

	return v;
}


void calcul_delta_generaliser(Network* Net, int option_fonction) {
	Layer* current_layer = Net->premier_layer;
	Neuron* current_neuron;
	double new_weight;
	
	//********************************Phase 1**********************************************
	//Loop until dernier_layer

	int L = 0;

	do {

		current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {
			//calcul activation et sortie de l'activation en fonction de la couche
			if (current_layer == Net->premier_layer) {

				for (int ligne_count = 0; ligne_count < Net->get_nombre_vecteur(); ligne_count++) {
					for (int colum_count = 0; colum_count < 12; colum_count++) {
						for (int link_count = 0; link_count < current_layer->get_neuron_count(); link_count++) {
							if (Net->donnees_entre[ligne_count][colum_count].link_source[link_count].source == current_neuron) {
								current_neuron->i += Net->donnees_entre[ligne_count][colum_count].x * Net->donnees_entre[ligne_count][colum_count].link_source[link_count].weight;
								//std::cout << current_neuron->i << std::endl;
							}
						}
					}
				}

				current_neuron->i += current_neuron->seuil;
				current_neuron->a = calcul_sortie_activation(current_neuron->i, option_fonction);
			}
			else {
				current_neuron->i += calcul_activation_neurone_autre_couche(current_neuron);
				current_neuron->i += current_neuron->seuil;
				
				current_neuron->a = calcul_sortie_activation(current_neuron->i, option_fonction);
			}

			
			
			//std::cout << L++ << "NEXT" << std::endl;
			//définit le prochain neuron à étudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//définit le prochain layer à étudier
		current_layer = current_layer->prochain_layer;

	} while (current_layer != NULL);
	/********************************************************************************************************************************************************/

	//**************************************** PHASE 2 *************************************************************************************
	//Loop from dernier_layer to premier_layer (obliger a cause du signal d'erreur qui se calcule du dernier_layer au premier_layer)
	current_layer = Net->dernier_layer;
	do {

		current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {

			//calcul signal d'erreur en fonction de la couche
			if (current_layer == Net->dernier_layer) {
				current_neuron->delta = calcul_signal_erreur_derniere_couche(current_neuron->d, current_neuron->a, current_neuron->i, option_fonction);
			}
			else {
				current_neuron->delta = calcul_signal_erreur_autre_couche(current_neuron, option_fonction);
			}

			//calcul de la correction de chaque poids et mise a jour de leur valeur avec la correction
			//*************************** Phase 3 et 4 **********************************************************************
			if (current_layer == Net->premier_layer) {
				for (int i = 0; i < current_neuron->get_main_count(); i++) {
					new_weight = calcul_correction_poids(Net->rate, current_neuron->get_main_data(i), current_neuron->delta, current_neuron->get_main_weight(i));
					current_neuron->set_main_weight(i, new_weight);
				}
			}
			else {
				for (int i = 0; i < current_neuron->get_main_count(); i++) {
					new_weight = calcul_correction_poids(Net->rate, current_neuron->a, current_neuron->delta, current_neuron->get_main_weight(i));
					current_neuron->set_main_weight(i, new_weight);
				}
			}
			//****************************************************************************************************************

			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//définit le prochain layer à étudier
		current_layer = current_layer->precedent_layer;

	} while (current_layer != NULL);

}




