/**
* @file Source.h
* @brief Contient les principales functions pour faire le MLP
* 
*/


#pragma once
#ifndef SOURCE_H
#define SOURCE_H

#define _GNU_SOURCE

#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <clocale>
#include <iomanip>
#include <vector>
#include <chrono>
#include <ctime>


#include <cstring>
#include "Network.h"
#include "DeltaGeneraliser.h"


#define MIN_VALUE 0.45
#define BUFFER_SIZE 400
#define MAX_LINE 60
#define COLUM_STATIC 12
#define DATA_TRAIN_SAMPLE 1340
#define DATA_VC_SAMPLE 120
#define DATA_TEST_SAMPLE 780

#define NBR_VECTORS_COMPONENT 12
#define VALEUR_TEST 3

/**
* @brief Cette fonction fait le pretratement des donnees en choissisant le nombre de ligne en parametre.
* À la fin de cette function, il va gerer un fichier text dans votre projet qui va ordonner chacune des entrees
* avec le nombre de ligne 
* @param _num_ligne_user nombre de ligne qu'on souhaite faire le traitement
* @param source_database fichier source qu'on souhaite faite le traitement
* @param destination_database ce fichier va etre generer une fois que la function va etre terminer
*/
void pretraitement_basedonne(int _num_ligne_user, const char* source_database, const char* destination_database);

/**
* @brief Cette function va lire un fichier qui a ete deja pretraiter, puis il va choisir une entree aleatoire 
* et il va generer une base_donnees avec l'entree choisie
* @param file_database structure de fichier pour l'ouverture
* @param source_database fichier deja pretraiter en string
* @param nombre_line le nombre_line du fichier qui a ete pretraiter
* @param data_piger l'entree qu'on a choisie aleatoirement
* @param random_input_vector vector qui sert a accumuler les entree traiter
* @param data_sample nombre de entree dans le fichier
* @param donnees tableau 2d qui enmagasine les donnees
*
* @return retourne vrai si on a atteint une epoque sinon retourne faux
*/
int parser_basedonne(FILE* file_database, int nombre_line, char* data_piger, std::vector<int>& random_input_vector, int data_sample, Input ** donnees);

/**
* @brief Cette function va lire un fichier de sortie deja configurer avec l'entree qu'on a choisi 
* et il va configurer les sortie dans la derniere couche du reseaux de neuronnes
* @param entree_piger l'entree qu'on a choisie
* @param fichier_sortie fichier de sortir dans le projet
* @param dernier_couche la dernier couche du reseaux de neuronnes
*/
void config_donnee_sortie(char entree_piger, const char* fichier_sortie, Layer* derniere_couche);

/**
* @brief Creation du reseaux de neuronnes avec les nombres de entrees, nombre de neuronnes, nombre de couches. 
* Il va aussi configurer chacune des poids aleatoirement  
* @param Net Le reseaux de neuronnes
* @param nombre_neuron Un tableau qui contient le nombres de neuronnes pour chaque couche
* @param nombre_couche le nombre de couche
* @param min_poid le poid minimum qui peut etre generer  
* @param max_poid  le poid maximun qui peut etre generer
*/
void creation_MLP(Network* Net, int* nombre_neuron, int nombre_couche, double min_poid, double max_poid);

/**
* @brief Cette fonction va mettre a jour les nouvelle donnees en entree et les sortie desirer
* 
* @param Net Le reseaux de neuronnes
* @param entrer_piger l'entree quon piger
* @param base_donnees la nouvelle base de donnees
*/
void update_MLP(Network* Net, char entree_piger, Input ** base_donnees);

/**
* @brief Cette fonction va evaluer les sortir obtenue avec les sortie desirer et va retourner 1 si on 
* optient les memes sortie, sinon il retourne 0 
* @param Net Le reseaux de neuronnes
* @param option_fonction la fonction d'activation qu'on desire soit 0 pour sigmoide ou 1 pour le sinus
*/
int evaluation_MLP(Network* Net, int option_fonction);

/**
* @brief Cette fonction va mettre a jour les nouvelle donnees en entree et les sortie desirer
* 
* @param Net Le reseaux de neuronnes
* @param entrer_piger l'entree quon piger
* @param base_donnees la nouvelle base de donnees
*/
void configuration_tableau_sortie(const char* fichier_sortie, int** tableau_sortie, int nombre_sortie);

void load_MLP(Network* Net);

void sauvegarde_MLP(Network* Net);

void test_MLP();
#endif