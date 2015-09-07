/*
 * main.h
 *
 *  Created on: 20 de ago de 2015
 *      Author: udesc
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#define TEMPO 200000
#define resolucao 640
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

void povoarItensMatriz(vector<vector<item> > *, int, int);
void povoarFormigas(vector<vector<item> > *, vector<formiga> *, int, int, int, int);
void mostrarMatriz(vector<vector<item> > *, int, int);
void montarMatriz(vector<vector<item> > *, int, int);
void movimentoDasFormigas(vector<vector<item> > *, formiga *, int, int, int);
float visibilidadeItem(vector<vector<int> >, formiga, int, int);
void probabilidadeItens(vector<vector<item> > *, formiga, int);
void mostrarMatrizLimpa(vector<vector<item> > *, int, int);
void movimentoFinal(vector<vector<item> > *,formiga *, int, int, int);
void interfaceGrafica(vector<vector<item> > *, vector<formiga> *, int, int, int, int);
void update(vector<vector<item> > *, vector<formiga> *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *);
void updateFinal(vector<vector<item> > *, formiga *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *);
void updateColor(vector<vector<item> > *, formiga *, int, int, int, std::vector<std::vector<sf::RectangleShape> > *, int);

#endif /* MAIN_H_ */
