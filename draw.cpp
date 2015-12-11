#include "draw.h"

namespace Draw
{
    /**
    @function Rngi
    @param maximo e minimo
    @return numero aleatorio entre maximo e minimo.
    @description gerador de numeros aleatorios**/
    int Rngi(int max, int min)
    {
        //se o maximo for igual ao minimo, retornar maximo
        if(max!=min)
        {
            if(max!=0)//se max for igual a zero, retornamos zero para evitar divisao por zero
                return min+rand() % ((max+1)-min);
            else
                return 0;
        }
        else
            return max;
    }

	/**
    @function Prob
    @param probabilidade (de 1.0 a 0.0)
    @return true ou false
    @description a partir de uma probabilidade de 0.0 a 1.0, procuramos um valor aleatorio entre 0
    e RAND_MAX e retornamos true ou false caso o numero esteja dentro da probabilidade**/
	bool Prob(double p)//probabilidade com precisao 0.0001%
	{
		double res = (double)rand()/(double)RAND_MAX;
		if(res<p)
			return true;
		else
			return false;

	}

    /**
    @function Insert
    @param matriz onde se quer procurar o tile, coordenadas do tile e tipo do tile
    @return o tipo do tile
    @description insere na matriz nas coordenadas desejadas um tile do tipo desejado
    Obs:se nao esta dentro dos limites da matriz, nada eh feito**/
    void Insert(Matriz m ,int x, int y, int t)
    {
        if((x<TAMX)&&(x>0)&&(y<TAMY)&&(y>0))
            m[x][y]=t;
    }
    void Insert(Matriz m ,Point<int> p)
    {
        if((p.x<TAMX)&&(p.x>0)&&(p.y<TAMY))
            m[p.x][p.y]=p.t;
    }


    /**
    @function SimpSqrFill
    @param Matriz, ponto xy, ponto wh
    @return void
    @description Preenche na matriz m uma area limitada pelos pontos xy e wh**/
    void SimpSqrFill(Matriz m, Point<int> xy, Point<int> wh)
    {
        for(int j = xy.y; j <= wh.y; ++j)
            for(int i = xy.x; i <= wh.x; ++i)
                m[i][j]=xy.t;
    }
    void SimpSqrFill(Matriz m,int tipo, int xi, int xf, int yi, int yf)
    {
        for(int j = yi; j <= yf; ++j)
            for(int i = xi; i <= xf; ++i)
                m[i][j]=tipo;
    }

    /**
    @function LinhaGorda
    @param matriz, ponto ini, ponto fim, ponto li, ponto ls, raio
    @return
    @description **/
    void LinhaGorda(Matriz m,Point<int> ini,Point<int> fim,Point<int> li,Point<int> ls, int radius)
    {
    	if((ini.x==fim.x)&&(ini.y==fim.y))
			return;

        Point <int> aux;
        double cosAux, senAux;
        double dx=(int)(fim.x-ini.x), dy=(int)(fim.y-ini.y);
        double diag = sqrt((dx*dx)+(dy*dy));
        dx=dx/diag;
        dy=dy/diag;
        int x_a, y_a;
        for(int i=0; i<diag; ++i)
        {
            aux = *new Point<int>((int)(i*dx)+ini.x,(int) (i*dy)+ini.y,0,ini.t);
            for(int j=0;j<radius;++j)
			{
				for(int i=0; i<360; ++i)
				{
					cosAux 		= cos(i*RAD)*j;
					senAux 		= sin(i*RAD)*j;
					x_a=aux.x+(cosAux);
					y_a=aux.y+(senAux);
					//circulo inicial
					if((x_a<ls.x)&&(y_a<ls.y)&&(x_a>li.x)&&(y_a>li.y))
						if(m[x_a][y_a]!=aux.t)
							m[x_a][y_a]=aux.t;
				}
			}
        }
    }
    void LinhaGorda(Matriz m,int tipo,int ix,int iy,int fx,int fy,int lix,int liy,int lsx,int lsy)
    {
    	if((ix==fx)&&(iy==fy))
			return;
        Point <int> aux;
		double dx=(int)fx-ix, dy=(int)fy-iy;
        double diag = sqrt((dx*dx)+(dy*dy));
        dx=dx/diag;
        dy=dy/diag;
        for(int i=0; i<diag; ++i)
        {
            aux = *new Point<int>((int)(i*dx)+ix,(int) (i*dy)+iy,0,tipo);

			for(int j=-1;j<2;++j)
				for(int k=-1;k<2;++k)
					if((aux.x+j<lsx)&&(aux.y+k<lsy)&&(aux.x+j>lix)&&(aux.y+k>liy))
						if(m[aux.x+j][aux.y+k]!=aux.t)
							m[aux.x+j][aux.y+k]=aux.t;
        }
    }

    //funcao usada para ver o que estamos fazendo
    inline void PrintCoisas(Matriz m)
    {
        char caracteres[] = {',','1','.','s','3','4','5','6','7'};
        for(int j=INI_XY;j<FIM_XY+1;++j)
        {
            for(int i=INI_XY;i<FIM_XY+1;++i)
            {
                cout<<caracteres[m[i][j]];
            }
            cout<<endl;
        }
        getchar();
    }

