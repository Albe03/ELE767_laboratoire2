#include "Source.h"
#include <cstring>

#pragma warning(disable:4996)

#if NO_TEST
int main(void) {
	
	int nombre_vecteur = 40;

	Input** base_donnees;

	std::vector<int> vector;
	std::ifstream file_database;

	char entrer_choisi;
	double performance_vc;
	double performance_test = 0;
	int option = 0;

	int nombre_couche = 4;
	int epoque = 0;
	int epoque_tot = 0;

	int nombre_neuron[6];
	double min_poid = -0.1;
	double max_poid = 0.1;

	nombre_neuron[0] = 480;
	nombre_neuron[1] = 3;
	nombre_neuron[2] = 3;
	nombre_neuron[3] = 3;
	nombre_neuron[4] = 10;
	nombre_neuron[5] = NULL;

	base_donnees = (Input**)malloc(sizeof(Input*)*nombre_vecteur);

	for (int i = 0; i < nombre_vecteur; i++) {
		base_donnees[i] = (Input*)malloc(sizeof(Input)*COLUM_STATIC);
	}

	char fichier_data_train[] = "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_train.txt";
	char fichier_sortie[] = "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/donnees_sorties.txt";
	char fichier_data_vc[] = "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_vc.txt";
	char fichier_data_test[] = "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_test.txt";

	char fichier_to_train[40];

	srand(time(NULL));

	//Preinitialisation
	//pretraiment_basedonne(40, fichier_data_train, "donnees_train_40.txt");
	//pretraiment_basedonne(50, fichier_data_train, "donnees_train_50.txt");
	//pretraiment_basedonne(60, fichier_data_train, "donnees_train_60.txt");

	if (nombre_vecteur == 40)
		strcpy(fichier_to_train, "donnees_train_40.txt");

	if(nombre_vecteur == 50)
		strcpy(fichier_to_train, "donnees_train_50.txt");

	if(nombre_vecteur == 60)
		strcpy(fichier_to_train, "donnees_train_60.txt");


	//pretraiment_basedonne(nombre_vecteur, fichier_data_vc, "donnees_vc.txt");
	//pretraiment_basedonne(nombre_vecteur, fichier_data_test, "donnees_test.txt");


	parser_basedonne(file_database, fichier_to_train, nombre_vecteur, &entrer_choisi, vector, DATA_TRAIN_SAMPLE, base_donnees);
	

	file_database.close();

	//Creation du MLP
	Network Net(nombre_neuron[0], base_donnees, nombre_neuron[1], nombre_vecteur);

	creation_MLP(&Net, nombre_neuron, nombre_couche, min_poid, max_poid);

	//configuration des donnees en sortie
	config_donnee_sortie(entrer_choisi, fichier_sortie, Net.dernier_layer);



	do {
			performance_vc = 0.0;

			while (!epoque) {
				calcul_delta_generaliser(&Net, option);	
				epoque = parser_basedonne(file_database, fichier_to_train, nombre_vecteur, &entrer_choisi, vector, DATA_TRAIN_SAMPLE, base_donnees);
				update_MLP(&Net, entrer_choisi, base_donnees, fichier_sortie);
			}

			file_database.close();

			epoque_tot++;
			epoque = 0;
			
			while (!epoque) {
				epoque = parser_basedonne(file_database, "donnees_vc.txt", nombre_vecteur, &entrer_choisi, vector, DATA_VC_SAMPLE, base_donnees);
				update_MLP(&Net, entrer_choisi, base_donnees, fichier_sortie);
				performance_vc += evaluation_MLP(&Net, option);
				//performance_vc += 1(pass) ou 0(fail) = phase_1_function(Net, base_donnees); //Mettre la mise a jour des x sans modifier les poids
			}


			std::cout << "Avant la division performance vc : "<< performance_vc << std::endl;
			file_database.close();

			epoque = 0;
			
			performance_vc /= DATA_VC_SAMPLE;
			performance_vc *= 100;


			std::cout << "Apres la division performance vc :"<< performance_vc << std::endl;

	} while (performance_vc < 80.0 && epoque_tot < 100);

	while (!epoque) {
		epoque = parser_basedonne(file_database, "donnees_test.txt", nombre_vecteur, &entrer_choisi, vector, DATA_TEST_SAMPLE, base_donnees);
		//performance_test += 1(pass) ou 0(fail) = phase_1_function(Net, base_donnees); //Mettre la mise a jour des x sans modifier les poids
	}
	
	file_database.close();

	performance_test /= DATA_TEST_SAMPLE;

	

	system("pause");

	return 0;
}
#else
int main(void) {

	test();

	system("pause");
	return 0;
}
#endif

void pretraiment_basedonne(int _num_ligne_user, const char* source_database, const char* destination_database) {

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
			test_count++;
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

	fclose(file_train);
	file_generate.close();
}

int parser_basedonne(std::ifstream& file_database, const char* source_database, int nombre_line, char* data_piger, std::vector<int>& random_input_vector, int data_sample, Input ** donnees) {

	std::string data_line;
	int i = 0;
	int data_count = 0;
	double valeur;
	int random_input = rand() % data_sample - 1 + 0;


	if (random_input_vector.empty() == NULL) {
		for (int i = 0; i < random_input_vector.size(); i++) {
			if (random_input == random_input_vector[i]) {
				random_input = rand() % data_sample - 1 + 0;
				i = 0;
			}
		}
	}

	file_database.open(source_database);

	random_input_vector.push_back(random_input);

	file_database.seekg((((nombre_line) * ((23 * COLUM_STATIC) + (COLUM_STATIC-3)))*random_input));


	while (getline(file_database, data_line)) { //Read chaque line du text file
		if (data_line != "") {
			if (data_line[1] == ':') { //Si on rencontre leb debut dune donnees
				char* tmp = strdup(data_line.c_str());
				*data_piger = *tmp;
				for (int line = 0; line < nombre_line; line++) {
					for (int colum = 0; colum < COLUM_STATIC; colum++) {
						getline(file_database, data_line, ' ');
						if (data_line != "") {
							donnees[line][colum].x = std::stod(data_line, 0);
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
	Neuron* current_neuron;

	std::string data_line;

	std::ifstream file_data(fichier_sortie);

	while (getline(file_data, data_line)) {
		data_line_char = strdup(data_line.c_str());
		if (data_line_char[0] == entree_piger) {
			strtok(data_line_char, " ");

			current_neuron = derniere_couche->premier_neuron;

			while (current_neuron != NULL) {
				data = strtok(NULL, " ");
				output = (int)*data - '0';
				current_neuron->set_output(output);
				current_neuron = current_neuron->prochain_neuron;
			}
		}
		free(data_line_char);
	}


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
		for (int j = 0; j < 3; j++) {
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

void update_MLP(Network* Net, char entree_piger, Input ** base_donnees, const char* fichier_sortie) {

	Neuron* current_neuron;
	Layer* current_layer;

	Net->donnees_entre = base_donnees;
	
	int input_count = 0;

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
	//Update la sortie
	config_donnee_sortie(entree_piger, fichier_sortie, Net->dernier_layer);

	
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

	//********************************Phase 1**********************************************
	//Loop until dernier_layer

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