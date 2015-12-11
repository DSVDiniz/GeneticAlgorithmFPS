#ifndef DRAW_H_
	#define DRAW_H_

#include "defines.h"
#include "point.h"

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

typedef int Matriz [TAMX][TAMY];

namespace Draw
{
	int Rngi(int max, int min);
	bool Prob(double p);
    void Insert(Matriz m ,int x, int y, int t);
    void Insert(Matriz m ,Point<int> p);
    void SimpSqrFill(Matriz m, Point<int> xy, Point<int> wh);
    void SimpSqrFill(Matriz m,int tipo, int xi, int xf, int yi, int yf);
    void Linha(Matriz m,Point<int> ini,Point<int> fim);
    void Linha(Matriz m,int tipo,int ix,int fx,int iy,int fy);
    void LinhaGorda(Matriz m,Point<int> ini,Point<int> fim,Point<int> li,Point<int> ls, int radius);
    void LinhaGorda(Matriz m,int tipo,int ix,int iy,int fx,int fy,int lix,int liy,int lsx,int lsy);
    void Fill_4(Matriz m, int fill_paint, int filled,int x, int y,vector<Point<int> > *coord);
    void InitMapa(Matriz m, bool type);
    int AchaArea(Matriz m_orig, int opcao);
    void RemoveBordasExiladas(Matriz m, vector<Point<int> >posicoes_bordas);
    void AdicionaItensESpawn(Matriz m,float porcentagem);
    vector<Point<int> > RemoveImpassavel(Matriz m);
}

#endif /*DRAW_H_*/
