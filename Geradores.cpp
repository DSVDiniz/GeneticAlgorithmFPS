#include "Geradores.h"

namespace Geradores
{
	vector<vector<int> > IniPop(int tipo,int num_pop)
	{
		vector<vector<int> > pop;
        pop.resize(num_pop);
		switch(tipo)
		{
			case G_GRID:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<81;++j)
						pop[i].push_back(Draw::Rngi(3,0));
			break;

			case G_ALLWHITE:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<NW*3;j+=3)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(126,0)-63);
					}
			break;

			case G_ALLBLACK:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<(CORREDORES*3)+(ARENAS*3);j+=3)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(31,0)-15);
					}
			break;

			case G_DIGGER:
				int pf,pr,pl,pv;
				for(int i=0;i<num_pop;++i)
				{
					pf = Draw::Rngi(100,0);
					pr = Draw::Rngi(100-pf,0);
					pl = Draw::Rngi(100-pf-pl,0);
					pv = Draw::Rngi(100,0);
					pop[0].push_back(pf);
					pop[1].push_back(pr);
					pop[2].push_back(pl);
					pop[3].push_back(pv);
				}
			break;

			case G_SC1:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<(ARENAS_TESTE*6);j+=6)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(10,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
					}
			break;

			case G_SC2:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<(ARENAS_TESTE*6);j+=6)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(21,0)-11);
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
					}
			break;

			case G_SC3:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<(ARENAS_TESTE*6);j+=6)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(10,0)-5);
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
					}
			break;

			case G_PC:
				for(int i=0;i<num_pop;++i)
					for(int j=0;j<(ARENAS_TESTE*5);j+=5)
					{
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(63,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
						pop[i].push_back(Draw::Rngi(ARENAS_TESTE-1,0));
					}
			break;
		}
		return pop;
	}

	void FirstPop(Matriz mapa, int num_pop, int opcao, int tipo_gerador)
	{
		cout<<"Gerando populacao de "<<num_pop<<" individuos ";

		vector<vector<int> > pop;
		string nomes[] = {"GRID","ALLWHITE", "ALLBLACK", "DIGGER", "SC1","SC2","SC3","PCSALA"};

		cout<<nomes[tipo_gerador];

		pop = IniPop(tipo_gerador,num_pop);

		for(int i=0; i<num_pop;++i)
		{
			stringstream nome_mapa;
			Geradores::GenerateMap(mapa,pop[i],opcao,tipo_gerador);
			nome_mapa<<"mapa"<<i<<".txt";
			io::WriteMap(mapa,nome_mapa.str());
		}
		io::WriteGenoma(pop,"genoma.txt");
	}

	void NextPop(Matriz mapa, vector<vector<int> > genoma, vector<int> fitness, int opcao, int tipo_gerador)
	{
		vector<vector<int> > nova_geracao;
		nova_geracao = Genetica::Selection(genoma,fitness,tipo_gerador);

		for(unsigned int i=0; i<nova_geracao.size();++i)
		{
			stringstream nome_mapa;
			Geradores::GenerateMap(mapa,nova_geracao[i],opcao,tipo_gerador);
			nome_mapa<<"mapa"<<i<<".txt";
			io::WriteMap(mapa,nome_mapa.str());
		}
		io::WriteGenoma(nova_geracao,"genoma.txt");
	}

	void ContinueRun(Matriz mapa, vector<vector<int> > genoma,int geracao,int opcao,int tipo_gerador)
	{
		for(int i=0; i<genoma.size();++i)
		{
			stringstream nome_mapa;
			Geradores::GenerateMap(mapa,genoma[i],opcao,tipo_gerador);
			nome_mapa<<"mapa"<<i<<".txt";
			io::WriteMap(mapa,nome_mapa.str());
		}
	}

	void GenomaToFile(Matriz mapa,char * arq, int opcao)
    {
        string nomearqs[] = {"GRIDGEN", "ALLWHITEGEN", "ALLBLACKGEN", "DIGGERGEN", "SC1GEN","SC2GEN2","SC3GEN3","PCGEN"};
        cout<<"Imprimindo mapas do arquivo de genomas "<<arq<<endl;
        vector<vector<int> > g;
        g = io::ReadGenoma(arq);
        for(unsigned int i=0; i<g.size();++i)
        {
            stringstream nome_mapa;
            nome_mapa<<nomearqs[i]<<i<<".txt";
            Geradores::GenerateMap(mapa,g[i],opcao,G_GRID);
            io::WriteMap(mapa,nome_mapa.str());
        }
        cout<<"Mapas imprimidos:"<<g.size()<<endl;
        return;
    }

	int GenerateMap(Matriz m, vector<int> genoma,int opcao, int tipo)
	{
		vector<Point<int> >posicoes_bordas, aux;
		int freespace=0;

		switch(tipo)
		{
            case G_GRID:
                Draw::InitMapa(m,true);
                posicoes_bordas = Grid(m,genoma);
            break;

            case G_ALLWHITE:
                Draw::InitMapa(m,true);
                posicoes_bordas = Allwhite(m,genoma);
                //aux = Draw::RemoveImpassavel(m);
                //for(unsigned int i=0;i<aux.size();++i)
					//posicoes_bordas.push_back(aux[i]);
            break;

            case G_ALLBLACK:
                Draw::InitMapa(m,false);
                posicoes_bordas = Allblack(m,genoma);
            break;

            case G_DIGGER:
                Draw::InitMapa(m,false);
                posicoes_bordas = Digger(m,genoma);
            break;

            case G_SC1:
                Draw::InitMapa(m,false);
                posicoes_bordas = Teste(m,genoma);
            break;

            case G_SC2:
                Draw::InitMapa(m,false);
                posicoes_bordas = Teste2(m,genoma);
            break;

            case G_SC3:
                Draw::InitMapa(m,false);
                posicoes_bordas = Teste3(m,genoma);
            break;

            case G_PC:
                Draw::InitMapa(m,false);
                posicoes_bordas = Testesemsala(m,genoma);
            break;
		}

		freespace = Draw::AchaArea(m,opcao);
		Draw::RemoveBordasExiladas(m,posicoes_bordas);
		Draw::AdicionaItensESpawn(m,DENSIDADE);

		return freespace;
	}

	vector<Point<int> > Grid(Matriz m,vector<int> genoma)
	{
		vector<Point<int> >posicoes_bordas;
		Point<int> auxN,auxL;
		for(int i=0;i<9;++i)
		{
			for(int j=0;j<9;++j)
			{
				switch(genoma[j+(i*9)])
				{
					case 0:
					break;

					case 1:
						for(int k=0;k<7;++k)
						{
							auxN=*new Point<int>(k+INI_XY+1+(7*i),INI_XY+(7*j),0,WALL);
							Draw::Insert(m,auxN.x,auxN.y,WALL);//norte
							posicoes_bordas.push_back(auxN);
						}
					break;

					case 2:
						for(int k=0;k<7;++k)
						{
							auxL=*new Point<int>(INI_XY+7+(7*i),k+INI_XY+(7*j),0,WALL);
							Draw::Insert(m,auxL.x,auxL.y,WALL);//leste
							posicoes_bordas.push_back(auxL);
						}
					break;

					case 3:
					{
						for(int k=0;k<7;++k)
						{
							auxN=*new Point<int>(k+INI_XY+1+(7*i),INI_XY+(7*j),0,WALL);
							auxL=*new Point<int>(INI_XY+7+(7*i),k+INI_XY+(7*j),0,WALL);
							Draw::Insert(m,auxN.x,auxN.y,WALL);//norte
							posicoes_bordas.push_back(auxN);
							Draw::Insert(m,auxL.x,auxL.y,WALL);//leste
							posicoes_bordas.push_back(auxL);
						}
					}
					break;
				}
			}
		}
		return posicoes_bordas;
	}

	vector<Point<int> > Allwhite(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas;
		Point<int> aux;
		int off_x1,off_x2,off_y1,off_y2;
		off_x1=off_y1=INI_XY;
		off_x2=off_y2=FIM_XY;
		int x,y;
		for(int i=0;i<NW*3;i+=3)
		{
			x=genoma[i]+off_x1;
			y=genoma[i+1]+off_y1;
			if(genoma[i+2]>0)//alinhado a X
			{
				int j=x;
				int k=0;
				while((j<off_x2)&&(k<=genoma[i+2]))
				{
					aux=*new Point<int>(j,y,0,WALL);
					m[j][y]=WALL;
					posicoes_bordas.push_back(aux);
					j++;
					k++;
				}
				j=k=0;
			}
			else//alinhado a Y
			{
				int j=y;
				int k=0;
				while((j<off_y2)&&(k<=-genoma[i+2]))
				{
					aux=*new Point<int>(x,j,0,WALL);
					m[x][j]=WALL;//Draw::Insert(m,aux);
					posicoes_bordas.push_back(aux);
					j++;
					k++;
				}
				j=k=0;
			}
			x=y=0;
		}

		return posicoes_bordas;
	}

	vector<Point<int> > Allblack(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas;
		int tam = (CORREDORES*3) + (ARENAS*3);
		int off_x1=0, off_x2=0,off_y1=0, off_y2=0;
		int aux1=0,aux2=0,aux3=0;
		for(int i=0; i<tam;i+=3)
		{
			aux1 = INI_XY+1 + genoma[i];
			aux2 = INI_XY+1 + genoma[i+1];
			if(i<15)//arena
			{
				if(genoma[i+2]<0)
					aux3 = -genoma[i+2];
				else
					aux3 = genoma[i+2];

				off_x1 = aux1 - aux3;
				off_x2 = aux1 + aux3;
				off_y1 = aux2 - aux3;
				off_y2 = aux2 + aux3;
			}
			else//corredor
			{
				if(genoma[i+2]>0)//horizontal
				{
					off_x1 = aux1 - genoma[i+2];
					off_x2 = aux1 + genoma[i+2];
					off_y1 = aux2 - 1;
					off_y2 = aux2 + 1;
				}
				else//vertical
				{
					off_x1 = aux1 - 1;
					off_x2 = aux1 + 1;
					off_y1 = aux2 - genoma[i+2];
					off_y2 = aux1 + genoma[i+2];
				}
			}

			if(off_x1<=INI_XY)
				off_x1 = INI_XY+1;
			if(off_x2>=FIM_XY)
				off_x2 = FIM_XY-1;
			if(off_y1<=INI_XY)
				off_y1 = INI_XY+1;
			if(off_y2>=FIM_XY)
				off_y2 = FIM_XY-1;

			Draw::SimpSqrFill(m,GROUND,off_x1,off_x2,off_y1,off_y2);
		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));

		return posicoes_bordas;
	}

	vector<Point<int> > Digger(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas;

		/*double pf,pr,pl,pv;

		int aux = Draw::Rngi(100,1);
		int posx=FIM_XY-INI_XY;
		int posy=FIM_XY-INI_XY;

		m[posx][posy]=GROUND;

		for(int i=0; i<ESPACO_DIGGER;++i)
		{
			if((aux>0)&&(aux<=pf))
			{

			}
			else if((aux>pf)&&(aux<=pf+pr))
			{

			}
			else if((aux>pf+pr)&&(aux<=pf+pr+pl))
			{

			}

		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));
		*/
		return posicoes_bordas;
	}

	vector<Point<int> > Teste(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas;
		int tam = ARENAS_TESTE*6;
		int off_x1=0, off_x2=0,off_y1=0, off_y2=0;
		int aux0=0,aux1=0,aux2=0,aux3=0,aux4=0,aux5=0;
		for(int i=0; i<tam;i+=6)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux2 = genoma[i+2];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			aux5 = genoma[i+5];

			off_x1 = aux0+1 - aux2;
			off_x2 = aux0+1 + aux2;
			off_y1 = aux1+1 - aux2;
			off_y2 = aux1+1 + aux2;

			if(off_x1<=INI_XY)
				off_x1 = INI_XY+1;
			if(off_x2>=FIM_XY)
				off_x2 = FIM_XY-1;
			if(off_y1<=INI_XY)
				off_y1 = INI_XY+1;
			if(off_y2>=FIM_XY)
				off_y2 = FIM_XY-1;

			Draw::SimpSqrFill(m,GROUND,off_x1,off_x2,off_y1,off_y2);

			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*6],INI_XY+genoma[(aux3*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*6],INI_XY+genoma[(aux4*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux5*6],INI_XY+genoma[(aux5*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));

		return posicoes_bordas;
	}

	vector<Point<int> > Teste2(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas,aux;
		bool negativo=false;
		int tam = ARENAS_TESTE*6;
		int off_x1=0, off_x2=0,off_y1=0, off_y2=0;
		int aux0=0,aux1=0,aux2=0,aux3=0,aux4=0,aux5=0;
		for(int i=0; i<tam;i+=6)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux2 = genoma[i+2];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			aux5 = genoma[i+5];

			if(aux2<0)
			{
				negativo=true;
				aux2=-aux2;
			}

			off_x1 = aux0+1 - aux2;
			off_x2 = aux0+1 + aux2;
			off_y1 = aux1+1 - aux2;
			off_y2 = aux1+1 + aux2;

			if(off_x1<=INI_XY)
				off_x1 = INI_XY+1;
			if(off_x2>=FIM_XY)
				off_x2 = FIM_XY-1;
			if(off_y1<=INI_XY)
				off_y1 = INI_XY+1;
			if(off_y2>=FIM_XY)
				off_y2 = FIM_XY-1;

			if(negativo)
				Draw::SimpSqrFill(m,WALL,off_x1,off_x2,off_y1,off_y2);
			else
				Draw::SimpSqrFill(m,GROUND,off_x1,off_x2,off_y1,off_y2);

			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*6],INI_XY+genoma[(aux3*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*6],INI_XY+genoma[(aux4*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux5*6],INI_XY+genoma[(aux5*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			negativo=false;
		}
		for(int i=0; i<tam;i+=6)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			aux5 = genoma[i+5];
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*6],INI_XY+genoma[(aux3*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*6],INI_XY+genoma[(aux4*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux5*6],INI_XY+genoma[(aux5*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));

		return posicoes_bordas;
	}

	vector<Point<int> > Teste3(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas,aux;
		bool negativo=false;
		int tam = ARENAS_TESTE*6;
		int off_x1=0, off_x2=0,off_y1=0, off_y2=0;
		int aux0=0,aux1=0,aux2=0,aux3=0,aux4=0,aux5=0;
		for(int i=0; i<tam;i+=6)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux2 = genoma[i+2];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			aux5 = genoma[i+5];

			if(aux2<0)
			{
				negativo=true;
				aux2=-aux2;
			}

			off_x1 = aux0+1 - aux2;
			off_x2 = aux0+1 + aux2;
			off_y1 = aux1+1 - aux2;
			off_y2 = aux1+1 + aux2;

			if(off_x1<=INI_XY)
				off_x1 = INI_XY+1;
			if(off_x2>=FIM_XY)
				off_x2 = FIM_XY-1;
			if(off_y1<=INI_XY)
				off_y1 = INI_XY+1;
			if(off_y2>=FIM_XY)
				off_y2 = FIM_XY-1;

			if(negativo)
				Draw::SimpSqrFill(m,WALL,off_x1,off_x2,off_y1,off_y2);
			else
				Draw::SimpSqrFill(m,GROUND,off_x1,off_x2,off_y1,off_y2);

			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*6],INI_XY+genoma[(aux3*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*6],INI_XY+genoma[(aux4*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux5*6],INI_XY+genoma[(aux5*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			negativo=false;
		}
		for(int i=0; i<tam;i+=6)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			aux5 = genoma[i+5];
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*6],INI_XY+genoma[(aux3*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*6],INI_XY+genoma[(aux4*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux5*6],INI_XY+genoma[(aux5*6)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));

		return posicoes_bordas;
	}

	vector<Point<int> > Testesemsala(Matriz m,vector<int>genoma)
	{
		vector<Point<int> >posicoes_bordas,aux;
		int tam = ARENAS_TESTE*5;
		int aux0=0,aux1=0,aux2=0,aux3=0,aux4=0;

		for(int i=0; i<tam;i+=5)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux2 = genoma[i+2];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];

			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux2*5],INI_XY+genoma[(aux2*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*5],INI_XY+genoma[(aux3*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*5],INI_XY+genoma[(aux4*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
		}
		for(int i=0; i<tam;i+=5)
		{
			aux0 = INI_XY + genoma[i];
			aux1 = INI_XY + genoma[i+1];
			aux2 = genoma[i+2];
			aux3 = genoma[i+3];
			aux4 = genoma[i+4];
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux2*5],INI_XY+genoma[(aux2*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux3*5],INI_XY+genoma[(aux3*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
			Draw::LinhaGorda(m,GROUND,aux0,aux1,INI_XY+genoma[aux4*5],INI_XY+genoma[(aux4*5)+1],INI_XY,INI_XY,FIM_XY,FIM_XY);
		}

		for(int j=0;j<FIM_XY;++j)
			for(int i=0;i<FIM_XY;++i)
				if(m[i][j]==WALL)
					posicoes_bordas.push_back(*new Point<int>(i,j,0,WALL));

		return posicoes_bordas;
	}
}

