#ifndef MYTOOLBOX_H
#define MYTOOLBOX_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// common functions : 
string readFile(string file);
void writeFile (string fileContent,string newfileName);
vector<string> split(string value, string sep);
map<string, vector<long double> > getColumnsChannel (string fileContent);

// extract functions :
vector<string> splitElements (string line);
map<string, vector<long double> > extractChannel (int numChannel, string fileContent);

// m_average functions :  
long double calcAvg(int pos, int win_size, vector<long double> dataSignal);
vector<long double> calcMovingAvg (vector<long double> dataSignal, int win_size);

#endif
