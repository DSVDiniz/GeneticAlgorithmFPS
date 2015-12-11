# $1 nome experimento
# $2 populacao
# $3 geracoes
# $4 -grid | -allwhite
# $5 seed
# $6 CPU core (0 até numero de cores maximo)

#gerando primeira geracao
mkdir $1
cp GeradorMapaGenetico $1/GeradorMapaGenetico
cd $1
rm mapa*
./GeradorMapaGenetico $4 $2
rm fitness.txt
cd ..
#preparando fitness
for((i=0;i < $2;i++))
do
	echo "mapa"$i".txt"
	rm map.txt
	cp $1/"mapa"$i".txt" map.txt
	echo "SEED $5" > seed.cfg
	taskset -c $6 /usr/bin/time -f "%E" --append --output=tempo.txt ./sauer_client -T > log.txt
	cat log.txt | grep TimeToFight  | awk '{print $4}' | sh avg-sig.sh | awk '{print $1}' >> $1/fitness.txt
	cat log.txt | grep FreeCells | awk '{print $3}'  >> $1/fitness.txt
done

for((j=0;j < $3;j++))
do
	#gerando prox geracao
	echo GEN $j
	cd $1
	rm mapa*
	./GeradorMapaGenetico $4 "fitness.txt" "genoma.txt" $j
	rm fitness.txt
	cd ..
	#preparando fitness
	for((i=0;i < $2;i++))
	do
		echo "mapa"$i".txt"
		rm map.txt
		cp $1/"mapa"$i".txt" map.txt
		echo "SEED $5" > seed.cfg
		taskset -c $6 /usr/bin/time -f "%E" --append --output=tempo.txt ./sauer_client -T > log.txt		
		cat log.txt | grep TimeToFight  | awk '{print $4}' | sh avg-sig.sh | awk '{print $1}' >> $1/fitness.txt
		cat log.txt | grep FreeCells | awk '{print $3}'  >> $1/fitness.txt
	done
done
cd $1
./GeradorMapaGenetico $4 "fitness.txt" "genoma.txt" "last"
cd ..