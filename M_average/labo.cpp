#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std; // utilisation de l'espace de nom de std

int main (){
	string myString = "Ok ok Ok";
	vector <string> vec = split(myString, " ");
	for (int i = 0 ; i < vec.size() ; i++){
		cout << vec[i] << endl; 
	} 
}