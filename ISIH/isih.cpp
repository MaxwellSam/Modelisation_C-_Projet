/*
* CPP Projet Modelisation
* file name : isih.cpp
* authors : Belmahi Asmae, Maxwell Sam
* date : 15/04/2021	
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

map <string, vector<string> > getColSpikeFile (string fileContent){
	/*
	Recupere les colonnes du fichier spikes. 
	:param fileContent: contenu du fichier
	:type fileContent: string
	:return data: colonnes extraites (type dataframe)  
	:type return: map<string, vector<string> >
	*/
	map <string, vector<string> > data;
	vector <string> Time;
	vector <string> Signal;
	vector <string> Spike;
	vector <string> Threshold;
	vector <string> fileLines = split(fileContent, "\n");
	vector <string> elements; 
	
	for (int i = 1 ; i < fileLines.size() ; i++){
		elements = split(fileLines[i], " ");
		Time.push_back(elements[0]);
		Signal.push_back(elements[1]);
		Spike.push_back(elements[2]);
		Threshold.push_back(elements[3]);
	}
	data["Time"] = Time;
	data["Signal"] = Signal;
	data["Spike"] = Spike;
	data["Threshold"] = Threshold;
	return data;
}

vector<string> isih (vector<string> dataSpike){
	/*
	Calcule le temps entre 2 PA sur l'ensemble de l'enregistrement. 
	:param dataSpike: données des PA identifiés
	:type dataSpike: vector<string>
	:return delta_T: liste des variations de temps entre les PA
	:type return: vector<string> 
	*/
	vector<string> delta_T; 
	long double step = 0.1; 
	long double cmpt = 0;
	for (int i = 0 ; i < dataSpike.size() ; i++){
		if (dataSpike[i]!="nan"){
			delta_T.push_back(to_string(cmpt));
			cmpt = 0;
		}
		cmpt = round(cmpt+step, 1); 
	}
	return delta_T;
}

int main (int argc, char *argv[]){
	try{
		// recuperation des arguments : 
		string fileName = argv[1];
		string newFileName = argv[2];
		// extraction des donnnées du fichier : 
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		map<string, vector<string> > dataSpikes = getColSpikeFile(fileContent);
		cout << "** Données extraites" << endl;
		// Calcule des delta_temps entre les PA :  
		vector<string> data_isih = isih(dataSpikes["Spike"]);
		// Ecriture du fichier : 
		cout << "* Ecriture du fichier" << endl;
		string content = "";
		for (int i = 0 ; i < data_isih.size() ; i++){
			content += data_isih[i] + "\n";
		}	
		writeFile(content, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl;
	}catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}