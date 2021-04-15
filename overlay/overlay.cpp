/*
* CPP Projet Modelisation
* file name : overlay.cpp
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

vector <vector <string> > overlay (vector<string> dataSignal, vector<string> dataSpike, int before, int after){
	/*
	Recupère les valeurs de signal sur l'interval [before, after] autour des P.A identifiés.
	:param dataSignal: données du signal
	:param dataSpike: données d'identification des PA 
	:param before: borne droite de l'interval autour du PA (en ms)
	:param after: borne gauche de l'interval autur du PA (en ms)
	:type dataSignal: vector<string> 
	:type dataSpike: vector<string>
	:type before: int
	:type before: int
	:return data: données de signal sur l'interval autour des PA
	:type return: vector <vector <string> >
	*/
	vector<vector<string> > data;
	int cmpt_spike = 0;
	long double cmpt_ms = 0;
	long double step = 0.1; // 0.1 ms
	// interval [t1, t2] :
	int t1 = before/step; 
	int t2 = after/step;
	// colonne time :  
	vector<string> colTime;
	for (long double i = -before ; i <= after ; i = round(i+step, 1)){
		colTime.push_back(to_string(i));
	}
	
	data.push_back(colTime);
	// colone spike  
	vector <string> newColSpike;
	for (int i = t1-1 ; i < dataSpike.size()-t2+1 ; i++){
		cmpt_ms = round(cmpt_ms+0.1, 1);
		//cout << cmpt_ms << "ms ; nbr spikes " << cmpt_spike << endl;
		if (dataSpike[i] != "nan"){
			cmpt_spike++;
			newColSpike.clear();
			for (int j = i-t1-1 ; j <= i+t2+1 ; j++){
				newColSpike.push_back(dataSignal[j]); // recuperation des info du signal sur l'interval [i-t1 ; i+t2] 
			}
			data.push_back(newColSpike);
		}
	}
	cout << cmpt_spike << " PA trouvés sur " << cmpt_ms << " ms" << endl;
	return data;
}

int main (int argc, char *argv[]){
	try{
		// recuperation des arguments : 
		string fileName = argv[1];
		string newFileName = argv[2];
		int before = stoi(argv[3]);
		int after = stoi(argv[4]);
		// extraction des donnnées du fichier : 
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		map<string, vector<string> > dataSpikes = getColSpikeFile(fileContent);
		cout << "** Données extraites" << endl;
		// Recuperation des valeurs des spikes :  
		vector <vector <string> > dataOverlay = overlay(dataSpikes["Signal"], dataSpikes["Spike"], before, after);
		// Ecriture du fichier : 
		cout << "* Ecriture du fichier" << endl;
		string content = "";
		string line = "";
		for (int i = 0 ; i < dataOverlay[0].size() ; i++){
			for (int j = 0 ; j < dataOverlay.size() ; j++){
				line+= dataOverlay[j][i]; 
				if (j == dataOverlay.size()-1){
					line+="\n";
					content+=line;
					line = "";
				} else {
					line+=" ";
				}
			}
		}	
		writeFile(content, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl;
	}catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}