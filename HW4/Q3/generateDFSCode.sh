if [ "$#" -ne 1 ]; then
	echo "Kindly supply the input file";
	echo "e.g. sh generateDFSCode.sh input.txt";
else
	echo $1;
	#make clean;
	make genDFSCode;
	./genDFSCode $1;
fi