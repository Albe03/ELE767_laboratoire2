

#include "Source.h"
#include "Affichage.h"
#include "Fichier.h"
#include <cstring>


#pragma warning(disable:4996)
#define NOT_TEST


#if NOT_TEST true
int main(void) {
	
	Input** base_donnees;

	std::vector<int> vector;
	FILE* file_database_train;
	FILE* file_database_vc;
	FILE* file_database_test;

	DonneesConfig mesDonnees;
	DemarrerAffichage(&mesDonnees);

	int nombre_vecteur = mesDonnees.nombreSets;

	char entrer_choisi;
	double performance_ap;
	double performance_vc;
	double performance_test = 0;
	int option = mesDonnees.valFctAct;

	int nombre_couche = mesDonnees.CouchesTotales;
	int epoque = 0;
	int epoque_tot = 0;

	double min_poid = -0.1;
	double max_poid = 0.1;

	int nombre_sortie = mesDonnees.valSortie;
	double taux_apprentisage = mesDonnees.valTauxApprentissage;

	int time_elapsed = 0;

	int* nombre_neuron = (int*)malloc(sizeof(int)*(mesDonnees.valCachee + 2));
	
	nombre_neuron[0] = mesDonnees.valEntree;


	for (int i = 1; i <= mesDonnees.valCachee; i++) {
		nombre_neuron[i] = mesDonnees.valCouchesCachees[i - 1];
	}

	nombre_neuron[mesDonnees.CouchesTotales] = mesDonnees.valSortie;
	nombre_neuron[mesDonnees.CouchesTotales+1] = NULL;


	base_donnees = (Input**)malloc(sizeof(Input*)*nombre_vecteur);

	for (int i = 0; i < nombre_vecteur; i++) {
		base_donnees[i] = (Input*)malloc(sizeof(Input)*COLUM_STATIC);
	}

	char fichier_data_train[300];
	char fichier_data_vc[300];
	char fichier_data_test[300];
	char fichier_sortie[300];

	strcpy(fichier_data_train, mesDonnees.valDataTrain.c_str());
	strcpy(fichier_data_vc, mesDonnees.valDataVC.c_str());
	strcpy(fichier_data_test, mesDonnees.valDataTest.c_str());
	strcpy(fichier_sortie, mesDonnees.valFichierSortie.c_str());
	
	char fichier_to_train[40];

	srand(time(NULL));

	//Preinitialisation de set 40,50 et 60
	pretraitement_basedonne(40, fichier_data_train, "donnees_train_40.txt");
	pretraitement_basedonne(50, fichier_data_train, "donnees_train_50.txt");
	pretraitement_basedonne(60, fichier_data_train, "donnees_train_60.txt");

	pretraitement_basedonne(nombre_vecteur, fichier_data_vc, "donnees_vc.txt");
	pretraitement_basedonne(nombre_vecteur, fichier_data_test, "donnees_test.txt");

	//Les conditions pour les sets qu'on a choisie
	if (nombre_vecteur == 40)
		strcpy(fichier_to_train, "donnees_train_40.txt");

	if (nombre_vecteur == 50)
		strcpy(fichier_to_train, "donnees_train_50.txt");

	if (nombre_vecteur == 60)
		strcpy(fichier_to_train, "donnees_train_60.txt");

	//On ouvres les fichier qui a ete pretraiter
	file_database_train = fopen(fichier_to_train, "r");
	file_database_vc = fopen("donnees_vc.txt", "r");
	file_database_test = fopen("donnees_test.txt", "r");

	//On recupere la premier base de donnee dans le fichier d'apprentisage
	parser_basedonne(file_database_train, nombre_vecteur, &entrer_choisi, vector, DATA_TRAIN_SAMPLE, base_donnees);

	//Initialisation de l'arbre du MLP avec les carateristique mit
	Network Net(nombre_neuron[0], base_donnees, nombre_neuron[1], nombre_vecteur, nombre_sortie, taux_apprentisage);

	//Creation du reseaux de neuronne avec la configuration de tout les liens des poids
	creation_MLP(&Net, nombre_neuron, nombre_couche, min_poid, max_poid);

	//configuration des donnees en sortie dans le derniere couche du MLP
	config_donnee_sortie(entrer_choisi, fichier_sortie, Net.dernier_layer);

	//On sauvegarde tout les donnees en sortie dans un tableaux de sortie
	configuration_tableau_sortie(fichier_sortie, Net.tableau_sortie, nombre_sortie);

	auto startTime = std::chrono::system_clock::now(); //Commence la chronometre

	//On fait une boucle jusqua arriver une bonne performance en vc ou a 10 min 
	do {
		performance_vc = 0.0;
		performance_ap = 0.0;
		performance_test = 0.0;
		epoque_tot++;

		//Lapprentissage
		while (!epoque) {
			//Calcule la retropopagation
			calcul_retropopagation(&Net, option); 
			//retire la prochain donnees d'entre dans le fichier d'apprentissage
			epoque = parser_basedonne(file_database_train, nombre_vecteur, &entrer_choisi, vector, DATA_TRAIN_SAMPLE, base_donnees);
			//On fait la mise a jour des entree et sortie 
			update_MLP(&Net, entrer_choisi, base_donnees);
			//On fait la cumulation des bon resultats 
			performance_ap += evaluation_MLP(&Net, option);
		}

		performance_ap /= DATA_TRAIN_SAMPLE;
		performance_ap *= 100;


		auto currentTime = std::chrono::system_clock::now();
		time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
		std::cout << "Epoque " << epoque_tot << " performance apprentissage :\t\t" << performance_ap << "\t elapsed time(seconde): " << time_elapsed << std::endl;


		epoque = 0;

		//On fait le test avec les donnees de la validation croisser
		while (!epoque) {
			//retire la prochain donnees d'entre
			epoque = parser_basedonne(file_database_vc, nombre_vecteur, &entrer_choisi, vector, DATA_VC_SAMPLE, base_donnees);
			//On fait la mise a jour des entree et sortie
			update_MLP(&Net, entrer_choisi, base_donnees);
			//On fait la cumulation des bon resultats 
			performance_vc += evaluation_MLP(&Net, option);
		}

		epoque = 0;

		//On rapport avec tout les bon resultats optenue et le nombre total en entree pour calculer la performance 
		performance_vc /= DATA_VC_SAMPLE;
		performance_vc *= 100;

		

		currentTime = std::chrono::system_clock::now();
		time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
		std::cout << "Epoque " << epoque_tot << " performance vc :           \t\t" << performance_vc << "\t elapsed time(seconde): " << time_elapsed << std::endl;

		

		//On fait le test avec les donnees de test
		while (!epoque) {
			//retire la prochain donnees d'entre
			epoque = parser_basedonne(file_database_test, nombre_vecteur, &entrer_choisi, vector, DATA_TEST_SAMPLE, base_donnees);
			//On fait la mise a jour des entree et sortie
			update_MLP(&Net, entrer_choisi, base_donnees);
			//On fait la cumulation des bon resultats
			performance_test += evaluation_MLP(&Net, option);
		}

		epoque = 0;
		//On rapport avec tout les bon resultats optenue et le nombre total en entree pour calculer la performance
		performance_test /= DATA_TEST_SAMPLE;
		performance_test *= 100;

		currentTime = std::chrono::system_clock::now();
		time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
		std::cout << "Epoque " << epoque_tot << " performance test :         \t\t" << performance_test << "\t elapsed time(seconde): " << time_elapsed << std::endl;
	} while (performance_vc < mesDonnees.valPerformanceVoulue && time_elapsed < mesDonnees.valTempsLimite);

	sauvegarde_MLP(&Net);

	//load_MLP(&Net);


	//fermeture
	fclose(file_database_train);
	fclose(file_database_vc);
	fclose(file_database_test);
	
	system("pause");

	return 0;
}
#else
int main(void) {

	test_MLP();

	system("pause");
	return 0;
}
#endif


