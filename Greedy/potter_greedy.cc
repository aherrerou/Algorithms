

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <sstream> 
#include <stdlib.h>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

int peta=0;
string nombre;

/* VARIABLES GLOBALES*/
int n;
float T;
vector<float> t;
vector<int> v;
vector<int> m;

void extraerCopias (const vector<int> &vector_copias,const vector<float> &t){

float T_aux = 0.0;

	for(int i = 0; i < vector_copias.size(); i++){
		if(i == vector_copias.size() - 1){ // Para evitar el ultimo espacio en blanco
			cout << vector_copias[i];
		}
		else{
		cout << vector_copias[i] << " ";
		}
		if(vector_copias[i] > 0){
		T_aux = T_aux + (vector_copias[i]*t[i]);
		}
	}
	cout << endl;
	cout << T_aux << endl;
}

int greedy(float T, const vector<float> &t, const vector<int> &v, const vector<int> &m, vector<int> &vector_copias){

	vector<int> idx(t.size());
	for(int i = 0; i < idx.size();i++){
		idx[i] = i;
	}

	sort(idx.begin(), idx.end(),[v,t](unsigned x, unsigned y){
		return v[x]/t[x] > v[y]/t[y];});

	int acc_v = 0;
	for(int i = 0; i < idx.size(); i++){ //Recorro el vector con los objetos ordenador con mejor ratio(v/t)
		for(int copias = m[idx[i]]; copias >= 0; copias--){ //Cojo el objeto con mejor ratio(v/t) y su numero máximo de copias
			if(copias*t[idx[i]] <= T){
			acc_v += copias*v[idx[i]];
			T -= copias*t[idx[i]];
			vector_copias[idx[i]] = copias;
			break;
			}
		}
	}
	return acc_v;
}	


// Creamos el fichero a leer
ifstream l;
int leerfichero (string fichero) {
	l.open(fichero.c_str(),ios::out);
	if (l.is_open()){
		l >> n; 
		l >> T; 
		int auxiliar;
		float auxiliar_float;
			for(int i = 0; i<n; i++){
				l >> auxiliar_float;
				t.push_back(auxiliar_float);
			}

			for(int j = 0; j<n; j++){
				l >> auxiliar;
				v.push_back(auxiliar);
			}

			for(int z = 0; z<n; z++){
				l >> auxiliar;
				m.push_back(auxiliar);
			}
		l.close();
	}
	else {
		cout << "ERROR: can’t open file: "<<nombre<<"."<<endl;
		peta=1;
	}
}
int argumentos (int argc, char *argv[]) {
	for (int i=0;i<argc;i++) {
		if ((strcmp(argv[i],"-f")==0)) {
			if (argv[i+1] != NULL){
				nombre=argv[i+1];
			i++;
			}
			else{
				cout << "ERROR: missing filename."<<endl;
			}
		}

		else if(i!=0){
			cout << "ERROR: unknown option "<<argv[i]<<"."<<endl;;
			peta=1;
		}
	}
}
int main(int argc, char *argv[]) {
	argumentos(argc, argv);

	if (peta==0)
		leerfichero(nombre);

	if (peta==1)
	 	cout <<"Usage:"<<endl<<"potter_greedy -f file"<<endl;
		 
	if (peta==0){
		vector<int> vector_copias(t.size());
		for (int i=0; i<vector_copias.size();i++){vector_copias[i] = 0;}
		int result_greedy = greedy(T,t,v,m,vector_copias);
		cout << result_greedy << endl;
		extraerCopias(vector_copias,t);
	}
}