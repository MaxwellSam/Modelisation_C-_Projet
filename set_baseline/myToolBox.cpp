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
using namespace std; // utilisation de l'espace de nom de std

/*
 -------------------------- common functions ----------------------------------- 
*/

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

string extractChannel (int numChannel, string fileContent) {
	/*
	Produit à partir du contenu du fichier et du numero de channel, 
	une string contenant les informations sur le temps et les données 
	du canal selectionné. 
	:param numChannel: numero du canal
	:param fileContent: contenu du fichier de base en chaine de caractères
	:type numChannel: int 
	:type fileContent: string
	:return newFileContent: la chaine de caractère contenant les infos du canal
	:type return: string
	*/
	
	string newFileContent = "%time channel_"+to_string(numChannel)+"\n"; // première ligne du nouveau fichier  
	vector <string> elementsLine;
	// preparation de la source : 
	vector<string> dataLines=split(fileContent, "\n"); // découpe des lignes
	// creation de la nouvelle chaine de caractère :  
	for (int i = 4 ; i < dataLines.size() ; i++){
		elementsLine = splitElements(dataLines[i]);
		newFileContent += elementsLine[0]+" "+elementsLine[numChannel]+"\n";
	}
	return newFileContent;
}

/*
 ------------------------ m_average functions ---------------------------------
*/

string movingAverage (string fileContent, int win_size){
	/*
	Calcule la moyenne mobile d'un jeu de données à partir du contenu du fichier. 
	:param fileContent: contenu du fichier de base en chaine de caractères 
	:param win_size: taille de l'interval des moyennes
	:type win_size: int
	:type fileContent: string
	:return newFileContent: contenu du nouveau fichier (temps/m_avg)
	:type return: string
	*/
	// 1) preparation des données : 
	vector<string> dataLines = split(fileContent, "\n");
	vector<long double> ColoneTime = convertColoneStoLD(0, dataLines);
	vector<long double> ColoneChannel = convertColoneStoLD(1, dataLines); 
	// 2) calcule de la moyenne mobile : 
	vector <long double> mvAvg;
	long double avg;
	for (int i = 0 ; i < ColoneTime.size() ; i++){
		avg = calcAverage(i, win_size, ColoneChannel);
		mvAvg.push_back(avg);
	}
	// 3) preparation du nouveau fichier : 
	string newFileContent = "%time av_value\n";
	for (int i = 0 ; i < ColoneTime.size() ; i++){
		newFileContent += to_string(ColoneTime[i])+" "+to_string(mvAvg[i])+"\n";
	}
	return newFileContent;
}