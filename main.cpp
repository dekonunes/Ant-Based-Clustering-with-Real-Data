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
	createGrid(&matriz, tamMatrizI, tamMatrizJ);
	populateItemsGrid(&matriz, tamMatrizI, tamMatrizJ);
	populateAnts(&matriz, &formigas, qtdFormigas, raio, tamMatrizI, tamMatrizJ);
	//movimentoDasFormigas(&matriz, &formigas.at(0), qtdFormigas, tamMatrizI,tamMatrizJ);
	for (int var = 0; var < qtdLoop; ++var) {
		for (int var2 = 0; var2 < qtdFormigas; ++var2) {
			motionAnt(&matriz, &formigas.at(var2), qtdFormigas, tamMatrizI, tamMatrizJ);
			usleep(TEMPO);
			//getchar();
			if (system("CLS"))
				system("clear");
			//cout << "-------------------------------" << endl;
			showGrid(&matriz, tamMatrizI, tamMatrizJ);
		}
	}
	//interfaceGrafica(&matriz, &formigas, qtdFormigas, tamMatrizI, tamMatrizJ, qtdLoop);
	//usleep(80000000);
	showGrid(&matriz, tamMatrizI, tamMatrizJ);
	return 0;
}
