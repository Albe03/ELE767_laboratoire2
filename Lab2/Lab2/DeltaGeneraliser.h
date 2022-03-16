#pragma once

#ifndef DELTA_H
#define DELTA_H

#include <math.h>
#include "Network.h"
#include "layer.h"

/**
* @brief UNIQUEMENT COUCHE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'ent�e et du poids et de la valeur de l'unit� (neurone)
* @param link listes des poids en sortie jusqu'au neurone
* @param theta valeur de l'unit� (neurone)
* Attention � ce que (sizeof(entree) == sizeof(poids))
*/
double calcul_activation_neurone_couche1(Weight_source* link, double theta);

/**
* @brief UNIQUEMENT AUTRE COUCHE QUE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'ent�e et du poids et de la valeur de l'unit� (neurone)
* @param current_neuron le neuron quo'on traite en question
*/
double calcul_activation_neurone_autre_couche(Neuron* current_neuron);

/**
* @brief sortie de la fonction d'activation en fonction de la valeur du signal d'activation pour
* tel ou tel neurone (unit�) (calcul� avec les fonctions activation_couche1 et activation_autre_couche).
* Cette fonction calcul utilise la fonction sigmoide ou celle de sinus.
* @param v_activation valeur du signal d'activation (calcul� avec les fonctions activation_couche1 et activation_autre_couche)
* @param option c'est l'option pour changer entre la fonction du sigmoide ou sinus. C'est 0 pour sigmoide, sinon 1 pour le sinus
*/
double calcul_sortie_activation(double v_activation, int option);

/**
* @brief UNIQUEMENT DERNIERE COUCHE : Cette fonction vient calcul� le signal d'erreur pour la derni�re couche.
* C'est l� que commence l'op�ration du delta g�n�ralis� (et sur a fonction voisine calcul_signal_erreur_autre_couche)
* @param sortie_desirer valeur de la sortie d�sir�e
* @param v_sortie_activation c'est la sortie optenue. donc le a
* @param v_activation c'est le i de l'activation
* @param option c'est l'option pour changer entre la fonction du sigmoide ou sinus. C'est 0 pour sigmoide, sinon 1 pour le sinus
*/
double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation, int option);

/**
* @brief Cette fonction vient calcul� le signal d'erreur pour les autre couche.
* C'est l� que commence l'op�ration du delta g�n�ralis�
* @param current_neuron le neuron qu'on traite en question
* @param option c'est l'option pour changer entre la fonction du sigmoide ou sinus. C'est 0 pour sigmoide, sinon 1 pour le sinus
*/
double calcul_signal_erreur_autre_couche(Neuron* current_neuron, int option);

/**
* @brief Cette fonction fait le mis a jour des poids et il fait le calcul de facteur de correction (Phase3 et Phase 4)
* 
* @param taux le taux d'apprentisage
* @param entree_ou_a c'est la sortie optenue. donc le a ou d
* @param v_signal_erreur le signal d'erreur
* @param poids_actuel le poids actuelle 
*/
double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel);


/**
* @brief Cette fonction fait le calcule de la retropopagation  
*
* @param Net le reseaux de neuronne qu'on souhaite faire la retro
* @param option c'est l'option pour changer entre la fonction activation du sigmoide ou sinus. C'est 0 pour sigmoide, sinon 1 pour le sinus
*/
void calcul_retropopagation(Network* Net, int option);

#endif