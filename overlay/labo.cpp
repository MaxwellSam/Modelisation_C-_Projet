#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
using namespace std; // utilisation de l'espace de nom de std

long double round(long double var, int n){
	/*
	Calcule l'arrondi de la valeur var à n chiffre après la virgule.
	:param var: valeur à arrondir
	:param n: nombre de chiffres après la virgule
	:type var: long double
	:type n: int
	:return: la valeur arrondie de var à 10^(-n)
	:type return: long double  
	*/
	int b = 10;
	int roundScale = 1;
	for (int i = 0 ; i < n ; i++){
		roundScale = roundScale * b;
	}
	cout << "rs " << roundScale << endl;
	long double value;
	if (var < 0){
		value = (int)(var*roundScale - 0.5);
	} else{
		value = (int)(var*roundScale + 0.5);
	}
	return (long double)value/roundScale;
	
}

int main (){
	vector<double> vect;
	float before = -1.0f;
	float after = 1.0f;
	float step = 0.1f;
	int t1 = before/step;
	int t2 = after/step; 
	long double value = 0.28955;
	long double newValue = round(value, 1);
	cout << "test = " << newValue << endl;
	for (float i = before ; i <= after ; i = round(i+step, 1)){
		cout << i << " ; ";
		vect.push_back(i);
	}
	
	// vect.push_back(before);
// 	cout << vect[0] << endl;
// 	double val = before;
// 	while(true){
// 		val = val+step;
//
// 		cout << val << endl;
// 		vect.push_back(val);
// 		if (val == after){
// 			break;
// 		}
// 	}
	
	cout << endl;
	for (int i = 0 ; i <= vect.size() ; i++){
		cout << vect[i] << endl;
	}
	
}