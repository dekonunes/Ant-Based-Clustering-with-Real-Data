/*
 * ant.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <math.h>
using namespace std;

struct item {
	double number1;
	double number2;
	double number3;
	double number4;
	double classe;
	double number1Past;
	double number2Past;
	double number3Past;
	double number4Past;
	double classePast;
};

struct formiga {
	struct item item;
	int i; //local da formiga em i
	int j; //local da formiga em j
	int raio;
	float tamVisao;
};

void viewAnt(vector<vector<item> >, formiga *, int, int);
void probabilityGetItem(vector<vector<item> > *, formiga *, double);
void probabilityDropItem(vector<vector<item> > *, formiga *, double);
void motionAnt(vector<vector<item> > *, formiga *, int, int);
double euclideanDistance(item, item, int);

#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_ */
