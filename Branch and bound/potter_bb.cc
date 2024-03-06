

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
#include <queue>
#include <tuple>

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
long int nodos_visitados = 0;
long int nodos_hoja_visitados = 0;
long int nodos_explorados = 0;
long int nodos_no_prometedores_descartados = 0;
long int nodos_no_factibles_descartados = 0;
long int nodos_prometedores_descartados = 0;
long int update_best_v_node_completado = 0;
long int update_best_v_cota_pesimista = 0;


unsigned alfarero_c(const vector<double> &v, const vector<double> &t,const vector<double> &m, int k ,float T){

	float acc_v = 0.0;
	for(int i = k; i < v.size(); i++){
		if(m[i]*t[i] >= T){
			acc_v += T/t[i] * v[i] * m[i];
			break;
		}
		acc_v += v[i] * m[i];
		T -= t[i] * m[i];
	}
	return unsigned(acc_v);
}

int alfarero_d(const vector<double> &v, const vector<double> &t, const vector<double> &m, int k ,float T){

	int acc_v = 0;
	for(int i = k; i < v.size(); i++){ //Recorro el vector con los objetos ordenador con mejor ratio(v/t)
		for(int copias = m[i]; copias >= 0; copias--){ //Cojo el objeto con mejor ratio(v/t) y su numero máximo de copias
			if(copias*t[i] <= T){
			acc_v += copias*v[i];
			T -= copias*t[i];
			break;
			}
		}
	}
	return acc_v;
}


int bb (float T, const vector<float> &t, const vector<int> &v, const vector<int> &m){

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

	using Node = tuple< unsigned,int,float,int >;
	priority_queue< Node > pq;

	int best_v = alfarero_d(s_v,s_t,s_m,0,T);
	unsigned opt_bound = alfarero_c(s_v,s_t,s_m,0,T);

	pq.emplace(opt_bound,0,0.0,0);

	while(!pq.empty()){
		auto [ignore,value,tiempo,k] = pq.top();
		pq.pop();

		if(k == v.size()){
			nodos_hoja_visitados++;
			if(value > best_v){
				update_best_v_node_completado++;
				best_v = value;
			}
			continue;
		}

		for(unsigned j = 0; j <= m[k]; j++){
			nodos_visitados++;
			float new_time = tiempo + j * t[k];
			int new_value = value + j * v[k];

			if(new_time <= T){			
				int pes_bound = new_value + alfarero_d(s_v,s_t,s_m,k+1,T-new_time);
				if(pes_bound > best_v){
					update_best_v_cota_pesimista++;
					best_v = pes_bound;
				}
				unsigned opt_bound = new_value + alfarero_c(s_v,s_t,s_m,k+1,T-new_time);
				if(opt_bound > best_v){
					nodos_explorados++;
					pq.emplace(opt_bound,new_value,new_time,k+1);
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
	 	cout <<"Usage:"<<endl<<"potter_bb -f file"<<endl;
		 
	if (error==0){
		auto begin = high_resolution_clock::now();
		int result_bb = bb(T,t,v,m);
		auto end = high_resolution_clock::now();
		std::chrono::duration<double,std::milli> duration = end - begin;
		cout << result_bb << endl;
		cout << nodos_visitados << " " << nodos_explorados << " " << nodos_hoja_visitados << " " << nodos_no_factibles_descartados << " " << nodos_no_prometedores_descartados;
		cout << " " << nodos_prometedores_descartados << " " << update_best_v_node_completado << " " << update_best_v_cota_pesimista << endl;
		cout << duration.count() << endl;
	}
}