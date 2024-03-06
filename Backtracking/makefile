
OPTS = -Wall -O3 -std=c++0x

potter: potter_bt.cc
	g++ -o potter_bt potter_bt.cc	 

all: potter_bt

tar: potter_bt.cc makefile
	tar cvfz 48686160J.tar.gz potter_bt.cc makefile
