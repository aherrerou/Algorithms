

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
#include <chrono>
#include <numeric>

using namespace std;
using namespace chrono;

int error=0;
string nombre;

/* VARIABLES GLOBALES*/
int n;
float T;
vector<float> t;
vector<int> v;
vector<int> m;

/* ESTADISTICAS*/
int nodos_visitados = 0;
int nodos_hoja_visitados = 0;
int nodos_explorados = 0;
int nodos_no_prometedores_descartados = 0;
int nodos_no_factibles_descartados = 0;


float alfarero_c(const vector<double> &v, const vector<double> &t,const vector<double> &m, int k ,float T){

	float acc_v = 0.0;
	for(int i = k; i < v.size(); i++){
		if(m[i]*t[i] >= T){
			acc_v += T/t[i] * v[i] * m[i];
			break;
		}
		acc_v += v[i] * m[i];
		T -= t[i] * m[i];
	}
	return acc_v;
}

int greedy(float T, const vector<float> &t, const vector<int> &v, const vector<int> &m){

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
			break;
			}
		}
	}
	return acc_v;
}

void bt(float T, const vector<double> &t, const vector<double> &v, const vector<double> &m,int k, vector<int> &x, double acc_t, int acc_v, int &best_v){

	if(k == x.size()){
		nodos_hoja_visitados++;
		best_v = max(best_v,acc_v);
	}
	else{

		for(int j=m[k]; j >= 0; j--){ //Aplicando reserse order
			nodos_visitados++;
			x[k] = j;
			double present_t = acc_t + x[k] * t[k];
			int present_v = acc_v + x[k] * v[k];
			
			if(present_t <= T){
			 	if(present_v + alfarero_c(v,t,m,k+1,T - present_t) > best_v){ //Aplicando voraz continuo
					nodos_explorados++;
					bt(T,t,v,m,k+1,x,present_t,present_v,best_v);
				}
				else{
					nodos_no_prometedores_descartados++;
				}
			}
			else{
				nodos_no_factibles_descartados++;
			}
		}
	}
}


int bt (float T, const vector<float> &t, const vector<int> &v, const vector<int> &m){

	// ORDENACION DE V,T Y M	
	vector<int> idx(v.size());
	iota(begin(idx), end(idx),0);
	sort(begin(idx), end(idx), [&v,&t] (int i, float j){return v[i]/t[i] > v[j]/t[j];});
	vector<double> s_v(v.size()), s_t(t.size()), s_m(m.size());
	for(int i = 0; i < v.size(); i++){
	s_v[i] = v[idx[i]];
	s_t[i] = t[idx[i]];
	s_m[i] = m[idx[i]];
	}
	//
	vector<int> x(v.size());
	int best_v = greedy(T,t,v,m); // Aplicando la mejor de empezar desde el mejor valor de voraz
	bt(T,s_t,s_v,s_m,0,x,0,0,best_v);
	return best_v;
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
		error=1;
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
			error=1;
		}
	}
}
int main(int argc, char *argv[]) {
	argumentos(argc, argv);

	if (error==0)
		leerfichero(nombre);

	if (error==1)
	 	cout <<"Usage:"<<endl<<"potter_bt -f file"<<endl;
		 
	if (error==0){
		auto begin = high_resolution_clock::now();
		int result_bt = bt(T,t,v,m);
		auto end = high_resolution_clock::now();
		std::chrono::duration<double,std::milli> duration = end - begin;
		cout << result_bt << endl;
		cout << nodos_visitados << " " << nodos_explorados << " " << nodos_hoja_visitados << " " << nodos_no_factibles_descartados << " " << nodos_no_prometedores_descartados << endl;
		cout << duration.count() << endl;
	}
}