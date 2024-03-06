

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <sstream> 
#include <stdlib.h>
#include <cstring>
#include <limits>

using namespace std;

int ok_ignore=0;
int ok_t=0;
int peta=0;
string nombre;


/* VARIABLES GLOBALES*/
int n;
int T;
vector<int> t;
vector<int> v;
vector<int> m;
const int SENTINEL = -1;
int total_T = -1;

void showLine1(const int &rsa, const int &rca, const int &iterative,const int &iterative_mejor){
	cout << rsa << " " << rca << " " << iterative << " " << iterative_mejor << endl;
}

void showLine1_ignore_naive(const int &rca, const int &iterative,const int &iterative_mejor){
	cout << rca << " " << iterative << " " << iterative_mejor << endl;
}

void showLine23(const int &n, int* &sol, const vector<int> &t){

int tiempo_acc = 0;
	for(int i=0; i<n; i++){
		cout << sol[i];
		tiempo_acc = tiempo_acc + (sol[i] * t[i]);
		if(i != n-1){ // Utilizado para eliminar espacios y que el diffchecker salga identico
			 cout << " ";
		}
	}
	cout << endl;
	cout << tiempo_acc;
	cout << endl;
}

void showLine4(const vector<vector<int>> &dic){
	cout <<"Memoization matrix: " << endl;
	for(int i=1;i<dic.size();i++){
		for(int j=0;j<dic[i].size();j++){
			if(dic[i][j] == -1){
				cout << "- ";
			}
			else{
			cout << dic[i][j];
				if(j != (dic[i].size() -1)){ // Utilizado para eliminar espacios y que el diffchecker salga identico
				cout << " ";
				} 
			}
		}
		cout << endl;
	}		
}	

void parse(const int &T,const vector<int> &t,const vector<int> &v, const vector<int> &m, int* &sol,const vector<vector<int>> &dic_iterative){

	int n = v.size();
	int T_final = T;
	int cmax = 0;
	 
	for(int o = n-1; o >= 0; o--){
		int maxValor = numeric_limits<int>::lowest();
		for(int i=0; i <= m[o];i++){				
			if(i*t[o] <= T_final){
				int aux = i*v[o] + dic_iterative[o][T_final-(i*t[o])];
				if(aux > maxValor){
					cmax = i;
					maxValor = aux;
				}	
			}
		}
	sol[o] = cmax;
	T_final = T_final - cmax*t[o];

	}
}

void iterativeMatrix(const vector<vector<int>> &dic_iterative){
		cout <<"Iterative matrix: " << endl;
		for(int i=1;i<dic_iterative.size();i++){
		for(int j=0;j<dic_iterative[i].size();j++){
			if(dic_iterative[i][j] == -1){
				cout << "- ";
			}
			else{
			cout << dic_iterative[i][j];
				if(j != (dic_iterative[i].size() -1)){
				cout << " ";
				} 
			}
		}
		cout << endl;
	}
}

int iterative(const int &n, const int &T, const vector<int> &t, const vector<int> &v, const vector<int> &m, vector<vector<int>> &dic_iterative){

int maxValor = numeric_limits<int>::lowest();

		for(int j=1;j<=n;j++){ // Recorro desde el primer hasta el ultimo objeto
			for(int k=1; k<=T;k++){ //Recorro todos los tiempos disponibles para ir llenando la matriz
			maxValor = numeric_limits<int>::lowest();
				for(int i=0; i <= m[j-1];i++){ //Intento calcular valores desde ninguna al maximo de copias disponibles				
					if(i*t[j-1] <= k){
						int aux = i*v[j-1] + dic_iterative[j-1][k-(i*t[j-1])];
						if(aux > maxValor){
						dic_iterative[j][k] = aux;
						maxValor = aux;
						}
					}
				}
			}
		}
		return maxValor;	
}

int iterative_mejor(const int &n, const int &T, const vector<int> &t, const vector<int> &v, const vector<int> &m){
	vector<int> v0(T+1);
	vector<int> v1(T+1);
	int maxValor = numeric_limits<int>::lowest();
	for(int vacio=0; vacio <= T;vacio++) v0[vacio] = 0;

	for(int objeto=1;objeto <= n;objeto++){
		for (int tiempo=1; tiempo <= T; tiempo++){
			maxValor = numeric_limits<int>::lowest();
			for(int copias=0; copias <= m[objeto-1];copias++){
				if(copias*t[objeto-1] <= tiempo){

					int aux = copias*v[objeto-1] + v0[tiempo-(copias*t[objeto-1])];

					if(aux > maxValor){
						v1[tiempo] = aux;
						maxValor = aux;
					}
				}
			}	
		}
		swap(v0,v1);
	}

	return maxValor;
}

