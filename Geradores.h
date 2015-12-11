#ifndef GERADORES_H_
    #define GERADORES_H_

#include "point.h"
#include "defines.h"
#include "InputOutput.h"
#include "Genetica.h"
#include "draw.h"

namespace Geradores
{
    vector<vector<int> > IniPop(int tipo,int num_pop);
	void FirstPop(Matriz mapa, int num_pop, int opcao, int tipo_gerador);
	void NextPop(Matriz mapa, vector<vector<int> > genoma, vector<int> fitness, int opcao, int tipo_gerador);
	void GenomaToFile(Matriz mapa,char * arq, int opcao);
	int GenerateMap(Matriz m,vector<int> genoma,int opcao,int tipo);

	vector<Point<int> > Grid(Matriz m,vector<int> genoma);
	vector<Point<int> > Allwhite(Matriz m,vector<int> genoma);
	vector<Point<int> > Allblack(Matriz m,vector<int>genoma);
	vector<Point<int> > Digger(Matriz m,vector<int>genoma);
	vector<Point<int> > Teste(Matriz m,vector<int>genoma);
	vector<Point<int> > Teste2(Matriz m,vector<int>genoma);
	vector<Point<int> > Teste3(Matriz m,vector<int>genoma);
	vector<Point<int> > Testesemsala(Matriz m,vector<int>genoma);
	void ContinueRun(Matriz mapa, vector<vector<int> > genoma,int geracao,int opcao,int tipo_gerador);
}
#endif /*GRID_H_*/


