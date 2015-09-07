/*
 * main-priv.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_MAIN_PRIV_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_MAIN_PRIV_HPP_

using namespace std;

typedef struct item {
	double number1;
	double number2;
	double number3;
	double number4;
	double classe;
	double temp;
} item, *pitem;

struct formiga {
	pitem item; //0 não contem item, 1 contem item
	int i; //local da formiga em i
	int j; //local da formiga em j
	int raio;
	float tamVisao;
};



#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_MAIN_PRIV_HPP_ */
