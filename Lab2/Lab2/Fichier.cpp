#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include "Fichier.h"
#include "Affichage.h"


#define NOM_BASE_DONNEE "Base_de_donnees.txt"
#define NOM_FICHIER_CONFIG "Config.txt"

using namespace std;

static FILE *BaseDonnee;
static FILE *FichierConfig;


void CreerFichierConfig() {
	FichierConfig = fopen(NOM_FICHIER_CONFIG, "w+");
	assert(FichierConfig);
}

void CreerBaseDonnees() {
	BaseDonnee = fopen(NOM_BASE_DONNEE, "w");
	assert(BaseDonnee);
}

int EcrireFichierConfig(int nombreSets, int Entree, int Cachee, int Sortie, int FctAct, int CouchesCachees[NB_COUCHES_CACHEES_MAX], 
	double valTauxApprentissage, int valTempsLimite, int valPerformanceVoulue, string valDataTrain, string valDataVC, string valDataTest, string valFichierSortie) {
	ofstream FichierConfig(NOM_FICHIER_CONFIG);
	// Ajoute toutes les donnees dans le fichier de config
	if (FichierConfig.is_open())
	{
		FichierConfig << nombreSets;
		FichierConfig << "\n";
		FichierConfig << Entree;
		FichierConfig << "\n";
		FichierConfig << Cachee;
		FichierConfig << "\n";
		FichierConfig << Sortie;
		FichierConfig << "\n";
		FichierConfig << FctAct;
		FichierConfig << "\n";

		for (int i = 0; i < Cachee; i++)
		{
			FichierConfig << CouchesCachees[i];
			FichierConfig << "\n";
		}

		FichierConfig << valTauxApprentissage;
		FichierConfig << "\n";
		FichierConfig << valTempsLimite;
		FichierConfig << "\n";
		FichierConfig << valPerformanceVoulue;
		FichierConfig << "\n";

		FichierConfig << valDataTrain;
		FichierConfig << "\n";
		FichierConfig << valDataVC;
		FichierConfig << "\n";
		FichierConfig << valDataTest;
		FichierConfig << "\n";
		FichierConfig << valFichierSortie;
		FichierConfig << "\n";

		FichierConfig.close();
		return 0;
	}
	else
		return -1;
}


int LireFichierConfig(int *nombreSets, int *Entree, int *Cachee, int *Sortie, int *FctAct, int CouchesCachees[NB_COUCHES_CACHEES_MAX],  
	double *valTauxApprentissage, int *valTempsLimite, int *valPerformanceVoulue, string *valDataTrain, string *valDataVC, string *valDataTest, string *valFichierSortie) {
	ifstream FichierConfig;
	FichierConfig.open(NOM_FICHIER_CONFIG);

	if (!FichierConfig)
		return -1;

	// Lit fichier ligne par ligne
	FichierConfig >> *nombreSets;
	FichierConfig >> *Entree;
	FichierConfig >> *Cachee;
	FichierConfig >> *Sortie;
	FichierConfig >> *FctAct;
	for (int i = 0; i < *Cachee; i++)
	{
		FichierConfig >> CouchesCachees[i];
	}

	FichierConfig >> *valTauxApprentissage;
	FichierConfig >> *valTempsLimite;
	FichierConfig >> *valPerformanceVoulue;

	FichierConfig >> *valDataTrain;
	FichierConfig >> *valDataVC;
	FichierConfig >> *valDataTest;
	FichierConfig >> *valFichierSortie;
	return 0;
}

//int Data[int couche][int poids], int NombrePoids[int couche]
void AjouterBaseDonnees(int **Data, int *NombrePoids, int NombreCouches) {
	
	ofstream FichierDonnees(NOM_BASE_DONNEE);
	// Ajoute toutes les donnees dans le fichier de config
	if (FichierDonnees.is_open()) {
		for (int i = 0; i < NombreCouches; i++)
		{
			for (int j = 0; j < NombrePoids[i]; j++)
			{
				FichierDonnees << Data[i][j] << " ";
			}
			FichierDonnees << "\n";
		}
	}
	FichierDonnees.close();
}

#if 0
void PrendreBaseDonnees(int **Data) {
	ifstream FichierDonnees;
	FichierDonnees.open(NOM_BASE_DONNEE);
	string str;
	
	int i = 0;
	int j = 0;

	if (!FichierDonnees)
		return;
	// Ajoute toutes les donnees dans le fichier de config
	if (FichierDonnees.is_open()) {
		// Pour chaque couche
		while (getline(FichierDonnees, str)) {
			// Sépare les données de la couche pris de https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
			// Used to split string around spaces.
			istringstream ss(str);

			string word; // for storing each word

			// Traverse through all words
			// while loop till we get 
			// strings to store in string word
			while (ss >> word)
			{
				Data[i][j] = stoi(word);
				j++;
			}
			i++;
		}


		/*
		for (int i = 0; i < NombreCouches; i++)
		{
			for (int j = 0; j < NombrePoids[i]; j++)
			{
				FichierDonnees >> Data[i][j];
			}
		}*/
	}
	FichierDonnees.close();
}
#else
void PrendreBaseDonnees(int (&Data)[20][20]) {
	ifstream FichierDonnees;
	FichierDonnees.open(NOM_BASE_DONNEE);
	string str;

	int i = 0;
	int j = 0;

	if (!FichierDonnees)
		return;
	// Ajoute toutes les donnees dans le fichier de config
	if (FichierDonnees.is_open()) {
		// Pour chaque couche
		while (getline(FichierDonnees, str)) {
			// Sépare les données de la couche pris de https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
			// Used to split string around spaces.
			istringstream ss(str);

			string word; // for storing each word

			// Traverse through all words
			// while loop till we get 
			// strings to store in string word
			while (ss >> word)
			{
				Data[i][j] = stoi(word);
				j++;
			}
			i++;
		}


		/*
		for (int i = 0; i < NombreCouches; i++)
		{
			for (int j = 0; j < NombrePoids[i]; j++)
			{
				FichierDonnees >> Data[i][j];
			}
		}*/
	}
	FichierDonnees.close();
}
#endif

//  nb neuronnes premiere couche avec poids. nombre de poids
// ex : 1:10 (premier layer = 10 neuronnes)
//		2 (poids)
//		5 (poids)
// Fonction sauvegarde tous poids + Utiliser sauvegarde
// Ordre : entrées et ensuite sortie
// *** neuronne a poids entrée et poids sortie
// Voir tabs Link (couche entrée 1 neuronne) et main (sortie)
// ex deltaGeneraliser.cpp current_neuron->get_main_weight(i)
// Tab 2 dimensions [#neuronne][poids]

void FermerBaseDonnees() {
	fclose(BaseDonnee);
}

void FermerFichierConfig() {
	fclose(FichierConfig);
}
