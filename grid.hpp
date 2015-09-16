/*
 * grid.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_

#include "ant.hpp"
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

struct item;
struct formiga;

struct normalDim {
	double normal;
	int dimension;
};

void createGrid(vector<vector<item> > *, int, int);
void showGrid(vector<vector<item> > *, int, int);
void populateAnts(vector<vector<item> > *, vector<formiga> *, int, int, int, int);
void populateItemsGrid(vector<vector<item> > *, int, int, normalDim *);
void populateAnts2(vector<formiga> *formigas, int qtdFormigas);
double normaliza(vector<vector<double> > *,int, int);

#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_ */
