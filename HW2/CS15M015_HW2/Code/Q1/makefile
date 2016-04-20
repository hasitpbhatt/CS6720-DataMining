GPP= g++ -std=c++11

all: UtilsApriori.o Transaction.o Apriori.o
	$(GPP) Apriori.o Transaction.o UtilsApriori.o -o Apriori

Apriori.o:
	$(GPP) -c Apriori.cpp -o Apriori.o

Transaction.o:
	$(GPP) -c Transaction.cpp -o Transaction.o

UtilsApriori.o:
	$(GPP) -c UtilsApriori.cpp -o UtilsApriori.o

clear:
	rm UtilsApriori.o Transaction.o Apriori.o