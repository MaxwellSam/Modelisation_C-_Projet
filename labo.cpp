#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std; // utilisation de l'espace de nom de std

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

int main(){
    // map<string, vector<int> > dataframe;
// 	int nbrOfChannel = 4;
// 	for (int i = 1 ; i <= nbrOfChannel ; i++){
// 		string channel = "channel_";
// 		channel += to_string(i);
// 		cout << channel << endl;
// 		dataframe[channel] = vector<int> v;
// 	}
// 	cout << dataframe["channel_1"] << endl;
// 	dataframe["channel_1"].push_back(1);
// 	cout << dataframe["channel_1"] << endl;
		
	string line = "0.000       	0.83        	-4.58       	3.75";
	vector<string> dataline = splitElements(line);
	for (int i = 0 ; i <= dataline.size() ; i++) {
		cout << dataline[i] << endl;
	}
	cout << dataline[2] << endl;
	return 0;
}