/*
 * graphicInterface.hpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */

#ifndef SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_
#define SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_

#include "main-priv.hpp"
#include "ant.hpp"
#include <SFML/Graphics.hpp>
#define resolucao 640
using namespace std;

void interfaceGrafica(vector<vector<item> > *, vector<formiga> *, int, int, int, int);
void update(vector<vector<item> > *, vector<formiga> *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *);
void updateFinal(vector<vector<item> > *, formiga *, int, int, int, sf::RenderWindow *, std::vector<std::vector<sf::RectangleShape> > *);
void updateColor(vector<vector<item> > *, formiga *, int, int, int, std::vector<std::vector<sf::RectangleShape> > *);


#endif /* SRC_ANT_BASED_CLUSTERING_WITH_REAL_DATA_GRAPHICINTERFACE_HPP_ */
