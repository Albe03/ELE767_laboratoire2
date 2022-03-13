#pragma once


#ifndef WEIGHT_H
#define WEIGHT_H

#include "neuron.h"

class Neuron;

/**
* @brief Classe de Link_source qui est la classe de la sortie du neuronne  
*/
class Weight_source{
public:
	double weight;
	Neuron* source;
};

/**
* @brief Classe de Main_source qui est la classe de l'entree du neuronne  
*/
class Main_weight_source {
public:
	double data;
	double* weight_ptr;
	Neuron* source;
};

/**
* @brief Cette class weight contient les functions pour la gestions des liens de poids entre les neuronnes 
* comme Main_source  
*/
class Weight {

public:

	/**
	* @brief Constructeur pour la classe du poids    
	* 
	* @param _etage l'identifiant de couche 
	* @param _neuron_count le nombre de neuronne dans cette couche
	*/
	Weight(int _link_count);

	/**
	* @brief Destruction de la classe weight   
	*/
	~Weight();

	/**
	* @brief Cette fonction modifie le poids dans la table data_table qui est dans main_source
	*    
	* 
	* @param _j l'identifiant du neuronne en lien  
	* @param _weight le nouveau poids a modifier
	*/
	void set_weight_ptr(int _j, double* _weight);

	void set_weight(int _j, double _weight);

	/**
	* @brief Cette fonction modifie l'adresse du neuronne dans la table data_table qui est dans main_source
	*    
	* @param _j l'identifiant du neuronne en lien 
	* @param _source l'adresse qu'on souhaite mettre
	*/
	void set_source(int _j, Neuron* _source);

	/**
	* @brief Cette fonction modifie la donnee en entre du neuronne dans la table data_table qui est dans main_source
	* 
	* @param _j l'identifiant de la donnee en entree 
	* @param _data la nouvelle donnees en entre qu'on souhaite mettre
	*/
	void set_data(int _j, double _data);

	/**
	* @brief Cette fonction retourne la donnee de l'entrre dans la table data_table qui est dans main_source 
	* 
	* @param _j l'identifiant de la donnee en entree
	*/
	double get_data(int _j);

	/**
	* @brief Cette fonction retourne le poids qui est situer dans la table data_table qui est dans main_source
	* 
	* @param _j identifiant du neuronne
	*/
	double get_weight(int _j);

	/**
	* @brief Cette fonction retourne la source qui est situer dans la table data_table qui est dans main_source
	* 
	* @param _j identifiant du neuronne
	*/
	Neuron* get_source(int _j);

private:
	int link_count;
	Main_weight_source* data_table;
};




#endif