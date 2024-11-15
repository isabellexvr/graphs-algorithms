tarjan=./tarjan.bin 

echo "Testando algoritmo de Tarjan"
for i in inputs_tarjan/*.dat
do
	echo -e "\e[33mInstância $i\e[0m";
	$tarjan -f $i | ./ordena.sh > temp;

	j=$(basename $i);
	diff -w temp ./outputs_tarjan/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done