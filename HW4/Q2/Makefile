CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC -std=c++11
SHVER = 2
OS = $(shell uname)

all: convertFile isocheck

isocheck: 
	javac -cp src:./GraphLib/Motif:./GraphLib/lib/* ./GraphLib/Motif/Check.java
	javac -cp src:./GraphLib/Motif:./GraphLib/lib/* ./GraphLib/Motif/CountFeatures.java

convertFile:
	$(CXX) $(CFLAGS) convertFile.cpp -o convertFile
	$(CXX) $(CFLAGS) convertForIso.cpp -o convertForIso
	$(CXX) $(CFLAGS) distFeat.cpp -o distFeat

clean: rmcurdir

rmcurdir:
	rm convertFile
	rm convertForIso