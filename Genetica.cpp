#include "Genetica.h"

namespace Genetica
{
	vector<int> IntToBin (unsigned int val)
	{
		unsigned int mask = 1 << (sizeof(int) * 8 - 1);
		vector<int> bin;
		for(unsigned int i = 0; i < sizeof(int) * 8; i++)
		{
			if( (val & mask) == 0 )
				bin.push_back(0);
			else
				bin.push_back(1);

			mask  >>= 1;
		}
		bin.erase(bin.begin(),bin.begin()+26);
		return bin;
	}

	unsigned int BinToInt (vector <int> val)
	{
		stringstream str;

		for(unsigned int i=0;i<val.size();++i)
			str<<val[i];


		bitset<6>  x(str.str());
		return x.to_ulong();
	}

	inline int Torneio(vector<int>fitness, int index1, int index2)
	{
		if(fitness[index1]>fitness[index2])
			return index1;
		else if(fitness[index1]<fitness[index2])
			return index2;
		else
			return index1;
	}

	vector<vector<int> > Selection(vector<vector<int> >genoma,vector<int>fitness, int tipo)
	{
		vector<vector<int> >filhos, pop_nova;
		int aux = (fitness.size()-1)/2;
		for(unsigned int i=0;i<fitness.size()/2;++i)
		{
			int vencedor1 = Torneio(fitness,Draw::Rngi(aux,0),Draw::Rngi(aux,0));
			int vencedor2 = Torneio(fitness,Draw::Rngi(aux,0),Draw::Rngi(aux,0));
			filhos = Crossover(genoma[vencedor1],genoma[vencedor2],tipo);
			pop_nova.push_back(filhos[0]);
			pop_nova.push_back(filhos[1]);
		}
		return pop_nova;
	}


	vector<vector<int> > Crossover(vector <int> pai_a,vector <int> pai_b, int tipo)
	{
		int tam = pai_a.size();

		vector<vector<int> > resultado;
		vector<int> filho_a, filho_b;

		filho_a.resize(tam);
		filho_b.resize(tam);

		if(Draw::Prob(CROSS_RATE))//se houver cruzamento
		{
			int ponto = Draw::Rngi(tam-1,0);
			for(int i=0; i<ponto;++i)
			{
				filho_a[i]=pai_a[i];
				filho_b[i]=pai_b[i];
			}
			for(int i=ponto; i<tam;++i)
			{
				filho_a[i]=pai_b[i];
				filho_b[i]=pai_a[i];
			}
		}
		else//se nao houver cruzamento
		{
			filho_a = pai_a;
			filho_b = pai_b;
		}

		//mutacao
		filho_a = Mutation(filho_a,tipo);
		filho_b = Mutation(filho_b,tipo);

		resultado.push_back(filho_a);
		resultado.push_back(filho_b);
		return resultado;
	}

