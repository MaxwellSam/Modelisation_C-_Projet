#ifndef MYTOOLBOX_H
#define MYTOOLBOX_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// common functions : 
string read_data(string file);
void writeFile (string fileContent,string newfileName);
vector<string> split(string value, string sep);
vector<long double> convertColoneStoLD (int numColone, vector<string> dataLines);

// extract functions :
vector<string> splitElements (string line);
string extractChannel (int numChannel, string fileContent);

// m_average functions :  
long double calcAverage(int pos, int win_size, vector<long double> data);
string movingAverage (string fileContent, int win_size);

#endif
