/*
 * graphicInterface.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_

#include "ant.hpp"
#include <SFML/Graphics.hpp>
#define resolucao 800
using namespace std;

void interfaceGrafica(vector<vector<item> > *, vector<formiga> *, int, int, int, int, normalDim );
void update(vector<vector<item> > *, vector<formiga> *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *, normalDim );
void updateFinal(vector<vector<item> > *, vector<formiga> *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *, normalDim );
void updateColor(vector<vector<item> > *, int, int, std::vector<std::vector<sf::RectangleShape> > *);


#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_ */