	vector <int> Mutation(vector <int> genoma, int tipo)
	{
		/*cout<<"A: ";
		for(int j=0;j<genoma.size();++j)
		{
			cout<<genoma[j]<<" ";
			if((j+1)%6==0)
				cout<<endl;
		}
		cout<<endl;*/
		if(tipo==G_GRID)
		{
			double p = (double)1/(double)genoma.size();
			for(unsigned int i=0; i<genoma.size();++i)
			{
				if(Draw::Prob(p))
				{
					if(Draw::Prob(0.5))
						genoma[i]-=1;
					else
						genoma[i]+=1;

					if(genoma[i]<0)
						genoma[i]=3;
					if(genoma[i]>3)
						genoma[i]=0;
				}
			}
		}
		else if(tipo==G_ALLWHITE)//<x,y,tam>, max int(63,63,-+63), bin size(6,6,6+1)
		{
			double p = (double)1/((double)genoma.size()*(6+6+7));
			int aux=0;
			bool negativo =false;
			vector<int> alelo;
			for(unsigned int i=0; i<genoma.size();++i)
			{
				if((i+1)%3==0)//caso do alelo tam
				{
					if(genoma[i]>0)
						alelo = IntToBin(genoma[i]);
					else
					{
						alelo = IntToBin(-genoma[i]);
						negativo = true;
					}
				}
				else
					alelo = IntToBin(genoma[i]);

				for(int j=0; j<6;++j)
				{
					if(Draw::Prob(p))
					{
						if(alelo[j]==0)
							alelo[j]=1;
						else
							alelo[j]=0;
					}
				}
				aux = BinToInt(alelo);

				if(negativo)//caso do alelo tam
				{
					aux=-aux;
					negativo =false;
				}

				if((i+1)%3==0)//caso do alelo tam
					if(Draw::Prob(p))
						aux= -aux;

				genoma[i] = aux;
			}
		}
		else if(tipo==G_ALLBLACK)//<x,y,tam>, max int(63,63,-+31), bin size(6,6,5+1)
		{
			double p = (double)1/((double)genoma.size()*(6+6+6));
			int aux=0;
			bool negativo =false;
			vector<int> alelo;
			for(unsigned int i=0; i<genoma.size();++i)
			{
				if((i+1)%3==0)//caso do alelo tam
				{
					if(genoma[i]>0)
						alelo = IntToBin(genoma[i]);
					else
					{
						alelo = IntToBin(-genoma[i]);
						negativo = true;
					}

					for(int j=1; j<6;++j)//trabalhando com cadeias de tamanho 5 (int max = 31)
					{
						if(Draw::Prob(p))
						{
							if(alelo[j]==0)
								alelo[j]=1;
							else
								alelo[j]=0;
						}
					}
					aux = BinToInt(alelo);

					if(negativo)
					{
						aux=-aux;
						negativo =false;
					}

					if(Draw::Prob(p))
						aux= -aux;
				}
				else//caso dos alelos x,y
				{
					alelo = IntToBin(genoma[i]);
					for(int j=0; j<6;++j)//trabalhando com cadeias de tamanho 6 (int max = 63)
					{
						if(Draw::Prob(p))
						{
							if(alelo[j]==0)
								alelo[j]=1;
							else
								alelo[j]=0;
						}
					}
					aux = BinToInt(alelo);
				}
				genoma[i] = aux;
			}
		}
		else if(tipo==G_DIGGER)
		{

		}
		else if(tipo==G_SC1)//<x,y,s,a,b,c> , max int(63,63,31,NUM_ARENAS,NUM_ARENAS,NUM_ARENAS), bin size(6,6,5+1,bsize_arenas*3)
		{
			//double p = (double)1/((double)genoma.size()*(6+6+6+4+4+4));
			double p = (double)1/((double)genoma.size());
			int aux=0;
			int index=0;
			vector<int> alelo0,alelo1,alelo2,alelo3,alelo4,alelo5;
			for( unsigned int i=0; i<genoma.size();i+=6)
			{
				alelo0 = IntToBin(genoma[i]);
				alelo1 = IntToBin(genoma[i+1]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo0[index]==0)
						alelo0[index]=1;
					else
						alelo0[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo1[index]==0)
						alelo1[index]=1;
					else
						alelo1[index]=0;
				}
				aux = BinToInt(alelo0);
				genoma[i]=aux;
				aux = BinToInt(alelo1);
				genoma[i+1]=aux;
				//------------------------------------------------------------------------------
				alelo2 = IntToBin(genoma[i+2]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(4,1);
					if(alelo2[index]==0)
						alelo2[index]=1;
					else
						alelo2[index]=0;
				}
				aux = BinToInt(alelo2);
				genoma[i+2]=aux;
				//------------------------------------------------------------------------------
				alelo3 = IntToBin(genoma[i+3]);
				alelo4 = IntToBin(genoma[i+4]);
				alelo5 = IntToBin(genoma[i+5]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo3[index]==0)
						alelo3[index]=1;
					else
						alelo3[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo4[index]==0)
						alelo4[index]=1;
					else
						alelo4[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo5[index]==0)
						alelo5[index]=1;
					else
						alelo5[index]=0;
				}
				aux = BinToInt(alelo3);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+3]=aux;
				aux = BinToInt(alelo4);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+4]=aux;
				aux = BinToInt(alelo5);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+5]=aux;
			}
		}
		else if(tipo==G_SC2)//<x,y,s,a,b,c> , max int(63,63,-+31,NUM_ARENAS,NUM_ARENAS,NUM_ARENAS), bin size(6,6,5+1,bsize_arenas*3)
		{
			//double p = (double)1/((double)genoma.size()*(6+6+6+4+4+4));
			double p = (double)1/((double)genoma.size());
			int aux=0;
			int index=0;
			bool negativo =false;
			vector<int> alelo0,alelo1,alelo2,alelo3,alelo4,alelo5;
			for(unsigned int i=0; i<genoma.size();i+=6)
			{
				alelo0 = IntToBin(genoma[i]);
				alelo1 = IntToBin(genoma[i+1]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo0[index]==0)
						alelo0[index]=1;
					else
						alelo0[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo1[index]==0)
						alelo1[index]=1;
					else
						alelo1[index]=0;
				}
				aux = BinToInt(alelo0);
				genoma[i]=aux;
				aux = BinToInt(alelo1);
				genoma[i+1]=aux;
				//------------------------------------------------------------------------------
				if(genoma[i+2]<0)
				{
					negativo=true;
					alelo2 = IntToBin(-genoma[i+2]);
				}
				else
					alelo2 = IntToBin(genoma[i+2]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(4,1);
					if(alelo2[index]==0)
						alelo2[index]=1;
					else
						alelo2[index]=0;
				}
				aux = BinToInt(alelo2);
				if(negativo)
				{
					aux=-aux;
					negativo=false;
				}
				if(Draw::Prob((double)1/((double)genoma.size()*(6+6+6+4+4+4))))
					aux=-aux;
				genoma[i+2]=aux;
				//------------------------------------------------------------------------------
				alelo3 = IntToBin(genoma[i+3]);
				alelo4 = IntToBin(genoma[i+4]);
				alelo5 = IntToBin(genoma[i+5]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo3[index]==0)
						alelo3[index]=1;
					else
						alelo3[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo4[index]==0)
						alelo4[index]=1;
					else
						alelo4[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo5[index]==0)
						alelo5[index]=1;
					else
						alelo5[index]=0;
				}
				aux = BinToInt(alelo3);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+3]=aux;
				aux = BinToInt(alelo4);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+4]=aux;
				aux = BinToInt(alelo5);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+5]=aux;

			}
		}
		else if(tipo==G_SC3)//<x,y,s,a,b,c> , max int(63,63,-+31,NUM_ARENAS,NUM_ARENAS,NUM_ARENAS), bin size(6,6,5+1,bsize_arenas*3)
		{
			//double p = (double)1/((double)genoma.size()*(6+6+6+4+4+4));
			double p = (double)1/((double)genoma.size());
			int aux=0;
			int index=0;
			bool negativo =false;
			vector<int> alelo0,alelo1,alelo2,alelo3,alelo4,alelo5;
			for(unsigned int i=0; i<genoma.size();i+=6)
			{
				alelo0 = IntToBin(genoma[i]);
				alelo1 = IntToBin(genoma[i+1]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo0[index]==0)
						alelo0[index]=1;
					else
						alelo0[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo1[index]==0)
						alelo1[index]=1;
					else
						alelo1[index]=0;
				}
				aux = BinToInt(alelo0);
				genoma[i]=aux;
				aux = BinToInt(alelo1);
				genoma[i+1]=aux;
				//------------------------------------------------------------------------------
				if(genoma[i+2]<0)
				{
					negativo=true;
					alelo2 = IntToBin(-genoma[i+2]);
				}
				else
					alelo2 = IntToBin(genoma[i+2]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(3,1);
					if(alelo2[index]==0)
						alelo2[index]=1;
					else
						alelo2[index]=0;
				}
				aux = BinToInt(alelo2);
				if(negativo)
				{
					aux=-aux;
					negativo=false;
				}
				if(Draw::Prob((double)1/((double)genoma.size()*(6+6+6+4+4+4))))
					aux=-aux;
				genoma[i+2]=aux;
				//------------------------------------------------------------------------------
				alelo3 = IntToBin(genoma[i+3]);
				alelo4 = IntToBin(genoma[i+4]);
				alelo5 = IntToBin(genoma[i+5]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo3[index]==0)
						alelo3[index]=1;
					else
						alelo3[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo4[index]==0)
						alelo4[index]=1;
					else
						alelo4[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo5[index]==0)
						alelo5[index]=1;
					else
						alelo5[index]=0;
				}
				aux = BinToInt(alelo3);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+3]=aux;
				aux = BinToInt(alelo4);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+4]=aux;
				aux = BinToInt(alelo5);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+5]=aux;
			}
		}
		else if(tipo==G_PC)//<x,y,a,b,c> , max int(63,63,NUM_ARENAS,NUM_ARENAS,NUM_ARENAS), bin size(6,6,bsize_arenas*3)
		{
			//double p = (double)1/((double)genoma.size()*(6+6+4+4+4));
			double p = (double)1/((double)genoma.size());
			int aux=0;
			int index=0;
			vector<int> alelo0,alelo1,alelo2,alelo3,alelo4;
			for(unsigned int i=0; i<genoma.size();i+=5)
			{
				alelo0 = IntToBin(genoma[i]);
				alelo1 = IntToBin(genoma[i+1]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo0[index]==0)
						alelo0[index]=1;
					else
						alelo0[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,0);
					if(alelo1[index]==0)
						alelo1[index]=1;
					else
						alelo1[index]=0;
				}
				aux = BinToInt(alelo0);
				genoma[i]=aux;
				aux = BinToInt(alelo1);
				genoma[i+1]=aux;
				//------------------------------------------------------------------------------
				//nada aqui
				//------------------------------------------------------------------------------
				alelo2 = IntToBin(genoma[i+2]);
				alelo3 = IntToBin(genoma[i+3]);
				alelo4 = IntToBin(genoma[i+4]);
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo2[index]==0)
						alelo2[index]=1;
					else
						alelo2[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo3[index]==0)
						alelo3[index]=1;
					else
						alelo3[index]=0;
				}
				if(Draw::Prob(p))
				{
					index=Draw::Rngi(5,2);
					if(alelo4[index]==0)
						alelo4[index]=1;
					else
						alelo4[index]=0;
				}
				aux = BinToInt(alelo2);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+2]=aux;
				aux = BinToInt(alelo3);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+3]=aux;
				aux = BinToInt(alelo4);
				if(aux>ARENAS_TESTE-1)
					aux-=ARENAS_TESTE-1;
				genoma[i+4]=aux;
			}
		}
		/*cout<<"D: ";
		for(int j=0;j<genoma.size();++j)
		{
			cout<<genoma[j]<<" ";
			if((j+1)%6==0)
				cout<<endl;
		}
		cout<<endl;
		getchar();*/
		return genoma;
	}

}
