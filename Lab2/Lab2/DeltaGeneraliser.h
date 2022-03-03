
/*#pragma once
class DeltaGeneraliser
{
};*/


/**
* @brief UNIQUEMENT COUCHE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'entée et du poids et de la valeur de l'unité (neurone)
* @param entree liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unité (neurone)
*/
int calcul_activation_couche1(int entree[], int poids[], int theta);

/**
* @brief UNIQUEMENT AUTRE COUCHE QUE 1 : cette fonction veut calculer la valeur du signal d'activation de chaque neurone en fonction
* de l'entée et du poids et de la valeur de l'unité (neurone)
* @param a liste des entrees jusqu'au neurone
* @param poids listes des poids jusqu'au neurone
* @param theta valeur de l'unité (neurone)
*/
int calcul_activation_autre_couche(int a[], int poids[], int theta);

/**
* @brief sortie de la fonction d'activation en fonction de la valeur du signal d'activation pour
* tel ou tel neurone (unité) (calculé avec les fonctions activation_couche1 et activation_autre_couche).
* Cette fonction calcul utilise la fonction sigmoide.
* @param v_activation valeur du signal d'activation (calculé avec les fonctions activation_couche1 et activation_autre_couche)
*/
int calcul_sortie_activation(int v_activation);

/**
* @brief UNIQUEMENT DERNIERE COUCHE : Cette fonction vient calculé le signal d'erreur pour la dernière couche.
* C'est là que commence l'opération du delta généralisé (et sur a fonction voisine calcul_signal_erreur_autre_couche)
* @param sortie_desirer valeur de la sortie désirée
* .........
*/
int calcul_signal_erreur_derniere_couche(int sortie_desirer, int v_sortie_activation, int v_activation);

/**
* .........
*/
int calcul_signal_erreur_autre_couche(int sortie_desirer);

/**
* calcul du facteur de correction (delta) et de la mise à jour des valeurs des poids (poids + delta)
* .........
*/
int calcul_correction_poids(int taux, int entree_ou_a, int v_signal_erreur);