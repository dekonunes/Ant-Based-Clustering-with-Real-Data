/*
 * ant.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_

#include "main-priv.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

float viewAnt(vector<vector<item> >, formiga, int, int);
void probabilityGetItem(vector<vector<item> > *, formiga, int);
void probabilityDropItem(vector<vector<item> > *, formiga, int);
void lastMotionAnt(vector<vector<item> > *, formiga *, int, int, int);
void motionAnt(vector<vector<item> > *, formiga *, int, int, int);
double euclideanDistance(item, formiga, int);

#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_ANT_HPP_ */
