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

vector<vector<long double> > getOverlayData (string fileContent){
	/*
	Recupere le contenu d'un fichier overlay_X.txt et le convertie en valeur numerique
	:param fileContent: contenu du fichier
	:type fileContent: string
	:return dataOverlay: données des colonnes du fichier overlay
	:type return: vector<vector<string> >
	*/
	vector<vector<long double> > dataOverlay; 
	vector<string> row; 
	vector<string> fileLines = split(fileContent, "\n");
	// Premiere ligne et initialisaton de la taille du vecteur
	row = split(fileLines[0], " ");
	for (int i = 0 ; i < row.size() ; i++){
		vector<long double> vect;
		vect.push_back(round(stold(row[i]), 1));
		dataOverlay.push_back(vect);
	} 
	for (int j = 1 ; j < fileLines.size() ; j++){
		row = split(fileLines[j], " ");
		for(int k = 0 ; k < dataOverlay.size() ; k++){
			dataOverlay[k].push_back(round(stold(row[k]), 1));
		}
	}
	return dataOverlay;
}

vector<map<string,long double> > spikes_amp (vector<vector<long double> > dataOverlay){
	/*
	Calcule les amplitudes des PA sur l'enregistrement. 
	:param dataOverlay: données des PA de l'enregistrement
	:type dataOverlay: vector<vector<long double> > 
	:return data_sort: données d'amplitude (Attention, la derniere map contient loc_min et loc_max)
	:type return: vector<map<string,long double> >
	*/
	vector<map<string,long double> > data;
	map<string,long double> loc; 
	map<string,long double> amp_spike;
	long double loc_max = 0;
	long double loc_min = 0;
	long double max = 0;
	long double min = 0;
	long double value;
	for (int i = 1 ; i < dataOverlay.size() ; i++){
		min = 0;
		max = 0;
		for (int j = 0 ; j < dataOverlay[0].size() ; j++){
			value = dataOverlay[i][j];
			if (value < min){
				min = value;
				if (value < loc_min){
					loc_min = value;
				}
			}
			if (value > max){
				max = value;
				if (value > loc_max){
					loc_max = value;
				}
			}
		}
		amp_spike["max"] = max;
		amp_spike["min"] = min;
		data.push_back(amp_spike);
	}
	amp_spike["loc_min"] = loc_min;
	amp_spike["loc_max"] = loc_max;
	data.push_back(amp_spike);
	return data;
}

