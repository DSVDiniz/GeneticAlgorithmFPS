#ifndef INPUTOUTPUT_H_
    #define INPUTOUTPUT_H_
#include "defines.h"
#include "draw.h"

#include <string.h>
#include <fstream>

namespace io
{
	void WriteMap(Matriz m, string arq);
	void WriteGenoma(vector<vector<int> >pop, string arq);
	void WriteGenBackup(vector<int>fitness,vector<vector<int> >pop, string arq);
	vector<int> ReadFitness(string arq);
	vector<vector<int> > ReadGenoma(string arq);
}


#endif /*INPUTOUTPUT_H_*/
