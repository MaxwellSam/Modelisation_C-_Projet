#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std; // utilisation de l'espace de nom de std

string read_data(string file){
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

vector<string> split(string value, string sep){
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

int main(){
    string filename="datasetTest.txt";
    string content=read_data(filename);
    cout << content << endl;
	vector<string> dataLines=split(content, "\n");
	cout << dataLines[2] << endl;
    return 0;
}