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

string extractChannel (int numChannel, string filename) {
	/*
	Produit à partir du nom du fichier et du numero de channel, 
	une string contenant les informations sur le temps et les données 
	du canal selectionné. 
	:param numChannel: numero du canal
	:param filename: nom du fichier de base
	:type numChannel: int 
	:type filename: string
	:return newData: la chaine de caractère contenant les infos du canal
	:type newData: string
	*/
	
	string newData = "";  
	vector <string> elementsLine;
	// preparation de la source : 
	string content=read_data(filename); // extraction du fichier
	vector<string> dataLines=split(content, "\n"); // découpe des lignes
	// creation de la nouvelle chaine de caractère :  
	newData += "%time channel_"+to_string(numChannel)+"\n"; // première ligne du fichier
	for (int i = 4 ; i < dataLines.size() ; i++){
		elementsLine = splitElements(dataLines[i]);
		cout << elementsLine[numChannel] << endl;
		newData += elementsLine[0]+" "+elementsLine[numChannel]+"\n"; 
	}
	return newData;
}

bool Contains(int num, vector<int> listNum){
	/*
	Verifie la presence du nombre dans la liste. 
	:param num: nombre 
	:param listNum: liste de nombres
	:type num: int 
	:type listNum: vector<int>
	:return rep: reponse de la verification 
	:type return: bool 
	*/
	bool rep = false;
	for (int i = 0 ; i < listNum.size() ; i++){
		if (listNum[i]==num){
			rep = true;
			break;
		}
	}
	return rep; 
}

int main(int argc, char *argv[]){
	
	try {
		string fileName = argv[1];
		string newFileName = argv[2];
		int numChannel = stoi(argv[3]);
		string dataChannel = extractChannel(numChannel, fileName);
		cout << dataChannel << endl;
		cout << endl << dataChannel << endl; 
		writeFile(dataChannel, newFileName);
		return 0;
	} catch (exception& ex){
		cerr << "Erreur : probleme dans les arguments" << endl;
	}
}