int rsa(const int &n, const int &T, const vector<int> &t, const vector<int> &v, const vector<int> &m){

	int maxValor = numeric_limits<int>::lowest();

	if(n == 0){
		return 0;
	}

	for(int i=0;i <= m[n-1];i++){  // Bucle para calcular valor del numero de copias del objeto
		if(i*t[n-1] <= T){ // Compruebo si el tiempo de las copias del objeto es mayor que el tiempo que tengo disponible
			int aux = i*v[n-1] + rsa(n-1,T-(i*t[n-1]),t,v,m); // Calculo el valor con el numero de copias y continuo con el siguiente objeto
			if(aux > maxValor){
				maxValor = aux;
			}
		}		
	}
	return maxValor;
}

int rca(const int &n, const int &T, const vector<int> &t, const vector<int> &v, const vector<int> &m, vector<vector<int>> &dic){
	
	int maxValor = numeric_limits<int>::lowest();

	if(dic[n][T] != SENTINEL){ //Si esta ya calculado el valor con ese numero de copias lo devolvemos
		return dic[n][T];
	}

	if(n == 0){
		return 0;
	}

	for(int i=0;i <= m[n-1];i++){  // Bucle para calcular valor del numero de copias del objeto
			if(i*t[n-1] <= T){ // Compruebo si el tiempo de las copias del objeto es mayor que el tiempo que tengo disponible
				int aux = i*v[n-1] + rca(n-1,T-(i*t[n-1]),t,v,m,dic); // Calculo el valor con el numero de copias y continuo con el siguiente objeto
				if(aux > maxValor){
					maxValor = aux;
					dic[n][T] = maxValor;
				}
			}	
	}
	return maxValor;
}

// Creamos el fichero a leer
ifstream l;
int leerfichero (string fichero) {
	l.open(fichero.c_str(),ios::out);
	if (l.is_open()){
		l >> n; 
		l >> T; 
		int auxiliar;
			for(int i = 0; i<n; i++){
				l >> auxiliar;
				t.push_back(auxiliar);
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
		else if ((strcmp(argv[i],"--ignore-naive")==0)) {
			ok_ignore=1;

		}
		else if ((strcmp(argv[i],"-t")==0)) {
			ok_t=1;
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
	 	cout <<"Usage:"<<endl<<"potter  [-t] [--ignore-naive] -f file"<<endl;
		 
	if (peta==0){
		vector< vector< int >> dic(n+1, vector<int>(T+1, SENTINEL));
		vector< vector<int >> dic_iterative(n+1, vector<int>(T+1));
		// Relleno los limites con 0 para la version recursiva con almacen
		for(int i=0;i<=T;i++){dic_iterative[0][i] = 0;}
		for(int j=0;j<=n;j++){dic_iterative[j][0] = 0;}
		// Llamo a la funcion con todos los objetos que necesito
		//int *copias = new int[n]; //Variable para guardar el numero de copias empleadas para el numero maximo

		// Obtengo los valores de todas las funciones salvo recursiva ingenua
		int rca_result = rca(n,T,t,v,m,dic);
		int iterative_result = iterative(n,T,t,v,m,dic_iterative);
		int iterative_mejor_result = iterative_mejor(n,T,t,v,m);
		int *sol = new int[n];
		for(int i=0;i<n;i++) sol[i] = -1;
		parse(T,t,v,m,sol,dic_iterative);
		if(ok_ignore == 1 && ok_t == 0){
			showLine1_ignore_naive(rca_result,iterative_result,iterative_mejor_result);
			showLine23(n,sol,t);
		}
		else if(ok_ignore == 1 && ok_t == 1){
			showLine1_ignore_naive(rca_result,iterative_result,iterative_mejor_result);
			showLine23(n,sol,t);
			showLine4(dic);
			iterativeMatrix(dic_iterative);
		}
		else if(ok_ignore == 0 && ok_t == 1){
			int rsa_result = rsa(n,T,t,v,m);
			showLine1(rsa_result,rca_result,iterative_result,iterative_mejor_result);
			showLine23(n,sol,t);
			showLine4(dic);
			iterativeMatrix(dic_iterative);
		}

		else{		
			int rsa_result = rsa(n,T,t,v,m);	
			showLine1(rsa_result,rca_result,iterative_result,iterative_mejor_result);
			showLine23(n,sol,t);

		}
	}
}