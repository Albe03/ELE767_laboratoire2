#pragma once
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Scroll.H>

#define NB_COUCHES_CACHEES_MAX 5

class Affichage : public Fl_Window {

public:
	Affichage(int w, int h, const char* title);
	~Affichage();
	Fl_Window* winNouvelleConfig;
	Fl_Window* winCoucheCachee;
	Fl_Button* okBtn;
	Fl_Button* okBtn2;
	Fl_Button* quitBtn;
	Fl_Round_Button* RadioBtnSig;
	Fl_Round_Button* RadioBtnTan;
	Fl_Round_Button* RadioBtnOldVals;
	Fl_Round_Button* RadioBtnNewVals;
	Fl_Round_Button* RadioBtnSets40;
	Fl_Round_Button* RadioBtnSets50;
	Fl_Round_Button* RadioBtnSets60;
	Fl_Value_Input* Entree;
	Fl_Value_Input* Cachee;
	Fl_Value_Input* Sortie;
	Fl_Value_Input* TauxApprentissage;
	Fl_Value_Input* TempsLimite;
	Fl_Value_Input* PerformanceVoulue;
	Fl_Input* DataTrain;
	Fl_Input* DataVC;
	Fl_Input* DataTest;
	Fl_Input* FichierSortie;
	Fl_Value_Input* CoucheCachee1;
	Fl_Value_Input* CoucheCachee2;
	Fl_Value_Input* CoucheCachee3;
	Fl_Value_Input* CoucheCachee4;
	Fl_Value_Input* CoucheCachee5;

	// Choix de donnees d'apprentissages
	// 0 = Anciennes donnees, 1 = nouvelles donnees
	int valDonneesApprentissage;
	// Nombre de couches
	int valEntree;
	int valCachee;
	// Nombre de neuronnes pour couche sortie
	int valSortie;
	// Nombre de neuronnes des couches cachees
	int valCouchesCachees[NB_COUCHES_CACHEES_MAX] = {};
	// 0 pour Sigmoide et 1 pour Tanh
	int valFctAct;
	// Couches cachees + une seule couche de sortie
	int CouchesTotales;
	// 40, 50 ou 60 sets de donnees
	int nombreSets;
	// Taux d'apprentissage (ex 0.1)
	double valTauxApprentissage;
	// Temps limite d'apprentissage en secondes
	int valTempsLimite;
	// Performance désirée pour arrêter l'apprentissage
	int valPerformanceVoulue;

	// Path pour les fichiers de données
	std::string valDataTrain;
	std::string valDataVC;
	std::string valDataTest;
	std::string valFichierSortie;

	int flag = 0;
private:
	static void cb_NewConfig(Fl_Widget*, void*);
	inline void cb_NewConfig_i();

	static void cb_OldConfig(Fl_Widget*, void*);
	inline void cb_OldConfig_i();

	static void cb_okBtn(Fl_Widget*, void*);
	inline void cb_okBtn_i();

	static void cb_okBtn2(Fl_Widget*, void*);
	inline void cb_okBtn2_i();

	static void cb_quit(Fl_Widget*, void*);
	inline void cb_quit_i();
};


class DonneesConfig {
public :
	// Nombre de couches
	int valEntree;
	int valCachee;
	// Nombre de neuronnes pour couche sortie
	int valSortie;
	// Nombre de neuronnes des couches cachees
	int valCouchesCachees[NB_COUCHES_CACHEES_MAX] = {};
	// 0 pour Sigmoide et 1 pour Sinus
	int valFctAct;
	// Couches cachees + une seule couche de sortie
	int CouchesTotales;
	// 40, 50 ou 60 sets de donnees
	int nombreSets;
	// Taux d'apprentissage (ex 0.1)
	double valTauxApprentissage;
	// Temps limite d'apprentissage en secondes
	int valTempsLimite;
	// Performance désirée pour arrêter l'apprentissage
	int valPerformanceVoulue;

	// Path pour les fichiers de données
	std::string valDataTrain;
	std::string valDataVC;
	std::string valDataTest;
	std::string valFichierSortie;
};


void DemarrerAffichage(DonneesConfig *mesDonnees);
void Afficher_Resultats(double tabResVC[], double tabResTest[], double tabResApprentissage[], int nbEpoques);