#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <assert.h>
#include <string>
#include "Fichier.h"


#define NOM_BASE_DONNEE "Base_de_donnees.txt"
#define NOM_FICHIER_CONFIG "Config.txt"

using namespace std;

static FILE *BaseDonnee;
static FILE *FichierConfig;

// Quoi mettre dans le fichier? Mettre en param
void CreerFichierConfig() {
	FichierConfig = fopen(NOM_FICHIER_CONFIG, "w+");
	assert(FichierConfig);
}


void CreerBaseDonnees() {
	BaseDonnee = fopen(NOM_BASE_DONNEE, "w+");
	assert(BaseDonnee);
}

void LireFichierConfig() {
	FichierConfig = fopen(NOM_FICHIER_CONFIG, "r");
}


void AjouterBaseDonnees(const char Data[]) {
	fprintf(BaseDonnee, Data);
	fprintf(BaseDonnee, "\n");
}

void FermerBaseDonnees() {
	fclose(BaseDonnee);
}

void FermerFichierConfig() {
	fclose(FichierConfig);
}
