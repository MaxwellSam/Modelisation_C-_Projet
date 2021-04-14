/*
* CPP Projet Modelisation
* file name : myToolBox.cpp
* authors : Belmahi Asmae, Maxwell Sam
* date : 11/04/2021	
*
* description : Fichier source contenant les méthodes outils du projet. 
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std; // utilisation de l'espace de nom de std

/*
 -------------------------- common functions ----------------------------------- 
*/

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


/*
 ------------------------ extract functions ---------------------------------
*/

vector<string> splitElements (string line){
	/*
	Convertie une chaine de caractères en un vecteurs d'éléments. 
	expl : string line = "ab   bc   cd   abcd"
		  vector v = {"ab", "bc", "cd", "abcd"}
	
	:param line: chaine de caractère contenant des données sur une ligne
	:type line: str
	:return: vecteur d'éléments 
	:type return: vector <string> 
	*/
	string element = ""; 
	vector <string> content; 
	for (int i = 0 ; i < line.size() ; i++) {
		if (line[i] != ' ' and line[i] != '\t'){
			element += line[i];
		} 
		if (line[i] == ' ' and element != ""){
			content.push_back(element);
			element = "";
		}
		if (line[i] == ' ' or line[i] == '\t' and element == ""){
			continue;
		}
	}
	content.push_back(element);
	return content;
}

map<string, vector<long double> > extractChannel (int numChannel, string fileContent) {
	/*
	Extrait les données d'un canal à partir du contenu du fichier source. 
	:param numChannel: numero du canal
	:param fileContent: contenu du fichier source
	:type numChannel: int 
	:type fileContent: string
	:return Data: données de temps et données du signal du canal
	:type newData: map<string, vector<long double> >
	*/
	
	vector<long double> dataTime;
	vector<long double> dataSignal;
	map<string, vector<long double> > data;
	// preparation des données du fichier source : 
	vector<string> s_content = split(fileContent, "\n"); // découpe des lignes
	vector<string>elements;
	for (int i = 4 ; i < s_content.size() ; i++){
		elements = splitElements(s_content[i]); // extraction des éléments de la ligne
		dataTime.push_back(stold(elements[0])); // ajout de la valeur dans le vecteur temps (+ conversion)
		dataSignal.push_back(stold(elements[numChannel])); // ajout de la valeur dans le vecteur signal (+ conversion)
	}
	data["Time"] = dataTime;
	data["Signal"] = dataSignal;
	return data;
}

/*
 ------------------------ m_average functions ---------------------------------
*/

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