    //funcao recursiva de flood fill usada para identificar uma area conexa no mapa
    void Fill_4(Matriz m, int fill_paint, int filled,int x, int y,vector<Point<int> > *coord)
    {
        int pt=m[x][y];
        if((pt==filled))
        {
            m[x][y]=fill_paint;
            coord->push_back(*new Point<int>(x,y,fill_paint));//guardando posicoes da area
            Fill_4(m,fill_paint,filled,x-1  ,y,coord);
            Fill_4(m,fill_paint,filled,x+1  ,y,coord);
            Fill_4(m,fill_paint,filled,x    ,y+1,coord);
            Fill_4(m,fill_paint,filled,x    ,y-1,coord);
        }
        else
            return;
    }

    //inicializa o mapa com uma area de 64x64 no meio
    void InitMapa(Matriz m, bool type)
    {
        int off_x=INI_XY;
        int off_y=FIM_XY;

        //inicializando toda matriz
        for(int i=0;i<TAMX;++i)
            for(int j=0;j<TAMY;++j)
                m[i][j]=NO_TILE;

        //bordas 64x64
        for(int i=off_x;i<off_y+1;++i)
                for(int j=off_x;j<off_y+1;++j)
                    m[i][j]=WALL;

        //interior 64x64
        if(type)//all white
        {
            for(int i=off_x+1;i<off_y;++i)
                for(int j=off_x+1;j<off_y;++j)
                    m[i][j]=GROUND;
        }
        else//all black
        {
            for(int i=off_x+1;i<off_y;++i)
                for(int j=off_x+1;j<off_y;++j)
                    m[i][j]=WALL;
        }
    }

    //Caso opcao == CENTRAL : funcao que procura a maior area conexa do mapa e apaga o resto das areas
    //Caso opcao == MAIOR : funcao que procura a area conexa do centro do mapa e apaga o resto das areas
    int AchaArea(Matriz m_orig, int opcao)
    {
        int freespace =0;
        int conj_atual = 3;
        vector< vector<Point<int> > > areas;
        areas.resize(81);
        int off_x1,off_y1;
        int off_x2,off_y2;
        off_x1=off_y1=INI_XY+1;
        off_x2=off_y2=FIM_XY;

        //achando e guardando as posicoes das areas
        for(int i=off_x1;i<off_x2;++i)
        {
            for(int j=off_y1;j<off_y2;++j)
            {
                if(m_orig[j][i]==GROUND)
                {
                    Fill_4(m_orig,conj_atual,GROUND,j,i,&areas[conj_atual-3]);
                    conj_atual++;
                }
            }
        }

        int index = 0;
        if(opcao==0)//descobrindo qual e a maior area e onde ela esta no vetor de areas
        {
            int maior = 0;
            for(int i=0; i<conj_atual-3;++i)
            {
                if(areas[i].size()>(unsigned)maior)
                {
                    maior=areas[i].size();
                    freespace = areas[i].size();
                    index=i;
                }
            }
        }
        else//descobrindo qual e a area central e onde ela esta no vetor de areas
        {
            for(unsigned int i=0;i<areas.size();++i)
            {
                for(unsigned int j=0;j<areas[i].size();++j)
                {
                    if((areas[i][j].x==FIM_XY-INI_XY)&&(areas[i][j].y==FIM_XY-INI_XY))
                    {
                        index = i;
                        freespace = areas[i].size();
                    }
                }
            }
        }

        //apagando areas menores e mudando o chao para o tipo certo
        for(int i=0; i<conj_atual-3;++i)
        {
            for(unsigned int j=0;j<areas[i].size();++j)
                if(i!=index)
                    m_orig[areas[i][j].x][areas[i][j].y]=NO_TILE;
                else
                    m_orig[areas[i][j].x][areas[i][j].y]=GROUND;
        }

        return freespace;
    }

    //funcao que testa em uma area 3x3 se existe algum tile de GROUND emvolta. Se nao houver, ela apaga a borda.
    inline void TesteArea(Matriz m, bool &chao_emvolta, Point<int> posicao_borda)
    {
        int off_x=posicao_borda.x;
        int off_y=posicao_borda.y;
        for(int j=off_x-1; j<off_x+2; ++j)
            for(int k=off_y-1; k<off_y+2; ++k)
                if(m[j][k]==GROUND)
                    chao_emvolta=true;

        if(!chao_emvolta)
            m[off_x][off_y]=NO_TILE;
        else
            chao_emvolta = false;
    }

