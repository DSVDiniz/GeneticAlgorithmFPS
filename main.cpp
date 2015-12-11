#include "Geradores.h"

Matriz mapa;

int main(int argc, char **argv)
{
    int num_pop;
    srand(time(NULL));
    int opcao = CENTRAL;
    if(argc==3)//gerando mapas pela primeira vez
    {
        num_pop = atoi(argv[2]);

        if(strcmp(argv[1],"-grid")==0)//-grid 50
			Geradores::FirstPop(mapa,num_pop, opcao,G_GRID);
        else if(strcmp(argv[1],"-allwhite")==0)//-allwhite 50
            Geradores::FirstPop(mapa,num_pop, opcao,G_ALLWHITE);
        else if(strcmp(argv[1],"-allblack")==0)//-allblack 50
            Geradores::FirstPop(mapa,num_pop, opcao,G_ALLBLACK);
        else if(strcmp(argv[1],"-sc1")==0)//-sc1 50
            Geradores::FirstPop(mapa,num_pop, opcao,G_SC1);
		else if(strcmp(argv[1],"-sc2")==0)//-sc2 50
			Geradores::FirstPop(mapa,num_pop, opcao,G_SC2);
		else if(strcmp(argv[1],"-sc3")==0)//-sc3 50
			Geradores::FirstPop(mapa,num_pop, opcao,G_SC3);
		else if(strcmp(argv[1],"-pc")==0)//-pc 50
			Geradores::FirstPop(mapa,num_pop, opcao,G_PC);
        else if(strcmp(argv[1],"-gridgen")==0)//-gridgen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_GRID);
        else if(strcmp(argv[1],"-allwhitegen")==0)//-allwhitegen arq.txt
            Geradores::GenomaToFile(mapa,argv[2],G_ALLWHITE);
        else if(strcmp(argv[1],"-allblackgen")==0)//-allblackgen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_ALLBLACK);
        else if(strcmp(argv[1],"-diggergen")==0)//-diggergen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_DIGGER);
        else if(strcmp(argv[1],"-sc1gen")==0)//-sc1gen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_SC1);
		else if(strcmp(argv[1],"-sc2gen")==0)//-sc2gen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_SC2);
		else if(strcmp(argv[1],"-sc3gen")==0)//-sc3gen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_SC3);
		else if(strcmp(argv[1],"-pcgen")==0)//-pcgen arq.txt
        	Geradores::GenomaToFile(mapa,argv[2],G_PC);
        else if(strcmp(argv[1],"-gridcontinue")==0)//-gridcontinue <gen>
		{
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_GRID);
		}
        else if(strcmp(argv[1],"-allwhitecontinue")==0)//-allwhitecontinue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_ALLWHITE);
		}
        else if(strcmp(argv[1],"-allblackcontinue")==0)//-allblackcontinue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_ALLBLACK);
		}
        else if(strcmp(argv[1],"-diggercontinue")==0)//-diggercontinue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_DIGGER);
		}
        else if(strcmp(argv[1],"-sc1continue")==0)//-sc1continue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_SC1);
		}
		else if(strcmp(argv[1],"-sc2continue")==0)//-sc2continue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_SC2);
		}
		else if(strcmp(argv[1],"-sc3continue")==0)//-sc3continue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_SC3);
		}
		else if(strcmp(argv[1],"-pccontinue")==0)//-pccontinue <gen>
        {
			vector<vector<int> >genoma = io::ReadGenoma("genoma.txt");
			Geradores::ContinueRun(mapa,genoma,atoi(argv[2]),opcao,G_PC);
		}
        else if(true)
        {

        }
    }
    else if(argc==5)//lendo fitness para preparar nova geracao
    {
    	vector<int>fitness = io::ReadFitness(argv[2]);
		vector<vector<int> >genoma = io::ReadGenoma(argv[3]);
		cout<<"F.size:"<<fitness.size()<<" G.size:"<<genoma.size()<<endl;
		stringstream nome_backup;

		if((fitness.size()!=0)&&(fitness.size()==genoma.size()))
		{
			cout<<fitness.size()<<" individuos encontrados."<<endl;

			if(strcmp(argv[4],"last")==0)
				io::WriteGenBackup(fitness,genoma,"GEN_BCKP_END.txt");
			else
			{
				nome_backup<<"GEN_BCKP_"<<atoi(argv[4])<<".txt";
				io::WriteGenBackup(fitness,genoma,nome_backup.str());
				if(strcmp(argv[1],"-grid")==0)//-grid fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_GRID);
				else if(strcmp(argv[1],"-allwhite")==0)//-allwhite fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_ALLWHITE);
				else if(strcmp(argv[1],"-allblack")==0)//-allblack fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_ALLBLACK);
				else if(strcmp(argv[1],"-digger")==0)//-digger fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_DIGGER);
				else if(strcmp(argv[1],"-sc1")==0)//-sc1 fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_SC1);
				else if(strcmp(argv[1],"-sc2")==0)//-sc2 fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_SC2);
				else if(strcmp(argv[1],"-sc3")==0)//-sc3 fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_SC3);
				else if(strcmp(argv[1],"-pc")==0)//-pc fitness.txt genoma.txt
					Geradores::NextPop(mapa,genoma,fitness,opcao,G_PC);
				else if(true)
				{

				}
			}
		}
		else
			cout<<"Numero de fitness nao eh igual ao de genomas."<<endl;
    }
    else
	{
		cout<<"Parametros errados.\n\t ./nomeprograma <-allwhite, -grid, -allblack, -sc1, -sc2, -sc3, -pc>";
        cout<<" <tam_populacao> <nome_arquivo.txt> <num geracao, ultima geracao = last>"<<endl;
        cout<<"Ou\n\t ./nomeprograma <-allwhite, -grid, -allblack, -sc1, -sc2, -sc3, -pc>";
        cout<<" <tam_populacao>"<<endl;
	}

    return 0;
}
