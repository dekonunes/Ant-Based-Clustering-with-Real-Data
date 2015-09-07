#include "main.hpp"

int main(int argc, char *argv[]) {
	if (argc < 5) {
		cout
				<< "Digite os parametros: 1º Linhas Matriz 2º Colunas Matriz 3º Qtd Formigas 4º Qtd Itens 5º Qtd iterações 6º Variação do raio de cada formiga"
				<< endl << "Exemplo: ./ant 40 40 10 500000 1" << endl;
		exit(0);
	}
	//int tamMatrizI = 40, tamMatrizJ = 40, qtdFormigas = 100, qtdItens = 250, qtdLoop = 1000000, raio = 1;
	int qtdLoop;
	int tamMatrizI = atoi(argv[1]), tamMatrizJ = atoi(argv[2]), qtdFormigas = atoi(argv[3]), raio = atoi(argv[5]);
	qtdLoop = atoi(argv[4]);
	//0 em branco, 1,2,3 e 4 item, 6 formiga sem item em baixo, 7 formiga e item (solto), 8 formiga e item (segurando) nada em baixo, 9 formiga e item (segurando) item em baixo
	srand(time(NULL));
	vector<vector<item> > matriz;
	vector<formiga> formigas;
	montarMatriz(&matriz, tamMatrizI, tamMatrizJ);
	povoarItensMatriz(&matriz, tamMatrizI, tamMatrizJ);
	povoarFormigas(&matriz, &formigas, qtdFormigas, raio, tamMatrizI, tamMatrizJ);
	//movimentoDasFormigas(&matriz, &formigas.at(0), qtdFormigas, tamMatrizI,tamMatrizJ);
	
	for (int var = 0; var < qtdLoop; ++var) {
		for (int var2 = 0; var2 < qtdFormigas; ++var2) {
			movimentoDasFormigas(&matriz, &formigas.at(var2), qtdFormigas, tamMatrizI, tamMatrizJ);
			usleep(TEMPO);
			//getchar();
			if (system("CLS"))
				system("clear");
			//cout << "-------------------------------" << endl;
			mostrarMatriz(&matriz, tamMatrizI, tamMatrizJ);
		}
	}
	//interfaceGrafica(&matriz, &formigas, qtdFormigas, tamMatrizI, tamMatrizJ, qtdLoop);
	//usleep(80000000);
	mostrarMatriz(&matriz, tamMatrizI, tamMatrizJ);
	return 0;
}

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
	for (int i = 0; i < qtdFormigas; i++) {
		if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 6)
			matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = 0;
		if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 7)
			matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = formigas->at(i).item->classe;
	}
	for (int i = 0; i < qtdFormigas; i++) {
		while (formigas->at(i).item->classe == 1) {
			updateFinal(matriz, &formigas->at(i), qtdFormigas, tamMatrizI, tamMatrizJ, window, &grid); //para não deixar nenhuma formiga carregando quando termina
		}
		if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 6)
			matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = 0;
		if (matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe == 7)
			matriz->at(formigas->at(i).i).at(formigas->at(i).j).classe = formigas->at(i).item->classe;
	}
}

void updateFinal(vector<vector<item> > *matriz, formiga *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ,
		sf::RenderWindow *window, std::vector<std::vector<sf::RectangleShape> > *grid) {
	movimentoFinal(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ);
	updateColor(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ, grid, 1);
	for (int i = 0; i < tamMatrizI; i++)
		for (int j = 0; j < tamMatrizJ; j++)
			window->draw(grid->at(i).at(j));
	window->display();
}

void update(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ,
		sf::RenderWindow *window, std::vector<std::vector<sf::RectangleShape> > *grid) {
	for (int i = 0; i < qtdFormigas; i++) {
		movimentoDasFormigas(matriz, &formigas->at(i), qtdFormigas, tamMatrizI, tamMatrizJ);
		updateColor(matriz, &formigas->at(i), qtdFormigas, tamMatrizI, tamMatrizJ, grid, 0);
	}

	for (int i = 0; i < tamMatrizI; i++)
		for (int j = 0; j < tamMatrizJ; j++)
			window->draw(grid->at(i).at(j));
	window->display();
}