    //funcao que remove as bordas que nao tem um tile GROUND por perto
    void RemoveBordasExiladas(Matriz m, vector<Point<int> >posicoes_bordas)
    {
        bool chao_emvolta= false;
        //removendo bordas que foram colocadas pelo algoritmo de construcao especifico
        for(unsigned int i=0; i<posicoes_bordas.size();++i)
            TesteArea(m,chao_emvolta,posicoes_bordas[i]);

        //removendo bordas colocadas pela inicializacao do mapa (bordas 64x64)
        int off_x, off_y;
        off_x=INI_XY;
        off_y=FIM_XY;
        for(int i=off_x;i<off_y+1;++i)
        {
            if(m[i][off_x]==WALL)
                TesteArea(m,chao_emvolta,*new Point<int>(i,off_x,0,WALL));
            if(m[i][off_y]==WALL)
                TesteArea(m,chao_emvolta,*new Point<int>(i,off_y,0,WALL));
            if(m[off_x][i]==WALL)
                TesteArea(m,chao_emvolta,*new Point<int>(off_x,i,0,WALL));
            if(m[off_y][i]==WALL)
                TesteArea(m,chao_emvolta,*new Point<int>(off_y,i,0,WALL));
        }
    }

    //melhorar esse algoritmo de busca de espaco livre
    inline void AchaEspaco(Matriz m, int c_x, int c_y, int li_x, int li_y, int ls_x, int ls_y, int raio, int tile)
    {
        float cosAux, senAux;
        int x_a,y_a;
        x_a=y_a=0;

        for(int j=0;j<raio;++j)
        {
            for(int i=0; i<360; ++i)
            {
                cosAux 		= cos(i*RAD)*j;
                senAux 		= sin(i*RAD)*j;
                x_a=c_x+(cosAux);
                y_a=c_y+(senAux);

                //circulo inicial
                if((x_a<ls_x)&&(y_a<ls_y)&&(x_a>li_x)&&(y_a>li_y))
                    if(m[x_a][y_a]==GROUND)
                    {
                        m[x_a][y_a]=tile;
                        return;
                    }
            }
        }
    }

    //funcao que insere itens e spawns em posicoes possiveis no mapa.
    void AdicionaItensESpawn(Matriz m,float porcentagem)
    {
        int arma = WEAP_0;
        int densidade=0;
        int x_off=0,y_off=0;
        int a,b,c;
        a=INI_XY+5;
        b=a+2;
        c=a+4;

        for(int k=0;k<5;++k)
        {
            for(int l=0;l<5;++l)
            {
                x_off=l*12;
                y_off=k*12;
                //descobrindo a densidade de uma area 12x12
                for(int j=INI_XY+2+y_off;j<INI_XY+14+y_off;++j)
                {
                    for(int i=INI_XY+2+x_off;i<INI_XY+14+x_off;++i)
                    {
                        if(m[i][j]==GROUND)
                            densidade++;
                    }
                }

                //se a densidade for aceitavel, tentamos inserir os itens/spawns
                if(densidade>=(144*porcentagem))
                {
                    if(m[a+x_off][a+y_off]==GROUND)
                        m[a+x_off][a+y_off]=SPAWN;
                    else//caso nao seja possivel inserir, tentamos achar um lugar proximo que tenha espaco
                        AchaEspaco(m,a+x_off,a+y_off,INI_XY+2+x_off,INI_XY+2+y_off,INI_XY+14+x_off,INI_XY+14+y_off,32,SPAWN);

                    if(m[b+x_off][b+y_off]==GROUND)
                        m[b+x_off][b+y_off]=arma;
                    else
                        AchaEspaco(m,b+x_off,b+y_off,INI_XY+2+x_off,INI_XY+2+y_off,INI_XY+14+x_off,INI_XY+14+y_off,32,arma);

                    if(m[c+x_off][c+y_off]==GROUND)
                        m[c+x_off][c+y_off]=SPAWN;
                    else
                        AchaEspaco(m,c+x_off,c+y_off,INI_XY+2+x_off,INI_XY+2+y_off,INI_XY+14+x_off,INI_XY+14+y_off,32,SPAWN);
                }
                densidade=0;
                arma++;
            }
            arma=WEAP_0;
        }
    }

    vector<Point<int> > RemoveImpassavel(Matriz m)
    {
    	bool N,S,O,L,NO,NL,SL,SO;
    	N=S=O=L=NO=NL=SL=SO=false;

    	vector< Point<int> > pos, bordas_novas;
    	for(int i=INI_XY;i<FIM_XY;++i)
			for(int j=INI_XY;j<FIM_XY;++j)
				if(m[i][j]==GROUND)
					pos.push_back(*new Point<int>(i,j,0,WALL));

		for(unsigned int i=0;i<pos.size();++i)
		{
			if(m[pos[i].x][pos[i].y-1]==WALL)
				N=true;
			if(m[pos[i].x][pos[i].y+1]==WALL)
				S=true;
			if(m[pos[i].x-1][pos[i].y]==WALL)
				O=true;
			if(m[pos[i].x+1][pos[i].y]==WALL)
				L=true;

			if(N&&S)
			{
				m[pos[i].x][pos[i].y]=WALL;
				bordas_novas.push_back(pos[i]);
			}
			else if(L&&O)
			{
				m[pos[i].x][pos[i].y]=WALL;
				bordas_novas.push_back(pos[i]);
			}
			N=S=O=L=false;
		}
		return bordas_novas;
    }
}
