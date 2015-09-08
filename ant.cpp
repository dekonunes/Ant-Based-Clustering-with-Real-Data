/*
 * ant.cpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */
#include "ant.hpp"

void viewAnt(vector<vector<item> > *matriz, formiga *formiga, int tamMatrizI, int tamMatrizJ) {
	int iAux = 0, jAux = 0, linhasMatriz = 3, aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0, aux5 = 0, k1, k2;
	double qtdItensRedor = 0, alpha = 2, distance, probability = 0.0;
	iAux = formiga->i - 1;
	jAux = formiga->j - 1;
	tamMatrizI--;
	tamMatrizJ--;
	distance = 1 / (formiga->raio * formiga->raio);
	//probability += 1 - (euclideanDistance(matriz->at(iAux).at(jAux), formiga, 1) / alpha);

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
			if (matriz->at(iAux).at(jAux).classe > 0) {
				probability += 1 - (euclideanDistance(matriz->at(iAux).at(jAux), formiga, 1) / alpha);
				qtdItensRedor++;
			}
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
			if (matriz->at(iAux).at(jAux).classe > 0) {
				probability += 1 - (euclideanDistance(matriz->at(iAux).at(jAux), formiga, 1) / alpha);
				qtdItensRedor++;
			}
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
			if (matriz->at(iAux).at(jAux).classe > 0) {
				probability += 1 - (euclideanDistance(matriz->at(iAux).at(jAux), formiga, 1) / alpha);
				qtdItensRedor++;
			}
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
			if (matriz->at(iAux).at(jAux).classe > 0) {
				probability += 1 - (euclideanDistance(matriz->at(iAux).at(jAux), formiga, 1) / alpha);
				qtdItensRedor++;
			}
			formiga->tamVisao++;
			iAux--;
		}
		jAux = formiga->j - 2;
		iAux = formiga->i - 1;
		iAux--;
	}

	probability = probability * -1;
	//cout << probability << endl;
	probability = distance * probability;
	if (formiga->item.classe >= 1) {
		k2 = qtdItensRedor;
		probability = (probability / (k2 + probability));
		probability = probability * probability;
		probabilityDropItem(matriz, formiga, probability);
	} else {
		k1 = (((2 * formiga->raio + 1) * (2 * formiga->raio + 1)) - 1) - qtdItensRedor;
		probability = (k1 / (k1 + probability));
		probability = probability * probability;
		probabilityGetItem(matriz, formiga, probability);

	}
	//return ((qtdItensRedor / (qtdItensRedor + formiga.tamVisao)) * (qtdItensRedor / (qtdItensRedor + formiga.tamVisao)));
}

void probabilityGetItem(vector<vector<item> > *matriz, formiga *formiga, double probability) {
	int random = rand() % 100;
	//cout << "get" << probability << endl;
	probability = probability * 100;
	//cout << "get" << probability << endl;
	if (((random < probability) && (matriz->at(formiga->i).at(formiga->j).classe == 7))) {
		//cout << probability << endl;
		//formiga->item.classe = matriz->at(formiga->i).at(formiga->j).temp;
		//cout << "t:" << formiga->item.classe << endl;
		formiga->item.classe = matriz->at(formiga->i).at(formiga->j).classePast;
		formiga->item.number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
		formiga->item.number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
		formiga->item.number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
		formiga->item.number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		matriz->at(formiga->i).at(formiga->j).classe = 8; //update matriz without item
		matriz->at(formiga->i).at(formiga->j).number1 = 0;
		matriz->at(formiga->i).at(formiga->j).number2 = 0;
		matriz->at(formiga->i).at(formiga->j).number3 = 0;
		matriz->at(formiga->i).at(formiga->j).number4 = 0;
		matriz->at(formiga->i).at(formiga->j).classePast = 0;
	}

}

void probabilityDropItem(vector<vector<item> > *matriz, formiga *formiga, double probability) {
	int random = rand() % 100;
	probability = probability * 100;
	//probability = 100;
	//cout << "drop" << probability << endl;
	if (((random < probability) && (matriz->at(formiga->i).at(formiga->j).classe == 8))) {
		matriz->at(formiga->i).at(formiga->j).classe = formiga->item.classe;
		matriz->at(formiga->i).at(formiga->j).number1 = formiga->item.number1;
		matriz->at(formiga->i).at(formiga->j).number2 = formiga->item.number2;
		matriz->at(formiga->i).at(formiga->j).number3 = formiga->item.number3;
		matriz->at(formiga->i).at(formiga->j).number4 = formiga->item.number4;
		formiga->item.classe = 0;
		formiga->item.number1 = 0;
		formiga->item.number2 = 0;
		formiga->item.number3 = 0;
		formiga->item.number4 = 0;
	}
}

