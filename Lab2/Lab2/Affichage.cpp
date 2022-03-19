#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include "Affichage.h"
#include "Fichier.h"

using namespace std;

// Exemple tiré de http://arkiletian.com/fltk-tutorial/
Affichage::Affichage(int w, int h, const char* title) :Fl_Window(w, h, title) {

	// Prend les valeurs du fichier de config
	LireFichierConfig(&nombreSets, &valEntree, &valCachee, &valSortie, &valFctAct, valCouchesCachees, &valTauxApprentissage, &valTempsLimite, &valPerformanceVoulue,
		&valDataTrain, &valDataVC, &valDataTest, &valFichierSortie);

	begin();
	// Boutons radio
	RadioBtnOldVals = new Fl_Round_Button(0, 0, 300, 40, "Utiliser anciennes donnees d'apprentissage");
	RadioBtnNewVals = new Fl_Round_Button(0, 50, 300, 40, "Utiliser nouvelles donnees d'apprentissage");
	RadioBtnOldVals->type(FL_RADIO_BUTTON);
	RadioBtnNewVals->type(FL_RADIO_BUTTON);

	// Boutons config
	Fl_Button* but1 = new Fl_Button(0, 100, 120, 40, "Nouvelle config");
	Fl_Button* but2 = new Fl_Button(150, 100, 120, 40, "Ancienne config");

	// Boutons appels fonctions pour nouvelles ou ancienne configuration
	but1->callback(cb_NewConfig, this);
	but2->callback(cb_OldConfig, this);

	// Bouton appel fonction pour quitter
	quitBtn = new Fl_Button(100, 150, 70, 30, "Quit");
	quitBtn->callback(cb_quit, this);


	end();
	resizable(this);
	show();
}

//----------------------------------------------------

Affichage::~Affichage() {}

//----------------------------------------------------

void Affichage::cb_NewConfig(Fl_Widget* o, void* v) {

	((Affichage*)v)->cb_NewConfig_i();
}


void Affichage::cb_NewConfig_i() {

	char *tempChar;

	// Prend valeurs de la derniere fenetre
	if (RadioBtnOldVals->value() == 1)
		valDonneesApprentissage = 0;
	else if (RadioBtnNewVals->value() == 1)
		valDonneesApprentissage = 1;

	// Crée nouvelle fenêtre
	winNouvelleConfig = new Fl_Window(500, 650, "Nouvelle configuration");
	winNouvelleConfig->begin();

	// Boites de textes et boutons
	Entree = new Fl_Value_Input(250, 0, 140, 30, "Nombre d'unites dans couche d'entree:");
	Cachee = new Fl_Value_Input(250, 50, 140, 30, "Nombre de couches cachees (Max 5):");
	Sortie = new Fl_Value_Input(250, 100, 140, 30, "Neuronnes dans la couche sortie:");
	RadioBtnSig = new Fl_Round_Button(150, 150, 80, 40, "Sigmoide");
	RadioBtnTan = new Fl_Round_Button(250, 150, 80, 40, "Tanh");
	RadioBtnSig->type(FL_RADIO_BUTTON);
	RadioBtnTan->type(FL_RADIO_BUTTON);


	RadioBtnSets40 = new Fl_Round_Button(100, 200, 80, 40, "40 sets");
	RadioBtnSets50 = new Fl_Round_Button(200, 200, 80, 40, "50 sets");
	RadioBtnSets60 = new Fl_Round_Button(300, 200, 80, 40, "60 sets");

	TauxApprentissage = new Fl_Value_Input(250, 250, 140, 30, "Taux d'apprentissage :    ");
	TempsLimite = new Fl_Value_Input(250, 300, 140, 30,		  "Temp limite en secondes : ");
	PerformanceVoulue = new Fl_Value_Input(250, 350, 140, 30, "Performance voulue en % : ");

	

	// Fichier
	DataTrain = new Fl_Input(260, 400, 200, 30, "Emplacement du fichier donnees train : ");
	DataVC = new Fl_Input(260, 450, 200, 30,    "Emplacement du fichier donnees VC :    ");
	DataTest = new Fl_Input(260, 500, 200, 30,  "Emplacement du fichier donnees test :  ");
	FichierSortie = new Fl_Input(260, 550, 200, 30, "Emplacement du fichier de sortie : ");

	// Prend les valeurs du fichier config et les mets dans le GUI
	Entree->value(valEntree);
	Cachee->value(valCachee);
	Sortie->value(valSortie);

	TauxApprentissage->value(valTauxApprentissage);
	TempsLimite->value(valTempsLimite);
	PerformanceVoulue->value(valPerformanceVoulue);

	tempChar = &valDataTrain[0];
	DataTrain->insert(tempChar, 0);
	tempChar = &valDataVC[0];
	DataVC->insert(tempChar, 0);
	tempChar = &valDataTest[0];
	DataTest->insert(tempChar, 0);
	tempChar = &valFichierSortie[0];
	FichierSortie->insert(tempChar, 0);

	// Active le bon bouton radio avec les valeurs du fichier config
	if (valFctAct == 0) {
		RadioBtnSig->value(1);
	}
	else {
		RadioBtnTan->value(1);
	}

	if (nombreSets == 40) {
		RadioBtnSets40->value(1);
	}
	else if (nombreSets == 50) {
		RadioBtnSets50->value(1);
	}
	else if (nombreSets == 60) {
		RadioBtnSets60->value(1);
	}

	okBtn = new Fl_Button(200, 600, 70, 30, "Ok");
	okBtn->callback(cb_okBtn, this);

	end();
	winNouvelleConfig->show();
}



