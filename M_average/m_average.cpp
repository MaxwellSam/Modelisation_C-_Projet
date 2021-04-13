/*
* CPP Projet Modelisation
* file name : m_average.cpp
* authors : Belmahi Asmae, Maxwell Sam
* date : 10/04/2021	
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std; // utilisation de l'espace de nom de std

string readFile(string file){
	/*
	Lecture d'un fichier txt
	:param file: nom du fichier
	:type file: string
	:return data: chaine de caractère contenant les infos du fichier
	:type data: string
	*/
	ifstream fichier(file);
	string data;
	string line;
	if(fichier){
		while(getline(fichier, line)){
			data+=line+"\n";
		}
		fichier.close();
	}else cerr << "Impossible d'ouvrir le fichier !" << endl;
	return data;
}

void writeFile (string fileContent,string newfileName){
	/*
	Ecriture dans un fichier txt
	:param fileContent: le contenu du nouveau fichier
	:param newfileName: nom du nouveau fichier
	:type fileContent: str
	:type fileName: str
	*/
	ofstream fichier(newfileName);
	if (fichier){
		fichier << fileContent;
		fichier.close();
	} else {
		cerr << "Impossible" <<endl;
	}
}

vector<string> split(string value, string sep){
	/*
	Découpe une chaine de caractère à un separateur donné
	:param value: la chaine de caractère à traiter
	:param sep: le séparateur
	:type value: string
	:type sep: string
	*/
    string token = "";
    vector<string> parsed;
    string temp = "";
    for(int i = 0; i < value.size(); i++){
        temp = value.at(i);
        if (temp != sep){
            token += value.at(i);
        }
        else{
            parsed.push_back(token);
            token = "";
        }
    }

    if (token != ""){
        parsed.push_back(token);
    }
    return parsed;
}

map<string, vector<long double> > getColumnsChannel (string fileContent){
	/*
	Extrait les deux colones du contenu du fichier d'un canal. 
	:param fileContent: contenu du fichier du canal
	:type fileContent: string
	:return data: les données du canal converties en nombre
	:type return: map<string, vector<long double> >
	*/
	vector<string> linesFile = split(fileContent, "\n");
	vector<long double> dataTime;
	vector<long double> dataSignal;
	map<string, vector<long double> > data;
	vector<string> elements; // elements extraient d'une ligne
	for (int i = 1 ; i < linesFile.size() ; i++){
		elements = split(linesFile[i], " ");
		dataTime.push_back(stold(elements[0]));
		dataSignal.push_back(stold(elements[1]));
	}
	data["Time"] = dataTime;
	data["Signal"] = dataSignal;
	return data;
}

long double calcAvg(int pos, int win_size, vector<long double> dataSignal){
	/*
	Calcule la moyenne sur un interval donné. Les positions de départ
	et d'arret s'adaptent en fonction de la position dans le jeu de 
	données. 
	:param pos: position dans le jeu de données
	:param win_size: interval autour de la position
	:param dataSignal: jeu de données
	:type pos: int 
	:type win_size: int 
	:type data: vector <long double>
	:return: moyenne sur l'interval autour de la position (pos)
	:return type: long double
	*/
	int pos_start = pos-win_size;
	int pos_stop = pos+win_size;
	
	if (pos < win_size){ // permet d'établir le start si l'interval est supérieur à l'interval possible à gauche de pos. 
		pos_start = 0; 
	}
	if (pos+win_size > dataSignal.size()){ // idem mais pour la droite de pos. 
		pos_stop = dataSignal.size()-1;
	}
	int nbrValues = pos_stop - pos_start;
	long double sum = 0;
	
	for (int i = pos_start ; i <= pos_stop ; i++){
		sum += dataSignal[i];
	}
	return sum/nbrValues;
}

vector<long double> calcMovingAvg (vector<long double> dataSignal, int win_size){
	/*
	Calcules la moyenne mobile d'un jeux de données. 
	:param dataSignal: jeu de données
	:param win_size: interval de la moyenne
	:type dataSignal: vector<long double>
	:param win_size: int
	:return mvAvg: moyenne mobile
	:type return: vector<long double>
	*/
	vector <long double> mvAvg;
	long double avg;
	for (int i = 0 ; i < dataSignal.size() ; i++){
		avg = calcAvg(i, win_size, dataSignal);
		mvAvg.push_back(avg);
	}
	return mvAvg;
}

int main (int argc, char *argv[]){
	try{
		// recuperation des arguments : 
		string fileName = argv[1];
		string newFileName = argv[2];
		int win_size = stoi(argv[3]);
		// extraction des donnnées du fichier : 
		cout << "* Extraction des données du fichier " << fileName << endl;
		string fileContent = readFile(fileName);
		map<string, vector<long double> > dataChannel = getColumnsChannel(fileContent);
		cout << "** Données extraites" << endl;
		cout << "* Calcule de la moyenne mobile" << endl;
		vector<long double> mvAvg = calcMovingAvg(dataChannel["Signal"], win_size);
		cout << "** Moyenne mobile calculée" << endl;
		// ecriture du fichier : 
		string newFileContent = "%time av_value\n";
		for (int i = 0 ; i < dataChannel["Time"].size() ; i++){
			newFileContent += to_string(dataChannel["Time"][i])+" "+to_string(mvAvg[i])+"\n";
		}
		writeFile(newFileContent, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl;
	} catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}