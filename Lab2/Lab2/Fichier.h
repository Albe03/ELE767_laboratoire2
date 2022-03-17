#pragma once
#include "Affichage.h"
using namespace std;

void CreerFichierConfig();

void CreerBaseDonnees();

//int EcrireFichierConfig(Affichage MonAffichage);
int EcrireFichierConfig(int nombreSets, int Entree, int Cachee, int Sortie, int FctAct, int CouchesCachees[NB_COUCHES_CACHEES_MAX], 
	double valTauxApprentissage, int valTempsLimite, int valPerformanceVoulue, string valDataTrain, string valDataVC, string valDataTest, string valFichierSortie);

//int LireFichierConfig(Affichage *MonAffichage);
int LireFichierConfig(int *nombreSets, int *Entree, int *Cachee, int *Sortie, int *FctAct, int CouchesCachees[NB_COUCHES_CACHEES_MAX], 
	double *valTauxApprentissage, int *valTempsLimite, int *valPerformanceVoulue, string *valDataTrain, string *valDataVC, string *valDataTest, string *valFichierSortie);

void FermerBaseDonnees();

void FermerFichierConfig();

void AjouterBaseDonnees(int **Data, int *NombrePoids, int NombreCouches);

//void PrendreBaseDonnees(int **Data);
void PrendreBaseDonnees(int(&Data)[20][20]);

