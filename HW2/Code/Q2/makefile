GPP= g++ -std=c++11

all: MakeClusters.o
	$(GPP) MakeClusters.o -o MakeClusters

rebuild: clear all

MakeClusters.o:
	$(GPP) -c MakeClusters.cpp -o MakeClusters.o

clear:
	rm *.o
	rm MakeClusters