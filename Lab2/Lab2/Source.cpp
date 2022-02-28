#include "Source.h"
#include "Network.h"

#pragma warning(disable:4996)


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


Input** parser_basedonne(const char* source_database, int nombre_line) {

	std::string data_line;
	int i = 0;
	int test = 0;
	int data_count = 0;
	double valeur;
	int random_input = rand() % DATA_TRAIN_SAMPLE + 1;

	Input** donnees = (Input**)malloc(sizeof(Input*)*nombre_line);

	for (int i = 0; i < nombre_line; i++) {
		donnees[i] = (Input*)malloc(sizeof(Input)*COLUM_STATIC);
	}

	std::ifstream file_database(source_database);


	while (getline(file_database, data_line)) { //Read chaque line du text file

		if (data_line[1] == ':') { //Si on rencontre leb debut dune donnees

			i++;

			if (i == random_input) { //Si la donnees quon a piger

				for (int line = 0; line < nombre_line; line++) {
					for (int colum = 0; colum < COLUM_STATIC; colum++) {
						getline(file_database, data_line, ' ');
						if (data_line != "") {
							donnees[line][colum].x = std::stod(data_line, 0);
							//std::cout << std::setprecision(20) << std::fixed << donnees[line][colum] << std::endl;
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

	return donnees;
}


int main(void) {
	
	Input** base_donnees;

	pretraiment_basedonne(40, "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_train.txt", "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/test_40.txt");
	pretraiment_basedonne(50, "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_train.txt", "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/test_50.txt");
	pretraiment_basedonne(60, "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/data_train.txt", "C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/test_60.txt");
	 
	base_donnees = parser_basedonne("C:/Users/Marti/Desktop/Hiver-2022/ELE767/Laboratoire2/ELE767_laboratoire2/test_40.txt", 40);

	
	int j_link = 0;
	int j_main = 0;
	double* weight_ptr;

	int nombre_couche = 4;
	//int nombre_neuron = 2;

	int nombre_neuron[6];

	nombre_neuron[0] = 480;
	nombre_neuron[1] = 3;
	nombre_neuron[2] = 3;
	nombre_neuron[3] = 3;
	nombre_neuron[4] = 3;
	nombre_neuron[5] = NULL;

	//int nombre_entrer = 3;
	int valeur_desirer = 2;

	int min_poid = 1;
	int max_poid = 100;

	double valeur_poid;

	srand(time(NULL));

	Neuron* neuron_prochaine_couche;
	Layer* current_layer;
	Neuron* current_neuron;

	Network Net(nombre_neuron[0], valeur_desirer, base_donnees, nombre_neuron[1]);


	//Creation des layers et neurons
	Net.add_layer(1, nombre_neuron[1]);
	current_layer = Net.premier_layer;

	for (int i = 1; i <= nombre_couche; i++) {
		for (int j = 0; j < current_layer->get_neuron_count(); j++)
		{
			current_layer->add_neuron(current_layer->get_etage(), j, nombre_neuron[i+1], nombre_neuron[i-1]);
		}
		if (i != nombre_couche) {
			Net.add_layer(i + 1, nombre_neuron[i + 1]);
			current_layer = current_layer->prochain_layer;
		}
	}

	//Creation des liens entre link et main avec des poids de nombre aleatoire
	current_layer = Net.premier_layer;
	 //lien entre les inputs
	int input_count = 0;
	
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 12; j++) {
			current_neuron = current_layer->premier_neuron;
			for (int k = 0; k < nombre_neuron[1]; k++) {
				valeur_poid = rand() % max_poid + min_poid;

				Net.set_weight_input(i, j, k, valeur_poid);
				Net.set_source_input(i, j, k, current_neuron);

				weight_ptr = &(Net.donnees_entre[i][j].link_source[k].weight);

				current_neuron->set_main_weight(input_count, weight_ptr);

				//std::cout << Net.donnees_entre[i][j].link_source[k].weight << "--->" << current_neuron->get_main_weight(input_count) << " input: " << 
					//current_neuron->get_i() << ","<< input_count << std::endl;

				current_neuron = current_neuron->prochain_neuron;
			}
			input_count++;
		}
	}

	current_neuron = current_layer->premier_neuron;
	//lien entre les neuronnnes
	while (current_layer != Net.dernier_layer) {

		neuron_prochaine_couche = current_layer->prochain_layer->premier_neuron;

		while (current_neuron != NULL) {
			while (neuron_prochaine_couche != NULL) {

				valeur_poid = rand() % max_poid + min_poid;

				current_neuron->set_link_weight(j_link, valeur_poid);
				current_neuron->set_link_source(j_link, neuron_prochaine_couche);

				weight_ptr = &(current_neuron->link_source[j_link].weight);

				neuron_prochaine_couche->set_main_weight(j_main, weight_ptr);
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

	//Net.display();
	system("pause");
	//Free la base de donnees
	for(int i = 0; i < 40; i++) {
		for (int j = 0; j < 12; j++) {
			free(base_donnees[i][j].link_source);
		}
		free(base_donnees[i]);
	}

	free(base_donnees);

	Net.display();
	//Net.display();
	//free(nombre_neuron);
	
	system("pause");
	//scanf_s("%d", &x);
	return 0;
}