void pretraitement_basedonne(int _num_ligne_user, const char* source_database, const char* destination_database) {

	char value;
	double double_Es;

	int count = 0;
	int count_tot = 0;
	int space_count = 0;
	int num_line_user = _num_ligne_user;
	int num_line_data;
	int data_count = 0;

	char data[61][BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	std::string Es_str;
	double data_es[61];

	FILE* file_train = fopen(source_database, "r");
	std::ofstream file_generate(destination_database);

	data_es[MAX_LINE] = 99.0;
	memset(buffer, NULL, BUFFER_SIZE * sizeof(char));

	int test_count = 0;

	while (!feof(file_train)) {
		value = fgetc(file_train);
		buffer[count++] = value;
		//Si on a un espace
		if (value == ' ') {
			space_count++;
		}
		//Print le numero dans le fichier dapprentissage
		else if (value == ':') {
			num_line_data = MAX_LINE;
			if (data_count) { //On evalue les condition de Es

				for (int k = 0; num_line_data != num_line_user; k++) {
					if (data_es[k] < MIN_VALUE) { //Si Es est trop petit

						num_line_data--;

						for (int j = k; j < MAX_LINE; j++) {
							memcpy(data[j], data[j + 1], BUFFER_SIZE * sizeof(char));
							data_es[j] = data_es[j + 1];
						}
					}
				}
				for (int u = 0; u < num_line_data; u++) {
					file_generate << std::endl;
					file_generate << data[u];
				}
			}
			//test_count++;
			data_count = 0;

			file_generate << buffer;

			count = 0;
			space_count = 0;
			memset(buffer, NULL, BUFFER_SIZE * sizeof(char));
		}
		//Quand on arrive a la donnee de Energie static
		if (space_count == 13) {
			space_count = 0;
			value = fgetc(file_train);

			while (value != ' ') { //extration du Es
				Es_str.append(1, value); //On met les donnes dans un tableau de char
				value = fgetc(file_train);
			}

			double_Es = std::stod(Es_str); //On convertie le tableau de char a une variable double pour lenergie static
			Es_str.clear();

			data_es[data_count] = double_Es; //On met le Energie statique dans le tableau
			memcpy(data[data_count], buffer, BUFFER_SIZE * sizeof(char));  //On copy les donnees statique dans le tableau
			data_count++;

			while (space_count <= 12) { //On skip les donnees dynamique
				if (fgetc(file_train) == ' ') {
					space_count++;
				}
			}
			memset(buffer, NULL, BUFFER_SIZE * sizeof(char));
			count = 0;
			space_count = 1;
		}
	}

	//std::cout << "Data count = " << test_count << std::endl;
	fclose(file_train);
	file_generate.close();
}

int parser_basedonne(FILE* file_database, int nombre_line, char* data_piger, std::vector<int>& random_input_vector, int data_sample, Input ** donnees) {

	char* data = NULL;
	int i = 0;

	size_t len = 4096 + 1;
	int data_count = 0;

	const unsigned MAX_LENGTH = 600;
	char data_line[MAX_LENGTH];
	char buffer[MAX_LENGTH];

	double valeur;
	int random_input = rand() % data_sample - 1 + 0;

/*
	if (random_input_vector.empty() == NULL) {
		for (int i = 0; i < random_input_vector.size(); i++) {
			if (random_input == random_input_vector[i]) {
				random_input = rand() % data_sample - 1 + 0;
				i = 0;
			}
		}
	}
*/

	random_input_vector.push_back(random_input);

	fseek(file_database, (((nombre_line) * ((23 * COLUM_STATIC) + (COLUM_STATIC - 6)))*random_input), SEEK_SET);


	while (fgets(buffer, MAX_LENGTH, file_database) > 0) { //Read chaque line du text file
		if (buffer != "") {
			if (buffer[1] == ':') { //Si on rencontre leb debut dune donnees
				char* tmp = strdup(buffer);
				*data_piger = *tmp;
				free(tmp);
				for (int line = 0; line < nombre_line; line++) {
					fgets(data_line, MAX_LENGTH, file_database);
					data = strtok(data_line, " ");
					for (int colum = 0; colum < COLUM_STATIC; colum++) {
						if (data != "") {
							donnees[line][colum].x = std::stod(data, 0);
							data = strtok(NULL, " ");
							//std::cout << donnees[line][colum].x << std::endl;
						}
						else {
							colum--;
						}
					}
				}
				break;
			}
		}
	}


	if (random_input_vector.size() == data_sample) {
		random_input_vector.clear();
		return 1;
	}

	return 0;
}

void config_donnee_sortie(char entree_piger, const char* fichier_sortie, Layer* derniere_couche) {

	char* data_line_char;
	char* data;
	int output;
	int i = 0;

	Neuron* current_neuron;

	std::string data_line;

	std::ifstream file_data(fichier_sortie);
	

	while (getline(file_data, data_line)) {
		data_line_char = strdup(data_line.c_str());
		if (data_line_char[0] == entree_piger) {
			strtok(data_line_char, " ");

			current_neuron = derniere_couche->premier_neuron;
			//std::cout << std::endl;

			while (current_neuron != NULL) {
				data = strtok(NULL, " ");
				output = (int)*data - '0';
				//std::cout << output;
				current_neuron->set_output(output);
				current_neuron = current_neuron->prochain_neuron;
			}
		}
		free(data_line_char);
	}

	file_data.close();
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void creation_MLP(Network* Net, int* nombre_neuron, int nombre_couche, double min_poid, double max_poid) {

	Neuron* neuron_prochaine_couche;
	Layer* current_layer;
	Neuron* current_neuron;

	double valeur_poid;
	double* weight_ptr;
	int j_link = 0;
	int j_main = 0;

	//Creation des layers et neurons
	Net->add_layer(1, nombre_neuron[1]);
	current_layer = Net->premier_layer;

	for (int i = 1; i <= nombre_couche; i++) {
		for (int j = 0; j < current_layer->get_neuron_count(); j++)
		{
			current_layer->add_neuron(current_layer->get_etage(), j, nombre_neuron[i + 1], nombre_neuron[i - 1]);
		}
		if (i != nombre_couche) {
			Net->add_layer(i + 1, nombre_neuron[i + 1]);
			current_layer = current_layer->prochain_layer;
		}
	}

	//Creation des liens entre link et main avec des poids de nombre aleatoire
	current_layer = Net->premier_layer;
	//lien entre les inputs
	int input_count = 0;

	for (int i = 0; i < Net->get_nombre_vecteur(); i++) {
		for (int j = 0; j < NBR_VECTORS_COMPONENT; j++) {
			current_neuron = current_layer->premier_neuron;
			for (int k = 0; k < nombre_neuron[1]; k++) {
				valeur_poid = fRand(min_poid, max_poid);

				Net->set_weight_input(i, j, k, valeur_poid);
				Net->set_source_input(i, j, k, current_neuron);

				weight_ptr = &(Net->donnees_entre[i][j].link_source[k].weight);

				current_neuron->set_main_weight_ptr(input_count, weight_ptr);

				current_neuron->set_main_data(input_count, Net->donnees_entre[i][j].x);

				//std::cout << Net->donnees_entre[i][j].x << "--->" << current_neuron->get_main_data(input_count) << " input: " << 
				//current_neuron->get_i() << ","<< input_count << std::endl;

				current_neuron = current_neuron->prochain_neuron;
			}
			input_count++;
		}
	}

	current_neuron = current_layer->premier_neuron;
	//lien entre les neuronnnes
	while (current_layer != Net->dernier_layer) {

		neuron_prochaine_couche = current_layer->prochain_layer->premier_neuron;

		while (current_neuron != NULL) {
			while (neuron_prochaine_couche != NULL) {

				valeur_poid = fRand(min_poid, max_poid);

				current_neuron->set_link_weight(j_link, valeur_poid);
				current_neuron->set_link_source(j_link, neuron_prochaine_couche);

				weight_ptr = &(current_neuron->link_source[j_link].weight);

				neuron_prochaine_couche->set_main_weight_ptr(j_main, weight_ptr);
				neuron_prochaine_couche->set_main_source(j_main, current_neuron);

				neuron_prochaine_couche = neuron_prochaine_couche->prochain_neuron;
				j_link++;
			}
			current_neuron = current_neuron->prochain_neuron;
			neuron_prochaine_couche = current_layer->prochain_layer->premier_neuron;
			j_link = 0;
			j_main++;
		}
		j_main = 0;
		current_layer = current_layer->prochain_layer;
		current_neuron = current_layer->premier_neuron;
	}
}

void update_MLP(Network* Net, char entree_piger, Input ** base_donnees) {

	Neuron* current_neuron;
	Layer* current_layer;

	Net->donnees_entre = base_donnees;
	
	int input_count = 0;
	int output;

	current_layer = Net->premier_layer;
	//Update les entre
	for (int i = 0; i < Net->get_nombre_vecteur(); i++) {
		for (int j = 0; j < 12; j++) {
			current_neuron = current_layer->premier_neuron;
			for (int k = 0; k < Net->premier_layer->get_neuron_count(); k++) {

				current_neuron->set_main_data(input_count, Net->donnees_entre[i][j].x);

				//std::cout << Net->donnees_entre[i][j].x << "--->" << current_neuron->get_main_data(input_count) << " input: " << 
				//current_neuron->get_i() << ","<< input_count << std::endl;

				current_neuron = current_neuron->prochain_neuron;
			}
			input_count++;
		}
	}


	//config_donnee_sortie(entree_piger, "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/donnees_sorties.txt", Net->dernier_layer);
	
	current_layer = Net->dernier_layer;
	current_neuron = current_layer->premier_neuron;
	
	//Update la sortie
	for (int i = 0; i < Net->nombre_sortie; i++) {
		for (int j = 0; j < Net->nombre_sortie; j++) {
			output = (int)entree_piger - '0';
			if (current_neuron == NULL) {
				break;
			}
			else if (i == output) {
				current_neuron->d = Net->tableau_sortie[i][j];
				current_neuron = current_neuron->prochain_neuron;
			}
			else if (entree_piger == 'o') {
				current_neuron->d = Net->tableau_sortie[i][j];
				current_neuron = current_neuron->prochain_neuron;
			}

		}
	}

	current_layer = Net->premier_layer;
	//current_neuron = current_layer->premier_neuron;
	//Fait un clean des variables
	do{
		current_neuron = current_layer->premier_neuron;
		do {
		
			current_neuron->a = 0.0;
			current_neuron->i = 0.0;
			current_neuron->delta = 0.0;
			
			current_neuron = current_neuron->prochain_neuron;
		} while (current_neuron != NULL);
	
	
		current_layer = current_layer->prochain_layer;
	} while (current_layer != NULL);
}

int evaluation_MLP(Network* Net, int option_fonction) {


	Layer* current_layer = Net->premier_layer;
	Neuron* current_neuron;
	int nombre_neuron;
	//********************************Phase 1**********************************************
	//Loop until dernier_layer
	int nombre_ligne = Net->get_nombre_vecteur();

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
			}
			else {
				current_neuron->i += calcul_activation_neurone_autre_couche(current_neuron);
				current_neuron->i += current_neuron->seuil;

				current_neuron->a = calcul_sortie_activation(current_neuron->i, option_fonction);
			}

			//définit le prochain neuron à étudier
			current_neuron = current_neuron->prochain_neuron;

		} while (current_neuron != NULL);


		//définit le prochain layer à étudier
		current_layer = current_layer->prochain_layer;

	} while (current_layer != NULL);
	/********************************************************************************************************************************************************/

	current_layer = Net->dernier_layer;
	current_neuron = current_layer->premier_neuron;

	int* array_comparaison = (int*)malloc(sizeof(int)*Net->dernier_layer->get_neuron_count());

	double max_a = -999.0;
	int neuron_count = 0;
	int indicater = 0;

	do {
	
		if (max_a < current_neuron->a) {
		
			max_a = current_neuron->a;

			indicater = neuron_count;
		}
	
		neuron_count++;
		current_neuron = current_neuron->prochain_neuron;
	} while (current_neuron != NULL);

	
	for (int i = 0; i < Net->dernier_layer->get_neuron_count(); i++) {
	
		if (i == indicater) {
			array_comparaison[i] = 1;
		}
		else {
			array_comparaison[i] = 0;
		}
	}

	current_neuron = current_layer->premier_neuron;

	for (int i = 0; i < Net->dernier_layer->get_neuron_count(); i++) {
	
		if (array_comparaison[i] - current_neuron->d) {
			return 0;
		}
	
		current_neuron = current_neuron->prochain_neuron;
	}

	free(array_comparaison);
	return 1;
}

