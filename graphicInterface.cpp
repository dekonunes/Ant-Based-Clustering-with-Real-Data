/*
 * graphicInterface.cpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */
#include "graphicInterface.hpp"

void interfaceGrafica(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int tamMatrizI,
		int tamMatrizJ, int qtdLoop) {
	bool flag;
	sf::RenderWindow *window;
	std::vector<std::vector<sf::RectangleShape> > grid;
	window = new sf::RenderWindow(sf::VideoMode(resolucao, resolucao), "Ant-Clustering!");
	window->setPosition(sf::Vector2i(700 / 2, 50));

	for (int i = 0; i < tamMatrizI; ++i) {
		vector<sf::RectangleShape> row;
		for (int j = 0; j < tamMatrizJ; ++j) {
			row.push_back(sf::RectangleShape(sf::Vector2f((resolucao / tamMatrizI), (resolucao / tamMatrizI))));
			row[j].setOutlineThickness(2);
			row[j].setOutlineColor(sf::Color(0, 0, 0));
			row[j].setPosition(i * (resolucao / tamMatrizI), j * (resolucao / tamMatrizI));

			flag = false;
			if (!flag) {
				if (matriz->at(i).at(j).classe == 0)
					row[j].setFillColor(sf::Color(sf::Color::White)); // espaço livre
				else
					row[j].setFillColor(sf::Color(sf::Color(128, 128, 128))); // item
			}
		}
		grid.push_back(row);
	}

	for (int i = 0; i < qtdLoop; ++i) {

		update(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ, window, &grid);
		//if (i == 1)
		//usleep(10000000);
	}
	/*for (int i = 0; i < qtdFormigas; i++) {
	 if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 6) {
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = 0;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number1 = 0;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number2 = 0;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number3 = 0;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number4 = 0;
	 }
	 if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 7) {
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = matriz->at(formigas->at(i).i).at(
	 formigas->at(i).j).classePast;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number1 = matriz->at(formigas->at(i).i).at(
	 formigas->at(i).j).number1Past;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number2 = matriz->at(formigas->at(i).i).at(
	 formigas->at(i).j).number2Past;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number3 = matriz->at(formigas->at(i).i).at(
	 formigas->at(i).j).number3Past;
	 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number4 = matriz->at(formigas->at(i).i).at(
	 formigas->at(i).j).number4Past;
	 }
	 }*/
	updateFinal(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ, window, &grid); //para não deixar nenhuma formiga carregando quando termina

}

void update(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ,
		sf::RenderWindow *window, std::vector<std::vector<sf::RectangleShape> > *grid) {
	for (int i = 0; i < qtdFormigas; i++) {
		motionAnt(matriz, &formigas->at(i), tamMatrizI, tamMatrizJ);
		//updateColor(matriz, tamMatrizI, tamMatrizJ, grid);
	}
	/*
	for (int i = 0; i < tamMatrizI; i++)
		for (int j = 0; j < tamMatrizJ; j++)
			window->draw(grid->at(i).at(j));
	window->display();*/
}

void updateFinal(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int tamMatrizI,
		int tamMatrizJ, sf::RenderWindow *window, std::vector<std::vector<sf::RectangleShape> > *grid) {
	/*for (int i = 0; i < qtdFormigas; i++) {
		while (formigas->at(i).item.classe != 0) {
			//cout << "formig" << formigas->at(i).item.classe << endl;
			//cout << "map" << matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe << endl;
			motionAnt(matriz, &formigas->at(i), tamMatrizI, tamMatrizJ);

		}
		if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 6) {
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = 0;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number1 = 0;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number2 = 0;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number3 = 0;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number4 = 0;
		 }
		 if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 7) {
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = matriz->at(formigas->at(i).i).at(
		 formigas->at(i).j).classePast;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number1 = matriz->at(formigas->at(i).i).at(
		 formigas->at(i).j).number1Past;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number2 = matriz->at(formigas->at(i).i).at(
		 formigas->at(i).j).number2Past;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number3 = matriz->at(formigas->at(i).i).at(
		 formigas->at(i).j).number3Past;
		 matriz->at(formigas->at(i).i).at(formigas->at(i).j).number4 = matriz->at(formigas->at(i).i).at(
		 formigas->at(i).j).number4Past;
		 }

	}*/
	updateColor(matriz, tamMatrizI, tamMatrizJ, grid);
	for (int i = 0; i < tamMatrizI; i++)
		for (int j = 0; j < tamMatrizJ; j++)
			window->draw(grid->at(i).at(j));
	window->display();

}

void updateColor(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ,
		std::vector<std::vector<sf::RectangleShape> > *grid) {
	bool flag;
	for (int i = 0; i < tamMatrizI; i++) {
		for (int j = 0; j < tamMatrizJ; j++) {
			flag = false;
			if ((matriz->at(i).at(j).classe == 6)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Red)); // formiga sem item
			} else if ((matriz->at(i).at(j).classe == 8)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Black)); // formiga com item
			} else if ((matriz->at(i).at(j).classe == 7)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Green));
			} else if ((matriz->at(i).at(j).classe == 9)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Yellow));
			} else if ((matriz->at(i).at(j).classe == 1)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Magenta));
			} else if ((matriz->at(i).at(j).classe == 2)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Cyan));
			} else if ((matriz->at(i).at(j).classe == 3)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color(0, 0, 155)));
			} else if ((matriz->at(i).at(j).classe == 4)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color(0, 155, 0)));
			}
			if (!flag) {
				if (matriz->at(i).at(j).classe == 0)
					grid->at(i).at(j).setFillColor(sf::Color(sf::Color::White));
				else
					grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Blue)); //item
			}
		}
	}
}

