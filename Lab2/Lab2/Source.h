/**
* @file Source.h
* @brief Contient les principales functions pour faire le MLP
* 
*/


#pragma once
#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <clocale>
#include <iomanip> 

#include <cstring>
#include "Network.h"


#define MIN_VALUE 0.45
#define BUFFER_SIZE 400
#define MAX_LINE 60
#define COLUM_STATIC 12
#define DATA_TRAIN_SAMPLE 1340

/**
* @brief Cette fonction fait le pretratement des donnees en choissisant le nombre de ligne en parametre.
* À la fin de cette function, il va gerer un fichier text dans votre projet qui va ordonner chacune des entrees
* avec le nombre de ligne 
* @param _num_ligne_user nombre de ligne qu'on souhaite faire le traitement
* @param source_database fichier source qu'on souhaite faite le traitement
* @param destination_database ce fichier va etre generer une fois que la function va etre terminer
*/
void pretraiment_basedonne(int _num_ligne_user, const char* source_database, const char* destination_database);

/**
* @brief Cette function va lire un fichier qui a ete deja pretraiter, puis il va choisir une entree aleatoire 
* et il va generer une base_donnees avec l'entree choisie
* @param source_database fichier deja pretraiter
* @param nombre_line le nombre_line du fichier qui a ete pretraiter
* @param data_piger l'entree qu'on a choisie aleatoirement
*/
Input** parser_basedonne(const char* source_database, int nombre_line, char* data_piger);

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
* @param nombre_couche  le poid maximun qui peut etre generer
*/
void creation_MLP(Network* Net, int* nombre_neuron, int nombre_couche, double min_poid, int max_poid);

#endif