void updateColor(vector<vector<item> > *matriz, formiga *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ,
		std::vector<std::vector<sf::RectangleShape> > *grid, int cor) {
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
			} else if ((matriz->at(i).at(j).classe == 2)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Magenta));
			} else if ((matriz->at(i).at(j).classe == 3)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color::Cyan));
			} else if ((matriz->at(i).at(j).classe == 4)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color(0, 0, 1)));
			} else if ((matriz->at(i).at(j).classe == 5)) {
				flag = true;
				grid->at(i).at(j).setFillColor(sf::Color(sf::Color(1, 0, 0)));
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

void movimentoFinal(vector<vector<item> > *matriz, formiga *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ) {
	movimentoDasFormigas(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ);
}

void probabilidadeItens(vector<vector<item> > *matriz, formiga *formiga, int probabilidade) {
	int random = rand() % 100;
	if (formiga->item->classe > 1) {
		if (((random < probabilidade) && (matriz->at(formiga->i).at(formiga->j).classe == 7))) {
			matriz->at(formiga->i).at(formiga->j).classe = 6;
			formiga->item = 0;
		}
	} else if (formiga->item->classe == 0) {
		if ((random > probabilidade) && (matriz->at(formiga->i).at(formiga->j).classe == 6)) {
			formiga->item->classe = matriz->at(formiga->i).at(formiga->j).classe;
			matriz->at(formiga->i).at(formiga->j).classe = 7;
		}
	}
}

float visibilidadeItem(vector<vector<item> > *matriz, formiga *formiga, int tamMatrizI, int tamMatrizJ) {
	int iAux = 0, jAux = 0, linhasMatriz = 3, aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0, aux5 = 0;
	float qtdItensRedor = 0;
	formiga->tamVisao = 0; //quantidade de celular analizadas
	iAux = formiga->i - 1;
	jAux = formiga->j - 1;
	tamMatrizI--;
	tamMatrizJ--;
	for (int var2 = 1; var2 < formiga->raio + 1; var2++) {
		linhasMatriz = (var2 * 2 + 1);
		for (int var3 = 0; var3 < linhasMatriz; var3++) {
			if (iAux < 0) {
				iAux = (tamMatrizI - aux1);
				aux1++;
			}
			if (jAux < 0)
				jAux = (tamMatrizJ - (var2));
			if (jAux > tamMatrizJ)
				jAux = 0;
			if (matriz->at(iAux).at(jAux).classe == formiga->item->classe)
				qtdItensRedor++;
			formiga->tamVisao++;
			jAux++;
		}
		iAux = formiga->i - var2;
		jAux = formiga->j + var2;
		iAux++;
		for (int var4 = 0; var4 < linhasMatriz - 1; var4++) {
			if (iAux < 0) {
				iAux = (tamMatrizI - (aux2));
				aux2++;
			}
			if (iAux > tamMatrizI)
				iAux = 0;
			if (jAux > tamMatrizJ) {
				jAux = 0 + aux3;
				aux3++;
			}
			if (matriz->at(iAux).at(jAux).classe == formiga->item->classe)
				qtdItensRedor++;
			formiga->tamVisao++;
			iAux++;
		}
		iAux = formiga->i + var2;
		jAux = formiga->j + (var2 - 1);
		for (int var5 = 0; var5 < linhasMatriz - 1; var5++) {
			if (iAux > tamMatrizI) {
				iAux = 0 + aux4;
				aux4++;
			}
			if (jAux < 0)
				jAux = tamMatrizJ;
			if (jAux > tamMatrizJ)
				jAux = 0;
			if (matriz->at(iAux).at(jAux).classe == formiga->item->classe)
				qtdItensRedor++;
			formiga->tamVisao++;
			jAux--;
		}
		iAux = formiga->i + (var2 - 1);
		jAux = formiga->j - var2;
		for (int var6 = 0; var6 < linhasMatriz - 2; var6++) {
			if (iAux > tamMatrizI)
				iAux = 0;
			if (iAux < 0)
				iAux = tamMatrizI;
			if (jAux < 0) {
				jAux = tamMatrizJ - aux5;
				aux5++;
			}
			if (matriz->at(iAux).at(jAux).classe == formiga->item->classe)
				qtdItensRedor++;
			formiga->tamVisao++;
			iAux--;
		}
		jAux = formiga->j - 2;
		iAux = formiga->i - 1;
		iAux--;
	}
	return ((qtdItensRedor / (qtdItensRedor + formiga->tamVisao))
			* (qtdItensRedor / (qtdItensRedor + formiga->tamVisao)));
}

void montarMatriz(vector<vector<item> > *matriz, int tamI, int tamJ) {
	item itemAux;
	itemAux.number1 = 0;
	itemAux.number2 = 0;
	itemAux.number3 = 0;
	itemAux.number4 = 0;
	itemAux.classe = 0;
	for (int i = 0; i < tamI; ++i) {
		vector<item> row;
		for (int j = 0; j < tamJ; ++j) {
			row.push_back(itemAux);
		}
		matriz->push_back(row);
	}
}

void mostrarMatriz(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ) {
	for (int i = 0; i < tamMatrizI; ++i) {
		for (int j = 0; j < tamMatrizJ; ++j) {
			if (matriz->at(i).at(j).classe == 1) {
				cout << "\033[1;34m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 2) {
				cout << "\033[1;31m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 3) {
				cout << "\033[1;32m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 4) {
				cout << "\033[1;33m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 5) {
				cout << "\033[1;35m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 6) {
				cout << "\033[1;36m" << matriz->at(i).at(j).classe << "\033[0m";
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

void mostrarMatrizLimpa(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ) {
	for (int i = 0; i < tamMatrizI; ++i) {
		for (int j = 0; j < tamMatrizJ; ++j) {
			if (matriz->at(i).at(j).classe == 1) {
				cout << "\033[1;34m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 2) {
				cout << "\033[1;31m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 3) {
				cout << "\033[1;32m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 4) {
				cout << "\033[1;33m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 8) {
				cout << "\033[1;38m" << matriz->at(i).at(j).classe << "\033[0m";
			} else if (matriz->at(i).at(j).classe == 9) {
				cout << "\033[1;39m" << matriz->at(i).at(j).classe << "\033[0m";
			} else {
				//cout << matriz->at(i).at(j);
				cout << " ";
			}
		}
		cout << endl;
	}
}

void povoarFormigas(vector<vector<item> > *matriz, vector<formiga> *formigas, int qtdFormigas, int raio, int tamMatrizI,
		int tamMatrizJ) {
	formiga formigaAux;
	for (int var = 0; var < qtdFormigas; ++var) {
		formigaAux.i = rand() % tamMatrizI;
		formigaAux.j = rand() % tamMatrizJ;
		formigaAux.item->number1 = 0;
		formigaAux.item->number2 = 0;
		formigaAux.item->number3 = 0;
		formigaAux.item->number4 = 0;
		formigaAux.item->classe = 0;
		//formigaAux.raio = (rand() % raio) + 1;
		formigaAux.raio = raio;
		if (matriz->at(formigaAux.i).at(formigaAux.j).classe == 0) {
			matriz->at(formigaAux.i).at(formigaAux.j).classe = 6;
			formigas->push_back(formigaAux);
		} else if ((matriz->at(formigaAux.i).at(formigaAux.j).classe >= 1)
				&& (matriz->at(formigaAux.i).at(formigaAux.j).classe < 6)) {
			matriz->at(formigaAux.i).at(formigaAux.j).classe = 7;
			formigas->push_back(formigaAux);
		} else if (matriz->at(formigaAux.i).at(formigaAux.j).classe <= 6)
			var--;

	}
}

void povoarItensMatriz(vector<vector<item> > *matriz, int tamMatrizI, int tamMatrizJ) {
	int i, j, lines = 0, linesAux = 0, dimension = -1, flag = 0;
	double aux;
	vector<vector<double> > itens;
	char c;
	FILE *file = fopen("Square1_DataSet_400itens.txt", "r");
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
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(1);
				break;
				case 3:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(1);
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(2);
				break;
				case 4:
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(0);
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(1);
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(2);
				matriz->at(i).at(j).number1 = itens.at(linesAux).at(3);
				break;
				default:
				break;
			}
			matriz->at(i).at(j).classe = itens.at(linesAux).at(dimension);
			linesAux++;

		} else if (matriz->at(i).at(j).classe == 1) {
			var--;
		} else if (matriz->at(i).at(j).classe == 2) {
			var--;
		} else if (matriz->at(i).at(j).classe == 3) {
			var--;
		} else if (matriz->at(i).at(j).classe == 4) {
			var--;
		}
	}
	fclose(file);
}

void movimentoDasFormigas(vector<vector<item> > *matriz, formiga *formiga, int qtdFormigas, int tamMatrizI,
		int tamMatrizJ) {
	int iAux = formiga->i, jAux = formiga->j,direcao, probInteiro;
	float probFloat;
	//probFloat = visibilidadeItem(matriz, formiga, tamMatrizI, tamMatrizJ) * 100;
	probInteiro = ceil(probFloat);
	//probabilidadeItens(matriz, formiga, probInteiro);
	tamMatrizI--;
	tamMatrizJ--;
	direcao = rand() % 8;
	direcao = 7;
	//cout << "==" << direcao << endl;
	switch (direcao) {
	case 0:
		//movimento para superior esquerdo
		if (formiga->i == 0)
			iAux = tamMatrizI +1;
		if (formiga->j == 0)
			jAux = tamMatrizJ +1;
		iAux--;
		jAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 1:
		//movimento para cima
		if (formiga->i == 0)
			iAux = tamMatrizI+1;
		iAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		break;
	case 2:
		//movimento para superior direito
		if (formiga->i == 0)
			iAux = tamMatrizI +1;
		if (formiga->j == tamMatrizJ)
			jAux = -1;
		iAux--;
		jAux++;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 3:
		//movimento para esquerda
		if (formiga->j == 0)
			jAux = tamMatrizJ+1;
		jAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->j = jAux;
		break;
	case 4:
		//movimento para direita
		if (formiga->j == tamMatrizJ)
			jAux = - 1;
		jAux++;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->j = jAux;
		break;
	case 5:
		//movimento para inferior esquerdo
		if (formiga->i == tamMatrizI)
			iAux = -1;
		if (formiga->j == 0)
			jAux = tamMatrizJ+1;
		iAux++;
		jAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 6:
		//movimento para baixo
		if (formiga->i == tamMatrizI)
			iAux = -1;
		iAux++;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		break;
	case 7:
		//movimento para inferior direito
		if (formiga->i == tamMatrizI)
			iAux = -1;
		if (formiga->j == tamMatrizJ)
			jAux = -1;
		iAux++;
		jAux++;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1)&& (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item->classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).temp; //atualiza o lugar para sem formiga com 1 item
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	default:
		break;
	}
}