void configuration_tableau_sortie(const char* fichier_sortie, int** tableau_sortie, int nombre_sortie) {

	char* data_line_char;
	char* data;
	int output;
	int i = 0;

	std::string data_line;

	std::ifstream file_data(fichier_sortie);


	while (getline(file_data, data_line)) {
		data_line_char = strdup(data_line.c_str());

		strtok(data_line_char, " ");

		for (int j = 0; j < nombre_sortie; j++) {
			data = strtok(NULL, " ");
			output = (int)*data - '0';
			tableau_sortie[i][j] = output;
		}

		i++;

		free(data_line_char);
	}

	file_data.close();
}

void load_MLP(Network* Net) {

	ifstream FichierDonnees(NOM_BASE_DONNEE);

	Neuron* current_neuron;
	Layer* current_layer;
	double new_weight;
	int nombre_neuron_precedente;
	int nombre_ligne;
	std::string data_line;

	current_layer = Net->premier_layer;
	current_layer->prochain_layer;
	nombre_ligne = Net->get_nombre_vecteur();
	
	do {

		current_neuron = current_layer->premier_neuron;
		do {

			if (current_layer == Net->premier_layer) { //premier layer

				for (int i = 0; i < nombre_ligne*NBR_VECTORS_COMPONENT; i++) {
					getline(FichierDonnees, data_line);

					new_weight = std::stod(data_line.c_str(),0);
					current_neuron->set_main_weight(i, new_weight);
				}
			}
			else { //les autres layer
			
				for (int i = 0; i < nombre_neuron_precedente; i++) {
					getline(FichierDonnees, data_line);
					
					new_weight = std::stod(data_line.c_str(), 0);
					current_neuron->set_main_weight(i, new_weight);
				}
			}

			current_neuron = current_neuron->prochain_neuron;
		} while (current_neuron != NULL);

		nombre_neuron_precedente = current_layer->get_neuron_count();
		current_layer = current_layer->prochain_layer;
	} while (current_layer != NULL);

	FichierDonnees.close();
}

