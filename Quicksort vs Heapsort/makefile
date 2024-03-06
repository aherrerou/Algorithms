

OPTS = -Wall -O3 -std=c++0x

qs-vs-hs: qs-vs-hs.cc
		g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc

qs-vs-hs.Msteps: qs-vs-hs
		./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gnuplot
		gnuplot qs-vs-hs.gnuplot

tar: qs-vs-hs.cc qs-vs-hs.gnuplot makefile
	tar cvfz 48686160J.tar.gz qs-vs-hs.cc qs-vs-hs.gnuplot makefile

all: qs-vs-hs qs-vs-hs.Msteps graphs
