/*
* CPP Projet Modelisation
* file name : set_baseline.cpp
* authors : Belmahi Asmae, Maxwell Sam
* date : 12/04/2021	
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

vector <long double> set_baseline (vector<long double> dataSignal, int win_size){
	vector<long double> c_dataSignal;
	// calcule de la moyenne mobile : 
	cout << "*** Calcule de la moyenne mobile" << endl; 
	vector<long double> mvAvg = calcMovingAvg(dataSignal, win_size);
	// soustraction de la base-line au signal de base 
	cout << "*** Soustraction de la base-line au signal d'origine" << endl;
	long double c_value; 
	for (int i = 0 ; i < dataSignal.size() ; i++){
		c_value = dataSignal[i]-mvAvg[i];
		c_dataSignal.push_back(c_value);
	}
	return c_dataSignal; 
}

int main (int argc, char *argv[]){
	try {
		// recuperation des arguments 
		string fileName = argv[1];
		string newFileName = argv[2];
		int numChannel = stoi(argv[3]);
		int win_size = stoi(argv[4]);
		// recupération du contenu du fichier source
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		map<string, vector<long double> > dataChannel = extractChannel(numChannel, fileContent);
		cout << "** Données extraites" << endl;
		// soustraction de la base-line 
		cout << "* Correction du signal" << endl;
		vector<long double> c_dataSignal = set_baseline(dataChannel["Signal"], win_size);
		// Ecriture du fichier 
		string newFileContent = "%time c_channel_"+to_string(numChannel)+"\n";
		for (int i = 0 ; i < dataChannel["Time"].size() ; i++){
			newFileContent += to_string(dataChannel["Time"][i])+" "+to_string(c_dataSignal[i])+"\n";
		}
		writeFile(newFileContent, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl; 
		writeFile(newFileContent, newFileName);
	}catch(exception& ex){
		cerr << "Erreur : probleme dans les arguments" << endl;
	}
}