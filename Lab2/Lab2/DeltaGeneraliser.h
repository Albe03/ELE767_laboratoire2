#include <math.h>
#include "Network.h"
#include "layer.h"

/*#pragma once
class DeltaGeneraliser
{
};*/

int FonctionChoisie;



/**
* @brief UNIQUEMENT COUCHE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'entée et du poids et de la valeur de l'unité (neurone)
* @param entree liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unité (neurone)
* Attention à ce que (sizeof(entree) == sizeof(poids))
*/
double calcul_activation_neurone_couche1(Weight_source* link, double theta, Network Net);

/**
* @brief UNIQUEMENT AUTRE COUCHE QUE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'entée et du poids et de la valeur de l'unité (neurone)
* @param a liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unité (neurone)
*/
double calcul_activation_neurone_autre_couche(Weight_source* link, double theta);

/**
* @brief sortie de la fonction d'activation en fonction de la valeur du signal d'activation pour
* tel ou tel neurone (unité) (calculé avec les fonctions activation_couche1 et activation_autre_couche).
* Cette fonction calcul utilise la fonction sigmoide.
* @param v_activation valeur du signal d'activation (calculé avec les fonctions activation_couche1 et activation_autre_couche)
*/
double calcul_sortie_activation(double v_activation);

/**
* @brief UNIQUEMENT DERNIERE COUCHE : Cette fonction vient calculé le signal d'erreur pour la dernière couche.
* C'est là que commence l'opération du delta généralisé (et sur a fonction voisine calcul_signal_erreur_autre_couche)
* @param sortie_desirer valeur de la sortie désirée
* .........
*/
double calcul_signal_erreur_derniere_couche(double sortie_desirer, double v_sortie_activation, double v_activation);

/**
* .........
*/
double calcul_signal_erreur_autre_couche(double sortie_desirer, Neuron* current_neuron, double v_activation);

/**
* calcul du facteur de correction (delta) et de la mise à jour des valeurs des poids (poids + delta)
* .........
*/
double calcul_correction_poids(double taux, double entree_ou_a, double v_signal_erreur, double poids_actuel);