void sauvegarde_MLP(Network* Net) {

	ofstream FichierDonnees(NOM_BASE_DONNEE);
	Neuron* current_neuron;
	Layer* current_layer;
	double new_weight;
	int nombre_neuron_precedente;
	int nombre_ligne;
	int nombre_couche;
	int move_colum = 4;

	current_layer = Net->premier_layer;
	current_layer->prochain_layer;
	nombre_ligne = Net->get_nombre_vecteur();

	nombre_couche = Net->dernier_layer->get_etage();

	do {

		current_neuron = current_layer->premier_neuron;
		do {

			if (current_layer == Net->premier_layer) { //premier layer

				for (int i = 0; i < nombre_ligne*NBR_VECTORS_COMPONENT; i++) {
					new_weight = current_neuron->get_main_weight(i);
					FichierDonnees << std::setprecision(6) << new_weight << "\n";

				}
			}
			else { //les autres layer

				for (int i = 0; i < nombre_neuron_precedente; i++) {
					new_weight = current_neuron->get_main_weight(i);
					FichierDonnees << std::setprecision(6) << new_weight << "\n";
				}
			}

			current_neuron = current_neuron->prochain_neuron;
		} while (current_neuron != NULL);

			nombre_neuron_precedente = current_layer->get_neuron_count();
			current_layer = current_layer->prochain_layer;
	} while (current_layer != NULL);

	FichierDonnees.close();
}
	
