/*
* CPP Projet Modelisation
* file name : spiketimes.cpp
* authors : Belmahi Asmae, Maxwell Sam
* date : 14/04/2021	
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

int findIndexTime(vector<long double> dataTime, long double timeToFind, long double time_0){
	/*
	Calcule l'index correspondant à une donnée de temps dans le vecteur.
	:param dataTime: données de temps
	:param timeToFind: valeur de temps recherché dans le vecteur
	:param time_0: le temps t0 du vecteur
	:type dataTime: vector<long double>
	:type timeToFind: long double
	:type timeToFind: long double  
	*/
	long double step = 0.1; // unité de temps du jeux de données
	int idx = (timeToFind/0.1) +1 - time_0 ;
	return idx;
}

map <string, long double> setupThreshold (vector<long double> dataTime, vector<long double> dataSignal, long double start, long double stop){
	/*
	1) Extrait les données sur l'interval de temps [start,stop]
	2) Trouve le maximum et le minimum sur l'interval
	:param dataTime: données de temps 
	:param dataSignal: données du signal
	:param start: valeur de début d'enregistement sans potentiel d'action 
	:param stop: valeur de fin d'enregistrement sans potentiel d'action
	:type dataTime: vector<lond double>
	:type dataSignal: vector<long double>
	:type start: long double
	:type stop: long double 
	*/
	map<string, long double> result;
	long double max = 0.0; 
	long double min = 0.0;
	int idx1 = findIndexTime(dataTime, start, 0.0);
	int idx2 = findIndexTime(dataTime, stop, 0.0);
	for (int i = idx1 ; i <= idx2 ; i++){
		if (dataSignal[i] > max){
			max = dataSignal[i];
		}
		if (dataSignal[i] < min){
			min = dataSignal[i];
		}
		//cout << "dataSignal = " << dataSignal[i] << " ; max = " << max << " ; min = " << min << endl;  
	}
	result["max"] = max;
	result["min"] = min;
	return result;
}

map <string, vector<string> > spiketimes (vector<long double> dataTime, vector<long double> dataSignal, map <string, long double> th_values, long double ref_lapse){
	/*
	Trouve les potentiels d'action sur l'enregistrement.
	:param dataTime: données de temps
	:param dataSignal: données du signal
	:param th_values: maximum et minimum sur l'interval sans P.A
	:param ref_lapse: durrée minimal entre 2 P.A
	:type dataTime: vector<long double>
	:type dataSignal: vector<long double>
	:type th_values: map <string, long double>
	:type ref_lapse: long double
	:return data: données sur les P.A et ligne seuil
	:type return: map <string, vector<long double> > 
	*/
	map <string, vector<string> > data;
	vector<string> Time; 
	vector<string> Signal;
	vector<string> threshold;
	vector<string> spike;
	long double comp_lapse = ref_lapse*10;
	
	for (int i = 0 ; i < dataTime.size() ; i++){
		if (dataSignal[i] < th_values["min"] && ref_lapse*10 < comp_lapse){
			spike.push_back(to_string(th_values["min"]));
			comp_lapse = 0;
		} else {
			comp_lapse++;
			spike.push_back("nan");
		}
		Time.push_back(to_string(dataTime[i]));
		Signal.push_back(to_string(dataSignal[i]));
		threshold.push_back(to_string(th_values["min"]));
	}
	data["Time"] = Time;
	data["Signal"] = Signal;
	data["Spike"] = spike;
	data["Threshold"] = threshold;
	return data;
}

int main (int argc, char *argv[]){
	try{
		// recuperation des arguments : 
		string fileName = argv[1];
		string newFileName = argv[2];
		long double start = stold(argv[3]);
		long double stop = stold(argv[4]);
		long double ref_lapse = stold(argv[5]);
		// extraction des donnnées du fichier : 
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		map<string, vector<long double> > dataChannel = getColumnsChannel(fileContent);
		cout << "** Données extraites" << endl;
		// identification des P.A : 
		cout << "* identification des potentiels d'action" << endl;
		map<string, long double> th_values = setupThreshold(dataChannel["Time"], dataChannel["Signal"], start, stop);
		cout << "** valeur seuil établit" << endl; 
		map<string, vector<string> > dataSpikes = spiketimes (dataChannel["Time"], dataChannel["Signal"], th_values, ref_lapse);
		cout << "** recherche des potentiels d'action terminée" << endl;
		// Ecriture du fichier : 
		cout << "* Ecriture du fichier" << endl;
		string content = "%time value spike threshold\n";
		string line;
		for (int i = 0 ; i < dataSpikes["Time"].size() ; i++){
			line = dataSpikes["Time"][i]+" ";
			line += dataSpikes["Signal"][i]+" ";
			line += dataSpikes["Spike"][i]+" ";
			line += dataSpikes["Threshold"][i]+"\n";
			content += line; 
		}
		writeFile(content, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl;
	}catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}