void Affichage::cb_OldConfig(Fl_Widget* o, void* v) {

	((Affichage*)v)->cb_OldConfig_i();
}


void Affichage::cb_OldConfig_i() {

	// Prend valeurs de la derniere fenetre
	if (RadioBtnOldVals->value() == 1)
		valDonneesApprentissage = 0;
	else if (RadioBtnNewVals->value() == 1)
		valDonneesApprentissage = 1;
	//FermerFichierConfig();
	hide();
}


//----------------------------------------------------
void Affichage::cb_okBtn(Fl_Widget*, void* v) {

	((Affichage*)v)->cb_okBtn_i();
}


void Affichage::cb_okBtn_i() {
	int val40, val50, val60;

	// Prend les valeurs entrees et les mets en memoire
	valEntree = (int)Entree->value();
	valCachee = (int)Cachee->value();
	valSortie = (int)Sortie->value();

	valTauxApprentissage = TauxApprentissage->value();
	valTempsLimite = (int)TempsLimite->value();
	valPerformanceVoulue = (int)PerformanceVoulue->value();

	valDataTrain = DataTrain->value();
	valDataVC = DataVC->value();
	valDataTest = DataTest->value();
	valFichierSortie = FichierSortie->value();

	// Bouton sigmoide activé
	if((int)RadioBtnSig->value() == 1)
		valFctAct = 0;
	// Bouton Tanh activé
	else if((int)RadioBtnTan->value() == 1)
		valFctAct = 1;

	if (valSortie != 10) {
		fl_alert("Attention, on doit utiliser 10 neuronnes de sortie pour les données du laboratoire 2!");
	}
	// Protection contre choix multiple de sets
	val40 = (int)RadioBtnSets40->value();
	val50 = (int)RadioBtnSets50->value();
	val60 = (int)RadioBtnSets60->value();

	if (val40 == 1 && val50 == 0 && val60 == 0)
	{
		nombreSets = 40;
		flag = 0;
	}
	else if (val40 == 0 && val50 == 1 && val60 == 0) {
		nombreSets = 50;
		flag = 0;
	}
	else if (val40 == 0 && val50 == 0 && val60 == 1) {
		nombreSets = 60;
		flag = 0;
	}
	else {
		fl_alert("SVP choisir un seul nombre de sets!");
		flag = 1;
	}
	// Cache la fenetre pour nouvelle config
	winNouvelleConfig->hide();
	// Crée une nouvelle fenêtre pour les couches cachées
	winCoucheCachee = new Fl_Window(400, 300, "Configuration couches cachees");
	winCoucheCachee->begin();

	// Pour le nombre de couche cachees choisi, on affiche les boites de texte
	if (valCachee > 0)
	{
		CoucheCachee1 = new Fl_Value_Input(250, 0, 140, 30, "Neuronnes dans couche cachee 1 :");
		CoucheCachee1->value(valCouchesCachees[0]);
	}
	if (valCachee > 1)
	{
		CoucheCachee2 = new Fl_Value_Input(250, 50, 140, 30, "Neuronnes dans couche cachee 2 :");
		CoucheCachee2->value(valCouchesCachees[1]);
	}
	if (valCachee > 2)
	{
		CoucheCachee3 = new Fl_Value_Input(250, 100, 140, 30, "Neuronnes dans couche cachee 3 :");
		CoucheCachee3->value(valCouchesCachees[2]);
	}
	if (valCachee > 3)
	{
		CoucheCachee4 = new Fl_Value_Input(250, 150, 140, 30, "Neuronnes dans couche cachee 4 :");
		CoucheCachee4->value(valCouchesCachees[3]);
	}
	if (valCachee > 4)
	{
		CoucheCachee5 = new Fl_Value_Input(250, 200, 140, 30, "Neuronnes dans couche cachee 5 :");
		CoucheCachee5->value(valCouchesCachees[4]);
	}

	okBtn2 = new Fl_Button(150, 250, 70, 30, "Ok");
	okBtn2->callback(cb_okBtn2, this);

	winCoucheCachee->end();
	winCoucheCachee->show();
}


void Affichage::cb_okBtn2(Fl_Widget*, void* v) {

	((Affichage*)v)->cb_okBtn2_i();
}


