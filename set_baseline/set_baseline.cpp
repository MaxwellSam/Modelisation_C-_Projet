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
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

string set_baseline(string fileContent, int numChannel, int win_size){
	// Extraction des données du fichier source
	string contentExtract = extractChannel(numChannel, fileContent);
	string fileNameExtract = "channel_"+to_string(numChannel)+".txt";
	writeFile(contentExtract, fileNameExtract); 
	cout << "** Extraction des données effectuée" << endl; 
	// Calcule de la moyenne mobile 
	string contentAvg = movingAverage(contentExtract, win_size);
	string fileNameAvg = "avg_channel_"+to_string(numChannel)+".txt";
	writeFile(contentAvg, fileNameAvg);
	cout << "** Calcule de ma moyenne mobile effectuée" << endl;
	//  soustraction de la baseline au signal original 
	vector <string> linesExtract = split(contentExtract, "\n");
	vector <string> linesAvg = split(contentAvg, "\n");
	vector <long double> colTime = convertColoneStoLD(0, linesExtract);
	vector <long double> colSignal = convertColoneStoLD(1, linesExtract);
	vector <long double> colBaseLine = convertColoneStoLD(1, linesAvg);
	cout << colBaseLine[0] << endl; 
	long double c_value;
	string newFileContent = "%time c_channel_"+to_string(numChannel)+"\n";
	for (int i = 0 ; i < colTime.size() ; i++){
		c_value = colSignal[i] - colBaseLine[i];
		cout << "c_value = " << c_value << endl; 
		newFileContent += to_string(colTime[i])+" "+to_string(c_value)+"\n";
	}
	cout << "* Soustraction de la baseline effectuée" << endl; 
	return newFileContent;
}
int main (int argc, char *argv[]){
	try {
		// recuperation des arguments 
		string fileName = argv[1];
		string newFileName = argv[2];
		int numChannel = stoi(argv[3]);
		int win_size = stoi(argv[4]);
		// recupération du contenu du fichier source
		string fileContent = read_data(fileName);
		// Calcule de la baseline
		string newFileContent = set_baseline(fileContent, numChannel, win_size); 
		writeFile(newFileContent, newFileName);
	}catch(exception& ex){
		cerr << "Erreur : probleme dans les arguments" << endl;
	}
}