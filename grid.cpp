#include "grid.hpp"

void createGrid(vector<vector<item> > *matriz, int tamI, int tamJ) {
	item itemAux;
	itemAux.number1 = 0;
	itemAux.number2 = 0;
	itemAux.number3 = 0;
	itemAux.number4 = 0;
	itemAux.number1Past = 0;
	itemAux.number2Past = 0;
	itemAux.number3Past = 0;
	itemAux.number4Past = 0;
	itemAux.classe = 0;
	itemAux.classePast = 0;
	for (int i = 0; i < tamI; ++i) {
		vector<item> row;
		for (int j = 0; j < tamJ; ++j) {
			row.push_back(itemAux);
		}
		matriz->push_back(row);
	}
}

void showGrid(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ) {
	for (int i = 0; i < tamMatrizI; ++i) {
		for (int j = 0; j < tamMatrizJ; ++j) {
			if (matriz->at(i).at(j).classe == 1) {
				cout << "\033[1;34m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 2) {
				cout << "\033[1;35m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 3) {
				cout << "\033[1;32m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 4) {
				cout << "\033[1;33m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 5) {
				cout << "\033[1;35m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 6) {
				cout << "\033[1;31m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 7) {
				cout << "\033[1;37m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 8) {
				cout << "\033[1;38m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 9) {
				cout << "\033[1;39m" << matriz->at(i).at(j).classe << "\033[0m";
			} else {
				//cout << matriz->at(i).at(j).classe;
				cout << " ";
			}
		}
		cout << endl;
	}
}

void populateAnts2(vector<formiga> *formigas, int qtdFormigas) {

}

void populateAnts(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int raio, int tamMatrizI,
		int tamMatrizJ) {
	formiga formiga;

	for (int var = 0; var < qtdFormigas; ++var) {
		formiga.i = rand() % tamMatrizI;
		formiga.j = rand() % tamMatrizJ;
		formiga.item.number1 = 0.0;
		formiga.item.number2 = 0.0;
		formiga.item.number3 = 0.0;
		formiga.item.number4 = 0.0;
		formiga.item.classe = 0;
		//formigaAux.raio = (rand() % raio) + 1;
		formiga.raio = raio;
		formiga.tamVisao = 0;
		if (matriz->at(formiga.i).at(formiga.j).classe == 0) {
			matriz->at(formiga.i).at(formiga.j).classe = 6;
			formigas->push_back(formiga);
		} else
			var--;
	}
}

void populateItemsGrid(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ) {
	int i, j, lines = 0, linesAux = 0, dimension = -1, flag = 0;
	double aux;
	vector<vector<double> > itens;
	char c;
	FILE *file = fopen("DataSet_150items_4Dime.txt", "r");
	if (file == NULL)
		exit(EXIT_FAILURE);

	while (c != '#') {
		c = ' ';
		vector<double> row;
		while (c != '\n') {
			fscanf(file, "%lf", &aux);
			row.push_back(aux);
			c = fgetc(file);
			if (!flag)
				dimension++;
			if (c == '#')
				break;
		}
		itens.push_back(row);
		flag = 1;
		lines++;
	}

	for (int var = 0; var < lines; ++var) {
		i = rand() % tamMatrizI;
		j = rand() % tamMatrizJ;
		if (matriz->at(i).at(j).classe == 0) {
			switch (dimension) {
			case 1:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				break;
			case 2:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				matriz->at(i).at(j).number2 = itens.at(linesAux).at(1);
				break;
			case 3:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				matriz->at(i).at(j).number2 = itens.at(linesAux).at(1);
				matriz->at(i).at(j).number3 = itens.at(linesAux).at(2);
				break;
			case 4:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				matriz->at(i).at(j).number2 = itens.at(linesAux).at(1);
				matriz->at(i).at(j).number3 = itens.at(linesAux).at(2);
				matriz->at(i).at(j).number4 = itens.at(linesAux).at(3);
				break;
			default:
				break;
			}
			matriz->at(i).at(j).classe = itens.at(linesAux).at(dimension);
			matriz->at(i).at(j).classePast = 0;
			matriz->at(i).at(j).number1Past = 0;
			matriz->at(i).at(j).number2Past = 0;
			matriz->at(i).at(j).number3Past = 0;
			matriz->at(i).at(j).number4Past = 0;
			linesAux++;
		} else if (matriz->at(i).at(j).classe <= 1)
			var--;

	}
	fclose(file);
}
