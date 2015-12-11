#ifndef GENETICA_H_
    #define GENETICA_H_

#include "defines.h"
#include "draw.h"
#include <sstream>
#include <bitset>

namespace Genetica
{
	vector<int> IntToBin (unsigned int val);
	unsigned int BinToInt (vector <int> val);
	vector<vector<int> > Selection(vector<vector<int> >genoma,vector<int>fitness, int tipo);
	vector<vector<int> > Crossover(vector <int> pai_a,vector <int> pai_b, int tipo);
	int* Crossover(int* genoma, int tam,int tipo);
	vector <int>Mutation(vector <int>genoma,int tipo);
	int* Mutation(int* genoma, int tam,int tipo);
}


#endif /*GENETICA_H_*/

