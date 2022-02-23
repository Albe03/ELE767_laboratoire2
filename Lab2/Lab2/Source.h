#pragma once
#ifndef SOURCE_H
#define SOURCE_H



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Affichage.h"
#include "Network.h"
#include <time.h> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <clocale>
#include <iomanip> 


#define MIN_VALUE 0.45
#define BUFFER_SIZE 400
#define MAX_LINE 60
#define COLUM_STATIC 12
#define DATA_TRAIN_SAMPLE 1340

void pretraiment_basedonnees(int _num_ligne_user, const char* source_database, const char* destination_database);

double** parser_basedonnees(const char* source_database, int nombre_line);

#endif