vector<string> spike_sort (vector<vector<long double> > dataOverlay){
	/*
	Classe les PAs dans 4 groupes différent de par leurs amplitude et 
	ecrit le contenu des 4 fichiers. 
	:param dataOverlay: données des PA 
	:type dataOverlay: vector<string> spike_sort
	:return filesContent: contenus des fichiers 
	:type return: vector<string>
	*/
	vector<string> filesContent;
	string file_1 = "";
	string file_2 = "";
	string file_3 = "";
	string file_4 = "";
	
	
	// Calcule des amplitudes :  
	vector<map<string,long double> > data_amp = spikes_amp (dataOverlay); 
	// recuperation des amplitues max et min du dataset :
	long double loc_max = data_amp[data_amp.size()-1]["loc_max"];
	long double loc_min = data_amp[data_amp.size()-1]["loc_min"];
	data_amp.pop_back();
	// creation des intervals : 
	map<string,long double> inter_1;
	map<string,long double> inter_2;
	map<string,long double> inter_3;
	map<string,long double> inter_4;
	long double amp = loc_max - loc_min;
		// inter_1 
	inter_1["min"] = loc_min;
	inter_1["max"] = loc_min+(amp/4);
		// inter_2
	inter_2["min"] = loc_min+(amp/4);
	inter_2["max"] = loc_min+(amp*2/4);
		// inter_3
	inter_3["min"] = loc_min+(amp*2/4);
	inter_3["max"] = loc_min+(amp*3/4);
		// inter_3
	inter_4["min"] = loc_min+(amp*3/4);
	inter_4["max"] = loc_max;
	// Attribution des groupes : 
	vector<int> Grp_1;
	vector<int> Grp_2;
	vector<int> Grp_3;
	vector<int> Grp_4;
	
	cout << "test " << data_amp[1]["max"] << endl;
	cout << "test_1 " << inter_1["max"] << " : " << inter_1["min"] << endl;
	cout << "test_1 " << inter_2["max"] << " : " << inter_2["min"] << endl;
	cout << "test_1 " << inter_3["max"] << " : " << inter_3["min"] << endl;
	cout << "test_1 " << inter_4["max"] << " : " << inter_4["min"] << endl;
	cout << " ----> " << data_amp.size() << endl;
	
	map<string,long double> value; 
	long double amp_val; 
	for (int i = 0 ; i < data_amp.size() ; i++){
		value = data_amp[i];
		amp_val = value["max"]=value["min"];
		cout << "test_2 " << value["max"] << " : " << value["min"] << endl;
		cout << "groupe 1 size = " << Grp_1.size() << endl;
		cout << "groupe 2 size = " << Grp_2.size() << endl;
		cout << "groupe 3 size = " << Grp_3.size() << endl;
		cout << "groupe 4 size = " << Grp_4.size() << endl;
		cout << "amp = " << amp_val << endl;
		
		if (amp_val >= inter_1["min"] && amp_val < inter_1["max"]){
			cout << "!!!!!!!!!" << endl;
			Grp_1.push_back(i);
		}
		if (amp_val >= inter_2["min"] && amp_val < inter_2["max"]){
			cout << "!!!!!!!!!" << endl;
			Grp_2.push_back(i);
		}
		if (amp_val >= inter_3["min"] && amp_val < inter_3["max"]){
			cout << "!!!!!!!!!" << endl;
			Grp_3.push_back(i);
		}
		if (amp_val > inter_4["min"] && amp_val <= inter_4["max"]){
			cout << "!!!!!!!!!" << endl;
			Grp_4.push_back(i);
		}
	}
	
	cout << Grp_1[0] << endl;
	
	// Ecriture des fichier : 
	for (int i = 0 ; i < dataOverlay[0].size() ; i++){
		for (int j = 0 ; j < Grp_1.size() ; j++){
			file_1 += to_string(dataOverlay[Grp_1[j]][i]);
			if (j == Grp_1.size()-1){
				file_1 += "\n";
			} else {
				file_1 += " ";
			}
		}
		for (int k = 0 ; k < Grp_2.size() ; k++){
			file_1 += to_string(dataOverlay[Grp_2[k]][i]);
			if (k == Grp_2.size()-1){
				file_2 += "\n";
			} else {
				file_2 += " ";
			}
		}
		for (int m = 0 ; m < Grp_3.size() ; m++){
			file_3 += to_string(dataOverlay[Grp_3[m]][i]);
			if (m == Grp_3.size()-1){
				file_3 += "\n";
			} else {
				file_3 += " ";
			}
		}
		for (int q = 0 ; q < Grp_4.size() ; q++){
			file_4 += to_string(dataOverlay[Grp_4[q]][i]);
			if (q == Grp_4.size()-1){
				file_4 += "\n";
			} else {
				file_4 += " ";
			}
		}
	}
	cout << file_1 << endl;
	filesContent.push_back(file_1);
	filesContent.push_back(file_2);
	filesContent.push_back(file_3);
	filesContent.push_back(file_4);
	return filesContent;
}

int main (int argc, char *argv[]){
	try{
		// recuperation des arguments : 
		string fileName = argv[1];
		string newFileName = argv[2];
		// extraction des donnnées du fichier : 
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		vector<vector<long double> > dataOverlay = getOverlayData(fileContent);
		cout << "** Données extraites" << endl;
		cout << "* Analyse des PA et attribution des groupes" << endl;
		vector<string> filesContent = spike_sort(dataOverlay);
		cout << "** classement effectué" << endl;
		// Ecriture du fichier : 
		cout << "* Ecriture des fichiers" << endl;
		writeFile(filesContent[0], newFileName+"_1.txt");
		writeFile(filesContent[1], newFileName+"_2.txt");
		writeFile(filesContent[2], newFileName+"_3.txt");
		writeFile(filesContent[3], newFileName+"_4.txt");
		//string content = "";
		//for (int i = 0 ; i < data_isih.size() ; i++){
		//	content += data_isih[i] + "\n";
		//}	
		//writeFile(content, newFileName);
		cout << "** fichiers créés" << endl;
	}catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}