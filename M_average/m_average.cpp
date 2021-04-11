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
using namespace std; // utilisation de l'espace de nom de std

string read_data(string file){
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

vector<long double> convertColoneStoLD (int numColone, vector<string> dataLines){
	/*
	Convertie une colone d'un fichier txt en un vecteur de double
	:param numColone: numero de la colone à extraire 
	:param dataLines: vecteur contenant les lignes du fichier txt
	:type numColone: int
	:type dataLines: vector<float>
	:return coloneConverted: vecteur contenant les données converties de la colone
	:type return: vector<float>
	*/
	vector<long double> coloneConverted;
	vector <string> content;
	//string::size_type st;
	long double value;
	for (int i = 1 ; i < dataLines.size() ; i++){
		content = split(dataLines[i], " ");
		value = stold(content[numColone]);
		coloneConverted.push_back(value); 
	}
	return coloneConverted;
}

long double calcAverage(int pos, int win_size, vector<long double> data){
	/*
	Calcule la moyenne sur un interval donné. Les positions de départ
	et d'arret s'adaptent en fonction de la position dans le jeu de 
	données. 
	:param pos: position dans le jeu de données
	:param win_size: interval autour de la position
	:param data: jeu de données
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
	if (pos+win_size > data.size()){ // idem mais pour la droite de pos. 
		pos_stop = data.size()-1;
	}
	int nbrValues = pos_stop - pos_start;
	long double sum = 0;
	
	for (int i = pos_start ; i <= pos_stop ; i++){
		sum += data[i];
	}
	return sum/nbrValues;
}

vector <long double> movingAverage (int win_size, vector<long double> data){
	/*
	Calcule la moyenne mobile d'un jeu de données. 
	:param win_size: taille de l'interval de la moyenne
	:param data: jeu de données
	:type win_size: int
	:type data: vector<long double>
	:return mvAvg: valeurs des moyennes mobiles du jeu
	:type return: vector<long double>
	*/
	vector <long double> mvAvg;
	long double avg;
	for (int i = 0 ; i < data.size() ; i++){
		avg = calcAverage(i, win_size, data);
		mvAvg.push_back(avg);
	}
	return mvAvg;
}

string prepareFileContent (vector<long double> ColTime, vector<long double> ColAvg){
	/*
	Prepare le contenu du fichier sous forme d'une string avec 
	une colone pour le temps et une colone pour la moyenne mobile. 
	:param ColTime: vecteur contenant les valeurs de temps
	:param ColAvg: vecteur contenant les valeurs de moyennes mobiles
	:type ColTime: vector<long double>
	:type ColAvg: vector<long double>
	:return fileContent: chaine de caractère correspondant au contenu du future fichier
	:type return: string
	*/
	string fileContent = "%time av_value\n";
	for (int i = 0 ; i < ColTime.size() ; i++){
		fileContent += to_string(ColTime[i])+" "+to_string(ColAvg[i])+"\n";
	}
	return fileContent;
}

int main (int argc, char *argv[]){
	try{
		string fileName = argv[1];
		string newFileName = argv[2];
		int win_size = stoi(argv[3]);
		string data = read_data(fileName);
		vector<string> dataLines = split(data, "\n");
		vector<long double> ColoneTime = convertColoneStoLD(0, dataLines);
		vector<long double> ColoneChannel = convertColoneStoLD(1, dataLines); 
		vector <long double> mvAvg = movingAverage(win_size, ColoneChannel);
		string fileContent = prepareFileContent(ColoneTime, ColoneChannel);
		writeFile(fileContent, newFileName);
	} catch (exception& ex){
		cerr << "probleme dans les arguments" << endl;
	}
}