void test_MLP() {

	Input** base_donnees = (Input**)malloc(sizeof(Input*) * 1);

	for (int i = 0; i < 1; i++) {
		base_donnees[i] = (Input*)malloc(sizeof(Input) * 2);
	}

	base_donnees[0][0].x = 1;
	base_donnees[0][1].x = 0;
	base_donnees[0][2].x = 1;

	int nombre_neuron[5];

	nombre_neuron[0] = 3;
	nombre_neuron[1] = 2;
	nombre_neuron[2] = 3;
	nombre_neuron[3] = 2;
	nombre_neuron[4] = NULL;

	int nombre_vecteur = 1;

	double min_poid = 0;
	double max_poid = 0;

	int test_val;

	Network Net(nombre_neuron[0], base_donnees, nombre_neuron[1], nombre_vecteur, NULL, 0.1);

	creation_MLP(&Net, nombre_neuron, 3, min_poid, max_poid);


	Net.donnees_entre[0][0].link_source[0].weight = 1;
	Net.donnees_entre[0][0].link_source[1].weight = 2;

	Net.donnees_entre[0][1].link_source[0].weight = 3;
	Net.donnees_entre[0][1].link_source[1].weight = 4;

	Net.donnees_entre[0][2].link_source[0].weight = 5;
	Net.donnees_entre[0][2].link_source[1].weight = 6;

	test_val = Net.premier_layer->premier_neuron->get_main_weight(2);

	Net.premier_layer->premier_neuron->set_link_weight(0, 7);
	Net.premier_layer->premier_neuron->set_link_weight(1, 8);
	Net.premier_layer->premier_neuron->set_link_weight(2, 9);
	Net.premier_layer->premier_neuron->seuil = 1;

	Neuron* prochain_neuron;

	prochain_neuron = Net.premier_layer->premier_neuron->prochain_neuron;

	prochain_neuron->set_link_weight(0,10);
	prochain_neuron->set_link_weight(1, 11);
	prochain_neuron->set_link_weight(2, 12);

	prochain_neuron->seuil = 2;

	Net.premier_layer->prochain_layer->premier_neuron->set_link_weight(0,13);
	Net.premier_layer->prochain_layer->premier_neuron->set_link_weight(1, 14);

	Net.premier_layer->prochain_layer->premier_neuron->seuil = 3;

	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->set_link_weight(0, 15);
	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->set_link_weight(1, 16);

	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->seuil = 4;

	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->prochain_neuron->set_link_weight(0, 17);
	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->prochain_neuron->set_link_weight(1, 18);

	Net.premier_layer->prochain_layer->premier_neuron->prochain_neuron->prochain_neuron->seuil = 5;

	Net.dernier_layer->premier_neuron->seuil = 6;
	Net.dernier_layer->premier_neuron->d = 1;

	Net.dernier_layer->premier_neuron->prochain_neuron->seuil = 7;
	Net.dernier_layer->premier_neuron->prochain_neuron->d = 2;


	calcul_retropopagation(&Net, 1);

}
