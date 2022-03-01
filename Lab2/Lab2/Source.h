#pragma once
#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <string.h>
#include <fstream>
#include <sstream>
#include <clocale>
#include <iomanip> 
#include "Weight.h"

#define MIN_VALUE 0.45
#define BUFFER_SIZE 400
#define MAX_LINE 60
#define COLUM_STATIC 12
#define DATA_TRAIN_SAMPLE 1340

typedef struct {
	double x;
	Weight_source* link_source;
}Input;

void pretraiment_basedonnees(int _num_ligne_user, const char* source_database, const char* destination_database);

Input** parser_basedonnees(const char* source_database, int nombre_line, char* data_piger);

#endif