void Affichage::cb_okBtn2_i() {

	// Prend valeurs du GUI et les mets dans des variables
	if (valCachee > 0)
	{
		valCouchesCachees[0] = (int)CoucheCachee1->value();
	}
		
	if (valCachee > 1)
	{
		valCouchesCachees[1] = (int)CoucheCachee2->value();
	}
	if (valCachee > 2)
	{
		valCouchesCachees[2] = (int)CoucheCachee3->value();
	}
	if (valCachee > 3)
	{
		valCouchesCachees[3] = (int)CoucheCachee4->value();
	}
	if (valCachee > 4)
	{
		valCouchesCachees[4] = (int)CoucheCachee5->value();
	}
	winCoucheCachee->hide();

	if(flag != 1)
		hide();

	// Nombre de couches totales = couches cachées + la sortie
	CouchesTotales = valCachee + 1;

	// Mets les valeurs entrées dans le fichier de configuration
	CreerFichierConfig();
	EcrireFichierConfig(nombreSets, valEntree, valCachee, valSortie, valFctAct, valCouchesCachees, valTauxApprentissage, valTempsLimite,
		valPerformanceVoulue, valDataTrain, valDataVC, valDataTest, valFichierSortie);
}



void Affichage::cb_quit(Fl_Widget*, void* v) {

	((Affichage*)v)->cb_quit_i();
}


void Affichage::cb_quit_i() {

	hide();
}

void DemarrerAffichage(DonneesConfig* mesDonnees)
{
	// Copie les variables des données d'affichage dans un objet pour utilisation externe
	Affichage win(300, 200, "Lab2 ELE767");
	Fl::run();
	mesDonnees->valDonneesApprentissage = win.valDonneesApprentissage;
	mesDonnees->valEntree = win.valEntree;
	mesDonnees->valCachee = win.valCachee;
	mesDonnees->valSortie = win.valSortie;
	std::copy(std::begin(win.valCouchesCachees), std::end(win.valCouchesCachees), std::begin(mesDonnees->valCouchesCachees));
	mesDonnees->valFctAct = win.valFctAct;
	mesDonnees->CouchesTotales = win.CouchesTotales;
	mesDonnees->nombreSets = win.nombreSets;
	mesDonnees->valTauxApprentissage = win.valTauxApprentissage;
	mesDonnees->valTempsLimite = win.valTempsLimite;
	mesDonnees->valPerformanceVoulue = win.valPerformanceVoulue;
	mesDonnees->valDataTrain = win.valDataTrain;
	mesDonnees->valDataVC = win.valDataVC;
	mesDonnees->valDataTest = win.valDataTest;
	mesDonnees->valFichierSortie = win.valFichierSortie;
}

void Afficher_Resultats(double tabResVC[], double tabResTest[], double tabResApprentissage[], int nbEpoques) {
	Fl_Window* winRes;
	char tempChar[10];
	winRes = new Fl_Window(500, 500, "Resultats obtenus");
	winRes->begin();
	Fl_Multiline_Output* OutputMsg = new Fl_Multiline_Output(0, 0, 500, 500);


	// Affiche toutes les epoques et leurs valeurs de performances
	for (int i = 0; i < nbEpoques ; i++) {
		// Performance VC
		OutputMsg->insert("Performance de vc pour epoque ");
		_itoa(i+1, tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert("               : ");
		sprintf(tempChar, "%f", tabResVC[i]);
		//_itoa(tabResVC[i], tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert("\n");
		// Performance Test
		OutputMsg->insert("Performance de test pour epoque ");
		_itoa(i + 1, tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert("             : ");
		sprintf(tempChar, "%f", tabResTest[i]);
		//_itoa(tabResTest[i], tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert("\n");
		// Performance apprentissage
		OutputMsg->insert("Performance apprentissage pour epoque ");
		_itoa(i + 1, tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert(" : ");
		sprintf(tempChar, "%f", tabResApprentissage[i]);
		//_itoa(tabResApprentissage[i], tempChar, 10);
		OutputMsg->insert(tempChar);
		OutputMsg->insert("\n");
		OutputMsg->insert("\n");
	}

	OutputMsg->insert("\nPerformance atteinte VC : ");
	sprintf(tempChar, "%f", tabResVC[nbEpoques - 1]);
	//_itoa(tabResVC[nbEpoques-1], tempChar, 10);
	OutputMsg->insert(tempChar);
	OutputMsg->insert("\n");


	OutputMsg->insert("\n\nPerformance de test : ");
	sprintf(tempChar, "%f", tabResTest[nbEpoques-1]);
	OutputMsg->insert(tempChar);
	OutputMsg->insert("\n");

	OutputMsg->insert("\n\nPerformance apprentissage : ");
	sprintf(tempChar, "%f", tabResApprentissage[nbEpoques - 1]);
	OutputMsg->insert(tempChar);
	OutputMsg->insert("\n");

	OutputMsg->insert("\n");
	OutputMsg->insert("*** Vous pouvez parcourir toutes les valeurs avec les fleches du clavier***");
	OutputMsg->insert("\n");

	winRes->end();
	winRes->show();

	Fl::run();
}