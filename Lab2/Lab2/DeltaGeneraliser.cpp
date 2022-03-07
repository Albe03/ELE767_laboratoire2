
#include "DeltaGeneraliser.h"





double calcul_activation_neurone_couche1(Weight_source* link, double theta) {
	
	//possible problème : si link ne foncitonne pas pour la couche 1, il va falloir aller chercher la valeur direct das donnees_entre

	double v = theta;

	for (int i = 0; i < sizeof(link); i++) {
		v = v + link[i].source->d * link[i].weight;
	}

	return v;
}

double calcul_activation_neurone_autre_couche(Weight_source* link, double theta) {
	
	double v = theta;

	for (int i = 0; i < sizeof(link); i++) {
		v = v + link[i].source->d * link[i].weight;
	}

	return v;
}

double calcul_fonction_sigmoide(double input) {
	return (1 / (1 + exp(input)));
}

double calcul_fonction_sigmoide_deriver(double input) {
	return ( calcul_fonction_sigmoide(input) * (1 - calcul_fonction_sigmoide(input)) );
}

double calcul_sortie_activation(double v_activation) {
	return calcul_fonction_sigmoide(v_activation);
}

double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation) {
	return ( (sortie_desirer - v_sortie_activation) * calcul_fonction_sigmoide_deriver(v_activation));
}


//Erreur la dedans (comment récupérer le poids relié à la sortie du neurone et cette sortie)
double calcul_signal_erreur_autre_couche(double sortie_desirer, Layer* couche_superieur, Weight_source* link, double v_activation) {
	
	
	double v = calcul_fonction_sigmoide_deriver(v_activation);

	for (int i = 0; i < sizeof(link); i++) {
		/*par ici l'erreur*/v = v + link[i].weight * couche_superieur->premier_neuron->delta;
	}
	
	return v;
}

double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel) {
	
	double v = taux * entree_ou_a * v_signal_erreur;
	
	v = poids_actuel + v;

	return v;
}


void calcul_delta_generaliser(Network Net) {
	Layer* current_layer = Net.premier_layer;
	
	//Loop until dernier_layer
	do {

		Neuron* current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {
			//calcul activation et sortie de l'activation en fonction de la couche
			if (current_layer == Net.premier_layer) {
				current_neuron->i = calcul_activation_neurone_couche1(current_neuron->link_source, current_neuron->seuil);
				current_neuron->a = calcul_sortie_activation(current_neuron->i);
			}
			else {
				current_neuron->i = calcul_activation_neurone_couche1(current_neuron->link_source, current_neuron->seuil);
				current_neuron->a = calcul_sortie_activation(current_neuron->i);
			}

			
			

			//définit le prochain neuron à étudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != current_layer->dernier_neuron);


		//définit le prochain layer à étudier
		current_layer = current_layer->prochain_layer;

	} while (current_layer != Net.dernier_layer);


	
	//Loop from dernier_layer to premier_layer (obliger a cause du signal d'erreur qui se calcule du dernier_layer au premier_layer)
	current_layer = Net.dernier_layer;
	do {

		Neuron* current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {

			//calcul signal d'erreur en fonction de la couche
			if (current_layer == Net.dernier_layer) {
				current_neuron->delta = calcul_signal_erreur_derniere_couche(current_neuron->d, current_neuron->a, current_neuron->i);
			}
			else {
				current_neuron->delta = calcul_signal_erreur_autre_couche(current_neuron->d, current_layer->prochain_layer, current_neuron->link_source, current_neuron->i);
			}

			//calcul de la correction de chaque poids et mise a jour de leur valeur avec la correction
			for (int i = 0; i < sizeof(current_neuron->link_source); i++) {
				current_neuron->link_source[i].weight = calcul_correction_poids(Net.rate, current_neuron->a, current_neuron->delta, current_neuron->link_source[i].weight);
			}

		} while (current_neuron != current_layer->dernier_neuron);


		//définit le prochain layer à étudier
		current_layer = current_layer->precedent_layer;

	} while (current_layer != Net.premier_layer);
}




