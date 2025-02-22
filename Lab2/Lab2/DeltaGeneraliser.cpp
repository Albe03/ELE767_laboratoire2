
#include "DeltaGeneraliser.h"
#include "Source.h"




double calcul_activation_neurone_couche1(Weight_source* link, double theta) {
	
	//possible probl�me : si link ne foncitonne pas pour la couche 1, il va falloir aller chercher la valeur direct das donnees_entre

	double v = theta;

	for (int i = 0; i < sizeof(link); i++) {
		v = v + link[i].source->d * link[i].weight;
	}

	return v;
}

double calcul_activation_neurone_autre_couche(Neuron* current_neuron) {
	

	double v = 0.0;
	Neuron* neuron_main_source;
	int nombre_main = current_neuron->get_main_count();

	for (int i = 0; i < nombre_main; i++) {
	
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
		return ((2 / (1 + exp(-2*v_activation))) - 1);
	}
}

double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation, int option) {

	if (!option) {
		return ((sortie_desirer - v_sortie_activation) * (v_sortie_activation)*(1 - v_sortie_activation));
	}
	else {
		return ((sortie_desirer - v_sortie_activation) * (1 - v_sortie_activation*v_sortie_activation));
	}
}


//Erreur la dedans (comment r�cup�rer le poids reli� � la sortie du neurone et cette sortie)
double calcul_signal_erreur_autre_couche(Neuron* current_neuron, int option) {
	
	
	double v = 0.0;
	double test;

	Neuron* neuron_link_source;
	int nombre_linked = current_neuron->get_link_count();

	for (int i = 0; i < nombre_linked; i++) {

		neuron_link_source = current_neuron->get_link_source(i);

		v += current_neuron->get_link_weight(i) * neuron_link_source->delta;
	}

	if (!option) {
		return v *= (current_neuron->a)*(1 - current_neuron->a);
	}
	else {
		return v *= (1 - current_neuron->a*current_neuron->a);
	}
}

double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel) {
	
	double v = taux * entree_ou_a * v_signal_erreur;
	
	v = poids_actuel + v;

	return v;
}


void calcul_retropopagation(Network* Net, int option_fonction) {

	Layer* current_layer;
	Neuron* current_neuron;
	double new_weight;
	int nombre_neuron;
	int nombre_ligne;
	//********************************Phase 1**********************************************
	//Loop until dernier_layer
	
	current_layer = Net->premier_layer;
	nombre_ligne = Net->get_nombre_vecteur();
	do {

		current_neuron = current_layer->premier_neuron;
		nombre_neuron = current_layer->get_neuron_count();
		
		//Loop until dernier_neuron
		do {
			//calcul activation et sortie de l'activation en fonction de la couche
			if (current_layer == Net->premier_layer) {			
				for (int i = 0; i < nombre_ligne*NBR_VECTORS_COMPONENT; i++) {
					current_neuron->i += current_neuron->get_main_data(i) * current_neuron->get_main_weight(i);
					//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " i=" << current_neuron->i << " x =" << current_neuron->get_main_data(i) << " weight = "<< current_neuron->get_main_weight(i) <<std::endl;
				}

				current_neuron->i += current_neuron->seuil;
				current_neuron->a = calcul_sortie_activation(current_neuron->i, option_fonction);
				//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " i=" << current_neuron->i << " a=" << current_neuron->a << std::endl;
			}
			else {
				current_neuron->i += calcul_activation_neurone_autre_couche(current_neuron);
				current_neuron->i += current_neuron->seuil;

				current_neuron->a = calcul_sortie_activation(current_neuron->i, option_fonction);
				//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id <<" i=" << current_neuron->i << " a=" << current_neuron->a << std::endl;
			}




			//d�finit le prochain neuron � �tudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//d�finit le prochain layer � �tudier
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
				//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " delta=" << current_neuron->delta << std::endl;
				//std::cout << "delta=" << current_neuron->delta << std::endl;
			}
			else {
				current_neuron->delta = calcul_signal_erreur_autre_couche(current_neuron, option_fonction);
				//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " delta=" << current_neuron->delta << std::endl;
				//std::cout << "delta=" << current_neuron->delta << std::endl;
			}

			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//d�finit le prochain layer � �tudier
		current_layer = current_layer->precedent_layer;

	} while (current_layer != NULL);


	//*************************** Phase 3 et 4 **********************************************************************
	current_layer = Net->premier_layer;

	int nombre_main_linked;
	do {
		
		current_neuron = current_layer->premier_neuron;

		do {
			nombre_main_linked = current_neuron->get_main_count();

			if (current_layer == Net->premier_layer) {
				for (int i = 0; i < nombre_main_linked; i++) {
					new_weight = calcul_correction_poids(Net->taux_apprentissage, current_neuron->get_main_data(i), current_neuron->delta, current_neuron->get_main_weight(i));
					current_neuron->set_main_weight(i, new_weight);
					//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " Link_counter" << i << " new_weight=" << current_neuron->get_main_weight(i) << std::endl;
				}
			}
			else {
				for (int i = 0; i < nombre_main_linked; i++) {
					Neuron* linked_neuron = current_neuron->get_main_source(i);
					new_weight = calcul_correction_poids(Net->taux_apprentissage, linked_neuron->a, current_neuron->delta, current_neuron->get_main_weight(i));
					current_neuron->set_main_weight(i, new_weight);
					//std::cout << "Couche " << current_layer->get_etage() << " Neuron" << current_neuron->id << " Link_counter" << i << " new_weight=" << current_neuron->get_main_weight(i) << std::endl;
				}
			}

			current_neuron = current_neuron->prochain_neuron;
		} while (current_neuron != NULL);
	
		current_layer = current_layer->prochain_layer;
	} while (current_layer != NULL);
	//**************************************************************************************************************

}




