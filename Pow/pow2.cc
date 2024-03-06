
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

long STEPS=0;


unsigned long pow2_1(unsigned int n) {
	STEPS++;
	if (n==0) {
		return 1;
	}
	else if (n>0) {
		return (2*pow2_1(n-1));
	}
	return -1;
}

unsigned long pow2_2(unsigned int n) {
	STEPS++;
	if (n==0) {
		return 1;
	}
	else if (n%2 == 0) {//es par
		return (pow2_2(n/2)*pow2_2(n/2));
	}
	else if (n%2 != 0) {//es impar
		return (2*pow2_2(n/2)*pow2_2(n/2));
	}
	return -1;
}

unsigned long pow2_3(unsigned int n) {
	STEPS++;
	if (n==0) {
		return 1;
	}
	else if (n > 0) {//es par
		return (pow2_3(n-1)+pow2_3(n-1));
	}
	return -1;

}
int main (void) {

	for (int i=0; i<=30;i=i+2) {
		STEPS=0;
		if(i==0) {
			cout << "n" << setw(14) << "pow2_1" << setw(14)  << "pow2_2" << setw(14)  << "pow2_3" << setw(14) << endl;
			cout << "*****************************************************" << "\n";
		}

		cout << i;

		pow2_1(i);
		cout << setw(10) << STEPS;
		STEPS=0;

		pow2_2(i);
		cout << setw(15) << STEPS;
		STEPS=0;

		pow2_3(i);
		cout << setw(15) << STEPS;
		STEPS=0;

		cout << endl;
	}	
}




