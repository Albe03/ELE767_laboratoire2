/**
* @file Neuron.h
* @brief Contient les principales functions pour le Neuron
* 
*/

#pragma once

#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "weight.h"


class Weight;
class Weight_source;

class Neuron{

public:

	/**
	* @brief Constructeur pour la creation d'un Neuron, Il recoit l'identifiant de la couche qui est situer, 
	* l'identifiant du neuron, le nombre de poids en entrer et en sortie qui est en lien avec les neuronnes. Il fait aussi
	* une allocation dynamique de Link_source et main_source.  
	* 
	* @param _etage l'identifiant de couche qui se situe le neuronne
	* @param _i l'identifiant du neuron
	* @param _link_count le nombre de lien en sortie avec les autres neuronnes
	* @param _main_count le nombre de lien en entrer avec les autres neuronnes
	*/
	Neuron(int _etage, int _i, int _link_count, int _main_count);

	/**
	* @brief Destruction du neuronne, il desalloue les tableaux allouer pour Link_source et main_source   
	*/
	~Neuron();

	/**
	* @brief Cette fonction retourne l'identifiant du neuronne en question  
	* 
	* @return retourne l'identifiant du neuronne
	*/
	int get_i();

	/**
	* @brief  Cette fonction met l'addresse du neuronne qui est relier par leur poids. 
	* Cette adresse est mit dans _source. Chaque neuronne va avoir un tableau qui contient tout les
	* lien des autres neuronnes. 
	*
	* @param _j l'identifiant du neuronne qui est en lien 
	* @param _source l'adresse du neuronne qui est en lien 
	*/
	void set_link_source(int _j, Neuron* _source);

	Neuron* get_link_source(int _j);

	/**
	* @brief  Cette fonction met le nouveau poids qui est relier par le neuronne. Cette valeur
	* est mit dans _weight
	*
	* @param _j l'identifiant du neuronne qui est relier 
	* @param _weight la valeur du poid qu'on souhaite mettre la nouvelle valeur
	*/
	void set_link_weight(int _j, double _weight);

	double get_link_weight(int _j);

	/**
	* @brief  Cette fonction met l'addresse du neuronne qui est relier par leur poids. 
	* Cette adresse est mit dans _source. Chaque neuronne va avoir un tableau qui contient tout les
	* lien des autres neuronnes. 
	*
	* @param _j l'identifiant du neuronne qui est en lien 
	* @param _source l'adresse du neuronne qui est en lien 
	*/
	void set_main_source(int _j, Neuron* _source);

	/**
	* @brief  Cette fonction met le nouveau poids qui est relier par le neuronne. Cette valeur
	* est mit dans _weight
	*
	* @param _j l'identifiant du neuronne qui est relier 
	* @param _weight la valeur du poid qu'on souhaite mettre la nouvelle valeur
	*/
	void set_main_weight_ptr(int _j, double* _weight);

	void set_main_weight(int _j, double _weight);
	/**
	* @brief  Cette fonction retourn l'adresse du neuronne qui sera identifier par son _j
	*
	* @param _j l'identifiant du neuronne
	*
	* @return retourne l'adresse du neuronne
	*/
	Neuron* get_main_source(int _j);

	/**
	* @brief  Cette fonction retourn le poids du neuronne qui sera identifier par son _j
	*
	* @param _j l'identifiant du neuronne
	*
	* @return retourne le poid du neuronne
	*/
	double get_main_weight(int _j);

	/**
	* @brief Cette fonction met la valeur de la donnees de l'entree 
	* du neuronne est relier (Les neuronnes dans la premier couche)
	*
	* @param _j l'identifiant du neuronne en question
	* @param _data la valeur de la donnee de l'entree
	*/
	void set_main_data(int _j, double _data);

	/**
	* @brief Cette fonction retourne la donnees de l'entree du neuronne en question (Les neuronnes dans la premier couche)
	*
	* @param _j l'identifiant du neuronne
	*
	* @return retourne la donnees de l'entree du neuronne 
	*/
	double get_main_data(int _j);

	/**
	* @brief  Cette fonction retourne le nombre de lien en sortie qui est connecter sur cette neuronne
	*
	* @return retourne le nombre de lien  
	*/
	int get_link_count();

	/**
	* @brief  Cette fonction retourne le nombre de lien en entrer qui est connecter sur cette neuronne
	*
	* @return retourne le nombre de lien  
	*/
	int get_main_count();

	/**
	* @brief Cette fonction modifie la donnees desirer du neuronne (Les neuronnes dans la derniere couche)
	*
	* @param _output la donnees desirer du neuronne
	*/
	void set_output(int _output);

	Neuron* prochain_neuron;
	Neuron* precedent_neuron;

	Weight_source* link_source;
	Weight* main_source;

	double i;        //valeur activation
	double a;        //valeur sortie activation
	double delta;    //valeur sortie activation
	double seuil;    //b ou theta dans les equations
	double d;		 //sortie desirer
	
private:
	
	int etage;

	int link_count;  //nbr d'entree sur ce neurone
	int main_count;  //nbr de sortie sur ce neurone
};

#endif