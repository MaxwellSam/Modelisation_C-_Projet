/*
* CPP Projet Modelisation
* file name : extract.cpp
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

int main(int argc, char *argv[]){
	
	try {
		cout << "* extraction des données du canal " << argv[3] << endl;
		// recuperation des arguments :
		string fileName = argv[1];
		string newFileName = argv[2];
		int numChannel = stoi(argv[3]);
		// extraction des données du canal :  
		string fileContent = readFile(fileName);
		map<string, vector<long double> > dataChannel = extractChannel(numChannel, fileContent);
		cout << "** données du canal extraites" << endl;
		// ecriture du fichier :
		string newFileContent = "%time channel_"+to_string(numChannel)+"\n"; // header
		for (int i = 0 ; i < dataChannel["Time"].size() ; i++){
			newFileContent += to_string(dataChannel["Time"][i])+" "+to_string(dataChannel["Signal"][i])+"\n";
		}
		writeFile(newFileContent, newFileName);
		cout << "** fichier " << newFileName << " créé" << endl;
		return 0;
	} catch (exception& ex){
		cerr << "Erreur : probleme dans les arguments" << endl;
	}
}