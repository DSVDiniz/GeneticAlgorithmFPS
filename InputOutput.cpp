#include "InputOutput.h"

namespace io
{
	void WriteMap(Matriz m, string arq)
	{
		ofstream file;
		file.open(arq.c_str(),ios::out | ios::trunc);
		char caracteres1[] = {',','1','.','s','3','4','5','6','7','#','#','#'};

		if(file.is_open())
		{
			for(unsigned int j=0;j<TAMY;j++)
			{
				for(unsigned int i=0;i<TAMX;i++)
				{
					file<<caracteres1[m[i][j]];
				}
				file<<"\n";
			}
		}
		file.close();
	}

	void WriteGenoma(vector<vector<int> >pop, string arq)
	{
		ofstream file;
		file.open(arq.c_str(),ios::out | ios::trunc);

		if(file.is_open())
		{
			for(unsigned int i=0;i<pop.size();++i)
			{
				for(unsigned int j=0;j<pop[0].size();++j)
				{
					file<<pop[i][j]<<' ';
				}
				file<<"\n";
			}
		}
		file.close();
	}

	void WriteGenBackup(vector<int>fitness,vector<vector<int> >pop, string arq)
	{
		ofstream file;
		file.open(arq.c_str(),ios::out | ios::trunc);
		int maior =0;
		int index=0;

		if(file.is_open())
		{
			for(unsigned int i=0;i<fitness.size();++i)
				if(fitness[i]>maior)
				{
					maior = fitness[i];
					index = i;
				}
			file<<"BEST: "<<maior<<"\t MAP: "<<index<<"\n\n";
			for(unsigned int i=0;i<fitness.size();++i)
			{
				file<<"MAP: "<<i<<"\tF: "<<fitness[i]<<endl;
				file<<"G: ";
				for(unsigned int j=0;j<pop[0].size();++j)
				{
					file<<pop[i][j]<<' ';
				}
				file<<"\n\n";
			}
		}
		file.close();
	}

	vector<int> ReadFitness(string arq)
	{
		vector<int>fitness;
		ifstream file;
		string linha;
		int freecells=0, timetofight=0;
		int i=1;

		file.open(arq.c_str(),ios::in);

		if((file.is_open())&&(file.good()))//tudo ok?
		{
			while ( getline (file,linha) )
			{
                if(i%2==0)
                {
                    freecells=atoi(linha.c_str());
                    fitness.push_back(timetofight+freecells);
                }
                else
                    timetofight=atoi(linha.c_str());
                i++;
			}
		}
		else
			cout<<"Erro: arquivo "<<arq<<" nao existe"<<endl;

		file.close();
		return fitness;
	}

	vector<vector<int> > ReadGenoma(string arq)
	{
		vector<vector<int> >genoma;
		ifstream file;
		string linha,num;

		file.open(arq.c_str(),ios::in);

		if((file.is_open())&&(file.good()))//tudo ok?
		{
			int pop=0;
			while ( getline (file,linha) )
				pop++;

			file.clear();
			file.seekg(0,ios::beg);

			int k=0;
			genoma.resize(pop);
			while ( getline (file,linha) )
			{
				for(unsigned int i=0;i<linha.length();++i)
				{
					if(linha[i]!=' ')
						num.push_back(linha[i]);
					else
					{
						genoma[k].push_back(atoi(num.c_str()));
						num="";
					}
				}
				k++;
			}
		}
		else
			cout<<"Erro: arquivo "<<arq<<" nao existe"<<endl;

		file.close();
		return genoma;
	}
}