double euclideanDistance(item item, formiga *ant, int dimension) {
	double aux = 0;
	switch (dimension) {
	case 1:
		return sqrt(pow(ant->item.number1 - item.number1, 2));
		break;
	case 2:
		aux = pow(ant->item.number1 - item.number1, 2);
		aux += pow(ant->item.number2 - item.number2, 2);
		return sqrt(aux);
		break;
	case 3:
		aux = pow(ant->item.number1 - item.number1, 2);
		aux += pow(ant->item.number2 - item.number2, 2);
		aux += pow(ant->item.number3 - item.number3, 2);
		return sqrt(aux);
		break;
	case 4:
		aux = pow(ant->item.number1 - item.number1, 2);
		aux += pow(ant->item.number2 - item.number2, 2);
		aux += pow(ant->item.number3 - item.number3, 2);
		aux += pow(ant->item.number4 - item.number4, 2);
		return sqrt(aux);
		break;
	default:
		return 0;
		break;
	}
}

void motionAnt(vector<vector<item> > *matriz, formiga *formiga, int tamMatrizI, int tamMatrizJ) {
	int iAux = formiga->i, jAux = formiga->j, direcao;
	if ((matriz->at(formiga->i).at(formiga->j).classe == 7) || (matriz->at(formiga->i).at(formiga->j).classe == 8))
		viewAnt(matriz, formiga, tamMatrizI, tamMatrizJ);
	tamMatrizI--;
	tamMatrizJ--;
	direcao = rand() % 8;
	//direcao = 1;
	switch (direcao) {
	case 0:
		//movimento para superior esquerdo
		if (formiga->i == 0)
			iAux = tamMatrizI + 1;
		if (formiga->j == 0)
			jAux = tamMatrizJ + 1;
		iAux--;
		jAux--;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;

		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 1:
		//movimento para cima
		if (formiga->i == 0)
			iAux = tamMatrizI + 1;
		iAux--;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;

		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->i = iAux;
		break;
	case 2:
		//movimento para superior direito
		if (formiga->i == 0)
			iAux = tamMatrizI + 1;
		if (formiga->j == tamMatrizJ)
			jAux = -1;
		iAux--;
		jAux++;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 3:
		//movimento para esquerda
		if (formiga->j == 0)
			jAux = tamMatrizJ + 1;
		jAux--;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->j = jAux;
		break;
	case 4:
		//movimento para direita
		if (formiga->j == tamMatrizJ)
			jAux = -1;
		jAux++;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->j = jAux;
		break;
	case 5:
		//movimento para inferior esquerdo
		if (formiga->i == tamMatrizI)
			iAux = -1;
		if (formiga->j == 0)
			jAux = tamMatrizJ + 1;
		iAux++;
		jAux--;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	case 6:
		//movimento para baixo
		if (formiga->i == tamMatrizI)
			iAux = -1;
		iAux++;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
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
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		matriz->at(iAux).at(jAux).classePast = matriz->at(iAux).at(jAux).classe;
		matriz->at(iAux).at(jAux).number1Past = matriz->at(iAux).at(jAux).number1;
		matriz->at(iAux).at(jAux).number2Past = matriz->at(iAux).at(jAux).number2;
		matriz->at(iAux).at(jAux).number3Past = matriz->at(iAux).at(jAux).number3;
		matriz->at(iAux).at(jAux).number4Past = matriz->at(iAux).at(jAux).number4;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e item em baixo
			matriz->at(iAux).at(jAux).classe = 7;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe >= 1)) {
			//atualizar o movimento da formiga segurando item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 8;
		} else if ((matriz->at(iAux).at(jAux).classe == 0) && (formiga->item.classe == 0)) {
			//atualizar o movimento da formiga SEM item e SEM item em baixo
			matriz->at(iAux).at(jAux).classe = 6;
		}
		if ((matriz->at(formiga->i).at(formiga->j).classe == 9)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 7)) {
			matriz->at(formiga->i).at(formiga->j).classe = matriz->at(formiga->i).at(formiga->j).classePast;
			matriz->at(formiga->i).at(formiga->j).number1 = matriz->at(formiga->i).at(formiga->j).number1Past;
			matriz->at(formiga->i).at(formiga->j).number2 = matriz->at(formiga->i).at(formiga->j).number2Past;
			matriz->at(formiga->i).at(formiga->j).number3 = matriz->at(formiga->i).at(formiga->j).number3Past;
			matriz->at(formiga->i).at(formiga->j).number4 = matriz->at(formiga->i).at(formiga->j).number4Past;
		} else if ((matriz->at(formiga->i).at(formiga->j).classe == 6)
				|| (matriz->at(formiga->i).at(formiga->j).classe == 8)) {
			matriz->at(formiga->i).at(formiga->j).classe = 0; //atualiza o lugar para sem formiga e sem item
			matriz->at(formiga->i).at(formiga->j).number1 = 0;
			matriz->at(formiga->i).at(formiga->j).number2 = 0;
			matriz->at(formiga->i).at(formiga->j).number3 = 0;
			matriz->at(formiga->i).at(formiga->j).number4 = 0;
		}
		formiga->i = iAux;
		formiga->j = jAux;
		break;
	default:
		break;
	}
}

