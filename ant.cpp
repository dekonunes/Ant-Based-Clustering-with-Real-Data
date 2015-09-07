/*
 * ant.cpp
 *
 *  Created on: 7 de set de 2015
 *      Author: deko
 */
#include "ant.hpp"

float viewAnt(vector<vector<item> > *matriz, formiga *formiga, int tamMatrizI, int tamMatrizJ) {
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

double euclideanDistance(item item, formiga formiga, int dimension) {
	double aux = 0;
	switch (dimension) {
	case 1:
		return sqrt(pow(formiga.item->number1 - item.number1, 2));
		break;
	case 2:
		aux = pow(formiga.item->number1 - item.number1, 2);
		aux += pow(formiga.item->number2 -item.number2, 2);
		return sqrt(aux);
		break;
	case 3:
		aux = pow(formiga.item->number1 - item.number1, 2);
		aux += pow(formiga.item->number2 - item.number2, 2);
		aux += pow(formiga.item->number3 - item.number3, 2);
		return sqrt(aux);
		break;
	case 4:
		aux = pow(formiga.item->number1 - item.number1, 2);
		aux += pow(formiga.item->number2 - item.number2, 2);
		aux += pow(formiga.item->number3 - item.number3, 2);
		aux += pow(formiga.item->number4 - item.number4, 2);
		return sqrt(aux);
		break;
	default:
		return 0;
		break;
	}
}

void probabilityDropItem(vector<vector<item> > *matriz, formiga *formiga, int probabilidade) {
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

void probabilityGetItem(vector<vector<item> > *matriz, formiga *formiga, int probabilidade) {
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

void lastMotionAnt(vector<vector<item> > *matriz, formiga *formigas, int qtdFormigas, int tamMatrizI, int tamMatrizJ) {
	motionAnt(matriz, formigas, qtdFormigas, tamMatrizI, tamMatrizJ);
}

void motionAnt(vector<vector<item> > *matriz, formiga *formiga, int qtdFormigas, int tamMatrizI, int tamMatrizJ) {
	int iAux = formiga->i, jAux = formiga->j, direcao, probInteiro;
	float probFloat;
	//probFloat = visibilidadeItem(matriz, formiga, tamMatrizI, tamMatrizJ) * 100;
	//probInteiro = ceil(probFloat);
	//probabilidadeItens(matriz, formiga, probInteiro);
	tamMatrizI--;
	tamMatrizJ--;
	direcao = rand() % 8;
	switch (direcao) {
	case 0:
		//movimento para superior esquerdo
		if (formiga->i == 0)
			iAux = tamMatrizI + 1;
		if (formiga->j == 0)
			jAux = tamMatrizJ + 1;
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
			iAux = tamMatrizI + 1;
		iAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
			iAux = tamMatrizI + 1;
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
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
			jAux = tamMatrizJ + 1;
		jAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
			jAux = -1;
		jAux++;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
			jAux = tamMatrizJ + 1;
		iAux++;
		jAux--;
		matriz->at(iAux).at(jAux).temp = matriz->at(iAux).at(jAux).classe;
		if (matriz->at(iAux).at(jAux).classe >= 6)
			break;
		if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe > 1)) {
			//atualizar o movimento da formiga segurando item e item em baixo
			matriz->at(iAux).at(jAux).classe = 9;
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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
		} else if ((matriz->at(iAux).at(jAux).classe >= 1) && (formiga->item->classe == 0)) {
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

