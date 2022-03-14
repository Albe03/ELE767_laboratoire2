
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
					for (int colum_count = 0; colum_count < 2; colum_count++) {
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



////////////////////////////////  TEST  /////////////////////////////////
void test() {

	Input** base_donnees = (Input**)malloc(sizeof(Input*) * 1);	for (int i = 0; i < 1; i++) {		base_donnees[i] = (Input*)malloc(sizeof(Input) * 3);	}

	base_donnees[0][0].x = 1;
	base_donnees[0][1].x = 0;
	base_donnees[0][2].x = 1;

	int nombre_neuron[5];
	nombre_neuron[0] = 3;
	nombre_neuron[1] = 2;
	nombre_neuron[2] = 3;
	nombre_neuron[3] = 2;
	nombre_neuron[4] = NULL;

	//Network* Net(nombre_entrée_x, base_donnees, nombre_neuron_premiere_couche, nombre_vecteur_d_entree);
	Network Net(nombre_neuron[0], base_donnees, 2, 1);
	//creation_MLP(Net, nombre_neuron[], nombre_couche_tot, min_poid_random, max_poid_random);
	creation_MLP(&Net, nombre_neuron, 3, 1, 2);
	// Comment je crééer le Network sans rien ? (ou avec ce que je veux)
	////////////////////////////////////////////////////////////////////

	Layer* current_layer = Net.premier_layer;
	Neuron* current_neuron;


	///////////////////////////////////////////////////////////////////
	//sortie désiré
	//test_d[neuron]
	double test_d[] = { 1, 2 };

	///////////////////////////////////////////////////////////////////
	
	//test_seuil[layerx][neuron_couchex] (seuil tout neuron)
	double test_seuil[3][3];
	
	///////////////////////////////////////////////////////////////////
	//entree_x
	//test_entree[neuron_couche1]
	double test_entree[] = { 1, 0, 1 };

	//entree_x et leur neuron et poid respectif
	auto test_entree_weight = new double[3][2];

	//test_entree_weight[entree][neuron_couche1]
	test_entree_weight[0][0] = 1;
	test_entree_weight[0][1] = 2;
	test_entree_weight[1][0] = 3;
	test_entree_weight[1][1] = 4;
	test_entree_weight[2][0] = 5;
	test_entree_weight[2][1] = 6;
	
	///////////////////////////////////////////////////////////////////
	//couche 1
	double test_seuil_layer_1[] = { 1, 2 };

	//test_seuil[layer0][neuronx]
	test_seuil[0][0] = 1;
	test_seuil[0][1] = 2;

	//double weight_couche1[neuron_couche1][neuron_couche2];
	double weight_couche1[2][3];
	weight_couche1[0][0] = 7;
	weight_couche1[0][1] = 8;
	weight_couche1[0][2] = 9;
	weight_couche1[1][0] = 10;
	weight_couche1[1][1] = 11;
	weight_couche1[1][2] = 12;

	///////////////////////////////////////////////////////////////////
	//couche 2
	double test_seuil_layer_2[] = { 3, 4, 5 };

	//test_seuil[layer1][neuronx]
	test_seuil[1][0] = 3;
	test_seuil[1][1] = 4;
	test_seuil[1][2] = 5;

	//les poids seront donnés avec la couche3 par rapidité

	///////////////////////////////////////////////////////////////////
	//couche 3 - sortie
	double test_seuil_layer_3[] = { 6, 7 };

	//test_seuil[layer2][neuronx]
	test_seuil[2][0] = 6;
	test_seuil[2][1] = 7;

	//double weight_couche1[neuron_couche3][neuron_couche2];
	double weight_couche3[2][3];
	weight_couche3[0][0] = 13;
	weight_couche3[0][1] = 14;
	weight_couche3[0][2] = 15;
	weight_couche3[1][0] = 16;
	weight_couche3[1][1] = 17;
	weight_couche3[1][2] = 18;
	
	///////////////////////////////////////////////////////////////////


	//Loop until dernier_layer
	do {

		int counter_layer = 0;
		current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {

			int counter_neuron = 0;


			if (current_layer == Net.premier_layer) {
				
				
				//										Net.get_nombre_vecteur() = 1
				for (int vector_components_count = 0; vector_components_count < Net.get_nombre_vecteur(); vector_components_count++) {
					for (int vector_entree_count = 0; vector_entree_count < 3; vector_entree_count++) {
						for (int link_count = 0; link_count < current_layer->get_neuron_count(); link_count++) {
							if (Net.donnees_entre[vector_components_count][vector_entree_count].link_source[link_count].source == current_neuron) {
								
								//														    test_entree[neuron_couche1]
								Net.donnees_entre[vector_components_count][vector_entree_count].x = test_entree[link_count];
								Net.donnees_entre[vector_components_count][vector_entree_count].link_source[link_count].weight = test_entree_weight[vector_entree_count][link_count];
								//    test_entree_weight[entree][neuron_couche1]

								//std::cout << current_neuron->i << std::endl;
							}
						}
					}
				}

			}
			else if (current_layer == Net.dernier_layer) {
				current_neuron->d = test_d[counter_neuron];
				current_neuron->seuil = test_seuil[counter_layer][counter_neuron];
				
				//double weight_couche1[neuron_couche3][neuron_couche2];
				for (int link_couter = 0; link_couter < sizeof(weight_couche3); link_couter++) {
					current_neuron->main_source[link_couter].set_weight(link_couter, weight_couche3[counter_neuron][link_couter]);
				}
			}
			// couche2 uniquement adapter pour d'autre couche
			else {
				current_neuron->seuil = test_seuil[counter_layer][counter_neuron];

				//double weight_couche1[neuron_couche3][neuron_couche2];
				for (int link_couter = 0; link_couter < sizeof(weight_couche1); link_couter++) {
					current_neuron->link_source[link_couter].weight = weight_couche1[counter_neuron][link_couter];
				}
			}
			
			//std::cout << L++ << "NEXT" << std::endl;
			//définit le prochain neuron à étudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//définit le prochain layer à étudier
		current_layer = current_layer->prochain_layer;

	} while (current_layer != NULL);
	/********************************************************************************************************************************************************/


	//////////////////////////////////////////////// DISPLAY ALL /////////////////////////////////////////////////
	//Loop until dernier_layer
	do {

		int weight = 0;
		int counter_layer = 0;
		current_neuron = current_layer->premier_neuron;

		//Loop until dernier_neuron
		do {

			int counter_neuron = 0;

			for (int link_counter = 0; link_counter < sizeof(current_neuron->link_source); link_counter++) {

				 link_counter = 0;

				 weight = current_neuron->link_source[link_counter].weight;
				 
				 std::string s = "Layer : " + std::to_string(counter_layer)  + 
					 ";Neuron : " + std::to_string(counter_neuron) + 
					 ";Link :" + std::to_string(link_counter) + 
					 ";New-Weight : " + std::to_string(weight);
				 std::cout << s << std::endl;
			} 			

			//std::cout << L++ << "NEXT" << std::endl;
			//définit le prochain neuron à étudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//définit le prochain layer à étudier
		current_layer = current_layer->prochain_layer;

	} while (current_layer != NULL);
}


