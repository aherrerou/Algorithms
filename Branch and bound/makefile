
OPTS = -Wall -O3 -std=c++1z

potter: potter_bb.cc
	g++ -o potter_bb potter_bb.cc	 

all: potter_bb

tar: potter_bb.cc makefile memoria.pdf
	tar cvfz 48686160J.tar.gz potter_bb.cc makefile memoria.pdf
