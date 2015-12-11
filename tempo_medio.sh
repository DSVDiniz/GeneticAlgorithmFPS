# $1 nome experimento
# $2 populacao
# $3 geracoes
# $4 -grid | -allwhite

#gerando primeira geracao
mkdir $1
cp GeradorMapaGenetico $1/GeradorMapaGenetico
cd $1
rm mapa*
./GeradorMapaGenetico $4 $2

for((j=0;j < $3;j++))
do
	#gerando prox geracao
	echo GEN $j
	cd $1
	rm mapa*
	time ./GeradorMapaGenetico $4 "fitness.txt" "genoma.txt" $j >>tempo.txt
done
cd $1
./GeradorMapaGenetico $4 "fitness.txt" "genoma.txt" "last"
cd ..