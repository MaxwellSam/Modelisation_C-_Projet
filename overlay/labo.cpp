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
	vect.push_back(2); 
	vect.push_back(1);
	cout << "size " << vect.size() << endl;  
	double last = vect[vect.size()-1];
	vect.pop_back();
	cout << "size " << vect.size() << endl;  
	cout << last << endl;  
	
}
