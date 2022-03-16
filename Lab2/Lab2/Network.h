/**
* @file Network.h
* @brief Contient les principales functions pour le Network
* 
*/


#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "layer.h"
#include <vector>

//#include "Source.h"

typedef struct {
	double x;
	Weight_source* link_source;
}Input;

class Network {


public:

	/**
	* @brief Constructeur principale du reseaux de neuronne. Il recoit le nombre de donnees pour une entree, les donnees, 
	* le nombre de neuron pour la premier couche et le nombre de vecteur dans la base de donnees.
	*
	* @param _input_count le nombre de donnees dans l'entree
	* @param _donnees les donnes qui a été generer
	* @param _neuron_count le nombre de neuron dans la premier couche cacher
	* @param _nombre_vecteur le nombre de vecteur dans la base de donnees
	*/
	Network(int _input_count, Input** _donnees, int _neuron_count, int _nombre_vecteur, int nombre_sortie);

	/**
	* @brief Destructeur de la class Network. Il desalloue les memoire prise par la base de donnees
	* et met les principale variable a NULL
	*/
	~Network();

	/**
	* @brief Cette fonction permet de ajouter une couche avec son identifiant et le nombre de neuronne.
	* Il va aussi faire l'allocation dynamique avec le nombre de neuron dans cette couche. 
	* 
	* @param _stage identifiant de la couche creer 
	* @param _neuron_count le nombre de neuronne dans cette couche
	*/
	void add_layer(int _stage, int _neuron_count);

	//void delete_layer();

	/**
	* @brief Cette fonction est seulement pour usage de debugage. Il affiche le nombre de couche 
	* avec le nombre neuronne et leur poids respectives. 
	* 
	*/
	void display();

	/**
	* @brief Cette fonction modifie le poids d'une donnees en entree. Comme la base de donnees
	* est un tableau 2D, il doit recevoir sa ligne et sa colonne. Il doit aussi recevoir
	* l'indice qui est associer a ce poids. 
	*
	* @param _i la ligne de la base de donnees
	* @param _j la colonne de la base de donnees
	* @param _i_neuron l'indice qui est associer au poids 
	* @param _weight le nouveau poids qu'on souhaite modifier
	*/
	void set_weight_input(int _i, int _j, int _i_neuron, double _weight);
	
	/**
	* @brief Cette fonction modifie la source d'une donnees en entree. Comme la base de donnees
	* est un tableau 2D, il doit recevoir sa ligne et sa colonne. Il doit aussi recevoir
	* l'indice qui est associer a cette source. 
	*
	* @param _i la ligne de la base de donnees
	* @param _j la colonne de la base de donnees
	* @param _i_neuron l'indice qui est associer au poids 
	* @param _source la nouvelle source qu'on souhaite modifier
	*/
	void set_source_input(int _i, int _j, int _i_neuron, Neuron* _source);

	/**
	* @brief Cette fonction retourne le nombre de vecteur qu'on a inserer initialement
	*/
	int get_nombre_vecteur();

	Input** donnees_entre;

	int** tableau_sortie;

	Layer* premier_layer;
	Layer* dernier_layer;

	double rate = 0.1;
	int nombre_sortie;

private:
	int input_count;
	int nombre_vecteur;
};

#endif