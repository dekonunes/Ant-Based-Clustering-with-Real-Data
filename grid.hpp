/*
 * grid.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_

#include "main-priv.hpp"
#include <vector>
#include <iostream>
using namespace std;
void createGrid(vector<vector<item> > *, int, int);
void showGrid(vector<vector<item> > *, int, int);
void showGridClean(vector<vector<item> > *, int, int);
void populateAnts(vector<vector<item> > *, vector<formiga> *, int, int, int, int);
void populateItemsGrid(vector<vector<item> > *, int, int);


#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRID_HPP_ */
