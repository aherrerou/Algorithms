
OPTS = -Wall -O3 -std=c++0x

potter: potter_greedy.cc
	g++ -o potter_greedy potter_greedy.cc	 

all: potter_greedy

tar: potter_greedy.cc makefile
	tar cvfz 48686160J.tar.gz potter_greedy.cc makefile
