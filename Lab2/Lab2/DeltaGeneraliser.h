#include <math.h>
#include "Network.h"
#include "layer.h"
#include "Source.h"
#include <string.h>
#include <iostream>

/*#pragma once
class DeltaGeneraliser
{
};*/


/**
* @brief UNIQUEMENT COUCHE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'ent�e et du poids et de la valeur de l'unit� (neurone)
* @param entree liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unit� (neurone)
* Attention � ce que (sizeof(entree) == sizeof(poids))
*/
double calcul_activation_neurone_couche1(Weight_source* link, double theta);

/**
* @brief UNIQUEMENT AUTRE COUCHE QUE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'ent�e et du poids et de la valeur de l'unit� (neurone)
* @param a liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unit� (neurone)
*/
double calcul_activation_neurone_autre_couche(Neuron* current_neuron);

/**
* @brief sortie de la fonction d'activation en fonction de la valeur du signal d'activation pour
* tel ou tel neurone (unit�) (calcul� avec les fonctions activation_couche1 et activation_autre_couche).
* Cette fonction calcul utilise la fonction sigmoide.
* @param v_activation valeur du signal d'activation (calcul� avec les fonctions activation_couche1 et activation_autre_couche)
*/
double calcul_sortie_activation(double v_activation, int option);

/**
* @brief UNIQUEMENT DERNIERE COUCHE : Cette fonction vient calcul� le signal d'erreur pour la derni�re couche.
* C'est l� que commence l'op�ration du delta g�n�ralis� (et sur a fonction voisine calcul_signal_erreur_autre_couche)
* @param sortie_desirer valeur de la sortie d�sir�e
* ......... 
*/
double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation, int option);

/**
* .........
*/
double calcul_signal_erreur_autre_couche(Neuron* current_neuron, int option);

/**
* calcul du facteur de correction (delta) et de la mise � jour des valeurs des poids (poids + delta)
* .........
*/
double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel);

void calcul_delta_generaliser(Network* Net, int option);

void test();