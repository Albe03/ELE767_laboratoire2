/**
* @file layer.h
* @brief Contient les principales functions pour le layer
* 
*/

#pragma once

#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include "neuron.h"

class Layer {

public:

	/**
	* @brief Constructeur pour la couche qu'on souhaite creer. Il recoit son identifiant et le nombre de
	* neuronne qu'on va integer sur cette couche   
	* 
	* @param _etage l'identifiant de couche 
	* @param _neuron_count le nombre de neuronne dans cette couche
	*/
	Layer(int _etage, int _neuron_count);

	/**
	* @brief Destruction de la couche. Il desalloue tout les neuronnes sur sa couche  
	*/
	~Layer();

	/**
	* @brief Retourne l'identifiant de la couche  
	* 
	* @return retourn son identifiant
	*/
	int get_etage();

	/**
	* @brief retourne le nombre de neuronne sur sa couche 
	*
	* @return retourne le nombre de neuronne
	*/
	int get_neuron_count();

	/**
	* @brief Cette fonction ajoute un neuron dans la couche en question.  
	* 
	* @param _etage l'identifiant de la couche
	* @param _i l'identifiant du neurone 
	* @param _link_count le nombre de lien en sortie avec les autres neuronnes
	* @param _main_count le nombre de lien en entrer avec les autres neuronnes
	*/
	void add_neuron(int etage, int _i, int _link_count, int _main_count);

	Layer* prochain_layer;
	Layer* precedent_layer;

	Neuron* premier_neuron;
	Neuron* dernier_neuron;



private:

	/**
	* @brief supprimer le dernier neuronne dans sa couche 
	*/
	void delete_neuron();

	int neuron_count;
	int etage;
};


#endif